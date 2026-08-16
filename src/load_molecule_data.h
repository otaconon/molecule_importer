#pragma once

#include <Geometry/point.h>
#include <GraphMol/FileParsers/FileParsers.h>
#include <GraphMol/FileParsers/MolSupplier.h>
#include <GraphMol/GraphMol.h>

#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/classes/resource_saver.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include <string>

#include "atom.h"
#include "bond.h"
#include "molecule_data.h"

using namespace godot;

static Array load_atom_data(std::shared_ptr<RDKit::ROMol> p_mol) {
    Array atom_data{};
    const RDKit::Conformer &conf = p_mol->getConformer();
    for (const auto atom : p_mol->atoms()) {
      String symbol(atom->getSymbol().c_str());
      RDGeom::Point3D pos = conf.getAtomPos(atom->getIdx());

      Ref<Atom> new_atom;
      new_atom.instantiate();
      new_atom->set_symbol(symbol);
      new_atom->set_position(Vector3(pos.x, pos.y, pos.z));
      
      atom_data.push_back(new_atom);
    }

    return atom_data;
}

static Array load_bond_data(std::shared_ptr<RDKit::ROMol> p_mol) {
	Array bond_data;

    for (const auto bond : p_mol->bonds()) {
        int atom_a_idx = bond->getBeginAtomIdx();
        int atom_b_idx = bond->getEndAtomIdx();

        Bond::BondType bond_type;
        switch (bond->getBondType()) {
            case RDKit::Bond::SINGLE:
                bond_type = Bond::BondType::SINGLE;
                break;
            case RDKit::Bond::DOUBLE:
                bond_type = Bond::BondType::DOUBLE;
                break;
            case RDKit::Bond::TRIPLE:
                bond_type = Bond::BondType::TRIPLE;
                break;
            default:
                continue;
        }
        
        Ref<Bond> new_bond;
        new_bond.instantiate();
        new_bond->set_atom_a_idx(atom_a_idx);
        new_bond->set_atom_b_idx(atom_b_idx);
        new_bond->set_bond_type(bond_type);

        bond_data.push_back(new_bond);
    }

	return bond_data;
}

static Ref<MoleculeData> load_molecule_data(const std::string &p_file_path) {
    Ref<MoleculeData> molecule_data;
    molecule_data.instantiate();

	RDKit::SDMolSupplier supplier(p_file_path, false, false, false);
    // TODO: Handle more than one molecule??
	while (!supplier.atEnd()) {
		std::shared_ptr<RDKit::ROMol> mol(supplier.next());
        if (!mol || mol->getNumConformers() == 0) {
            continue;
        }

        molecule_data->set_atoms(load_atom_data(mol));
        molecule_data->set_bonds(load_bond_data(mol));
    }

    return molecule_data;
}

