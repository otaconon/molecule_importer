#pragma once

#include <Geometry/point.h>
#include <GraphMol/FileParsers/FileParsers.h>
#include <GraphMol/FileParsers/MolSupplier.h>
#include <GraphMol/Resonance.h>
#include <GraphMol/MolDraw2D/MolDraw2DCairo.h>
#include <GraphMol/DistGeomHelpers/Embedder.h>
#include <GraphMol/Depictor/RDDepictor.h>

#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include <string>

#include "atom.h"
#include "bond.h"
#include "mol.h"
#include "resonance_structure.h"
#include "godot_cpp/classes/image_texture.hpp"

inline godot::Array load_atom_data(const RDKit::ROMol &p_mol) {
    godot::Array atom_data{};
    const RDKit::Conformer &conf = p_mol.getConformer();
    for (const auto atom : p_mol.atoms()) {
      godot::String symbol(atom->getSymbol().c_str());
      const RDGeom::Point3D &pos = conf.getAtomPos(atom->getIdx());

      godot::Ref<godot::Atom> new_atom;
      new_atom.instantiate();
      new_atom->set_symbol(symbol);
      new_atom->set_position(godot::Vector3(pos.x, pos.y, pos.z));

      atom_data.push_back(new_atom);
    }

    return atom_data;
}

inline godot::Array load_bond_data(const RDKit::ROMol &p_mol) {
	godot::Array bond_data;

    for (const auto bond : p_mol.bonds()) {
        const uint16_t atom_a_idx = bond->getBeginAtomIdx();
        const uint16_t atom_b_idx = bond->getEndAtomIdx();

        godot::Bond::BondType bond_type;
        switch (bond->getBondType()) {
            case RDKit::Bond::SINGLE:
                bond_type = godot::Bond::BondType::SINGLE;
                break;
            case RDKit::Bond::DOUBLE:
                bond_type = godot::Bond::BondType::DOUBLE;
                break;
            case RDKit::Bond::TRIPLE:
                bond_type = godot::Bond::BondType::TRIPLE;
                break;
            default:
                continue;
        }

        godot::Ref<godot::Bond> new_bond;
        new_bond.instantiate();
        new_bond->set_atom_a_idx(atom_a_idx);
        new_bond->set_atom_b_idx(atom_b_idx);
        new_bond->set_bond_type(bond_type);

        bond_data.push_back(new_bond);
    }

	return bond_data;
}

inline godot::Array load_resonance_data(RDKit::ROMol &p_mol) {
    constexpr unsigned int res_flags =
    RDKit::ResonanceMolSupplier::KEKULE_ALL |
    RDKit::ResonanceMolSupplier::ALLOW_CHARGE_SEPARATION |
    RDKit::ResonanceMolSupplier::ALLOW_INCOMPLETE_OCTETS;

    godot::Array resonance_structures;
    constexpr uint16_t max_structs = 10;
    RDKit::ResonanceMolSupplier res_supplier(p_mol, res_flags, max_structs);
    while (!res_supplier.atEnd()) {
       	std::unique_ptr<RDKit::ROMol> res_mol(res_supplier.next());
        if (!res_mol) continue;

        godot::Array charges;
        charges.resize(res_mol->getNumAtoms());
        for (const auto atom: res_mol->atoms()) {
            const auto atom_idx = atom->getIdx();
            const auto formal_charge = atom->getFormalCharge();
            charges[atom_idx] = formal_charge;
        }

        godot::Array bond_types;
        bond_types.resize(res_mol->getNumBonds());
        
        int bond_idx = 0;
        for (const auto bond: res_mol->bonds()) {
            switch (bond->getBondType()) {
                case RDKit::Bond::SINGLE:
                    bond_types[bond_idx] = godot::Bond::SINGLE;
                    break;
                case RDKit::Bond::DOUBLE:
                    bond_types[bond_idx] = godot::Bond::DOUBLE;
                    break;
                case RDKit::Bond::TRIPLE:
                    bond_types[bond_idx] = godot::Bond::TRIPLE;
                    break;
                default:
            		std::string mol_name = "Unnamed";
            		p_mol.getPropIfPresent("_Name", mol_name);
                    godot::UtilityFunctions::printerr(
                        "Unhandled bond type in molecule: ",
                        godot::String::utf8(mol_name.c_str()));
                    break;
            }
            bond_idx++;
        }

        godot::Ref<godot::ResonanceStructure> new_resonance_structure;
        new_resonance_structure.instantiate();
        new_resonance_structure->set_charges(charges);
        new_resonance_structure->set_bond_types(bond_types);
        resonance_structures.push_back(new_resonance_structure);
    }

    return resonance_structures;
}

