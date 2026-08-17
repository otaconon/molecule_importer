#pragma once

#include <Geometry/point.h>
#include <GraphMol/FileParsers/FileParsers.h>
#include <GraphMol/FileParsers/MolSupplier.h>
#include <GraphMol/GraphMol.h>
#include <GraphMol/MolOps.h>
#include <GraphMol/Resonance.h>

#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/classes/resource_saver.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include <string>

#include "atom.h"
#include "bond.h"
#include "molecule_data.h"
#include "resonance_structure.h"

static godot::Array load_atom_data(std::shared_ptr<RDKit::ROMol> p_mol) {
    godot::Array atom_data{};
    const RDKit::Conformer &conf = p_mol->getConformer();
    for (const auto atom : p_mol->atoms()) {
      godot::String symbol(atom->getSymbol().c_str());
      RDGeom::Point3D pos = conf.getAtomPos(atom->getIdx());

      godot::Ref<godot::Atom> new_atom;
      new_atom.instantiate();
      new_atom->set_symbol(symbol);
      new_atom->set_position(godot::Vector3(pos.x, pos.y, pos.z));

      atom_data.push_back(new_atom);
    }

    return atom_data;
}

static godot::Array load_bond_data(std::shared_ptr<RDKit::ROMol> p_mol) {
	godot::Array bond_data;

    for (const auto bond : p_mol->bonds()) {
        int atom_a_idx = bond->getBeginAtomIdx();
        int atom_b_idx = bond->getEndAtomIdx();

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

static godot::Array load_resonance_data(std::shared_ptr<RDKit::ROMol> p_mol) {
    unsigned int res_flags =
    RDKit::ResonanceMolSupplier::KEKULE_ALL |
    RDKit::ResonanceMolSupplier::ALLOW_CHARGE_SEPARATION |
    RDKit::ResonanceMolSupplier::ALLOW_INCOMPLETE_OCTETS;

    godot::Array resonance_structures;
    unsigned int max_structs = 10;
    RDKit::ResonanceMolSupplier res_supplier(*p_mol, res_flags, max_structs);
    while (!res_supplier.atEnd()) {
        std::unique_ptr<RDKit::ROMol> res_mol(res_supplier.next());
        if (!res_mol) continue;

        godot::Array charges;
        charges.resize(res_mol->atoms().size());
        for (const auto atom: res_mol->atoms()) {
            unsigned int atom_idx = atom->getIdx();
            int formal_charge = atom->getFormalCharge();
            charges[atom_idx] = formal_charge;
        }

        godot::Ref<godot::ResonanceStructure> new_resonance_structure;
        new_resonance_structure.instantiate();
        new_resonance_structure->set_charges(charges);
        resonance_structures.push_back(new_resonance_structure);
    }

    return resonance_structures;
}

static godot::Ref<godot::MoleculeData> load_molecule_data(const std::string &p_file_path) {
    godot::Ref<godot::MoleculeData> molecule_data;
    molecule_data.instantiate();

	RDKit::SDMolSupplier supplier(p_file_path, false, false, false);
    // TODO: Handle more than one molecule??
	while (!supplier.atEnd()) {
		std::shared_ptr<RDKit::ROMol> mol(supplier.next());
        if (!mol || mol->getNumConformers() == 0) {
            continue;
        }

        unsigned int failed_op = 0;
        unsigned int sanitize_ops = RDKit::MolOps::SANITIZE_ALL;
        sanitize_ops ^= RDKit::MolOps::SANITIZE_SETAROMATICITY;
        RDKit::MolOps::sanitizeMol(static_cast<RDKit::RWMol &>(*mol), failed_op, sanitize_ops);

        molecule_data->set_atoms(load_atom_data(mol));
        molecule_data->set_bonds(load_bond_data(mol));
        molecule_data->set_resonance_structures(load_resonance_data(mol));
    }

    return molecule_data;
}

