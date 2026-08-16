#include "molecule_data.h"

#include <godot_cpp/core/class_db.hpp>

namespace godot {
    void MoleculeData::_bind_methods() {
        ClassDB::bind_method(D_METHOD("set_atoms", "atoms"), &MoleculeData::set_atoms);
        ClassDB::bind_method(D_METHOD("get_atoms"), &MoleculeData::get_atoms);
        ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "atoms"), "set_atoms", "get_atoms");

        ClassDB::bind_method(D_METHOD("set_bonds", "bonds"), &MoleculeData::set_bonds);
        ClassDB::bind_method(D_METHOD("get_bonds"), &MoleculeData::get_bonds);
        ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "bonds"), "set_bonds", "get_bonds");
    }

    void MoleculeData::set_atoms(const Array& p_atoms) {
        atoms = p_atoms;
    }

    Array MoleculeData::get_atoms() const {
        return atoms;
    }

    void MoleculeData::set_bonds(const Array& p_bonds) {
        bonds = p_bonds;
    }

    Array MoleculeData::get_bonds() const {
        return bonds;
    }
}