inline godot::Ref<godot::Mol> load_sdf_mol(const std::string &p_file_path) {
    godot::Ref<godot::Mol> mol;
    mol.instantiate();

	RDKit::SDMolSupplier supplier(p_file_path, false, false, false);
    // TODO: Handle more than one molecule??
	while (!supplier.atEnd()) {
		std::unique_ptr<RDKit::ROMol> rd_mol(supplier.next());
        if (!rd_mol || rd_mol->getNumConformers() == 0) {
            continue;
        }

        unsigned int failed_op = 0;
        unsigned int sanitize_ops = RDKit::MolOps::SANITIZE_ALL;
        sanitize_ops ^= RDKit::MolOps::SANITIZE_SETAROMATICITY;
        RDKit::MolOps::sanitizeMol(dynamic_cast<RDKit::RWMol &>(*rd_mol), failed_op, sanitize_ops);

        mol->set_atoms(load_atom_data(*rd_mol));
        mol->set_bonds(load_bond_data(*rd_mol));
        mol->set_resonance_structures(load_resonance_data(*rd_mol));
    }

    return mol;
}

inline godot::Ref<godot::Texture2D> load_texture(RDKit::ROMol &p_mol) {
    RDKit::MolDraw2DCairo mol_draw(512, 512);
    mol_draw.drawOptions().clearBackground = false;
    mol_draw.drawMolecule(p_mol);
    mol_draw.finishDrawing();
    std::string png = mol_draw.getDrawingText();

    godot::PackedByteArray bytes;
    bytes.resize(png.size());
    memcpy(bytes.ptrw(), png.data(), png.size());

    godot::Ref<godot::Image> img;
    img.instantiate();
    img->load_png_from_buffer(bytes);

    return godot::ImageTexture::create_from_image(img);
}

inline godot::Ref<godot::Mol> load_smiles_mol(const std::string &p_file_path) {
    godot::Ref<godot::Mol> mol;
    mol.instantiate();
	RDKit::SmilesMolSupplier supplier(p_file_path, "\t", 0, -1, false, true);
	// TODO: Handle more than one molecule??
	while (!supplier.atEnd()) {
		std::unique_ptr<RDKit::ROMol> rd_mol(supplier.next());
		RDDepict::compute2DCoords(*rd_mol);
		if (!rd_mol || rd_mol->getNumConformers() == 0) {
			godot::UtilityFunctions::print(
				"Zero conformers found for molecule: ",
				godot::String::utf8(p_file_path.c_str()));
			continue;
		}

		unsigned int failed_op = 0;
		unsigned int sanitize_ops = RDKit::MolOps::SANITIZE_ALL;
		sanitize_ops ^= RDKit::MolOps::SANITIZE_SETAROMATICITY;
		RDKit::MolOps::sanitizeMol(dynamic_cast<RDKit::RWMol &>(*rd_mol), failed_op, sanitize_ops);

		mol->set_atoms(load_atom_data(*rd_mol));
		mol->set_bonds(load_bond_data(*rd_mol));
		mol->set_texture(load_texture(*rd_mol));
	}
    return mol;
}