#include "sdf_mol.h"

#include <godot_cpp/core/class_db.hpp>

namespace godot {
    void SDFMol::_bind_methods() {
        ClassDB::bind_method(D_METHOD("set_atoms", "atoms"), &SDFMol::set_atoms);
        ClassDB::bind_method(D_METHOD("get_atoms"), &SDFMol::get_atoms);
        ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "atoms"), "set_atoms", "get_atoms");

        ClassDB::bind_method(D_METHOD("set_bonds", "bonds"), &SDFMol::set_bonds);
        ClassDB::bind_method(D_METHOD("get_bonds"), &SDFMol::get_bonds);
        ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "bonds"), "set_bonds", "get_bonds");

        ClassDB::bind_method(D_METHOD("set_resonance_structures", "resonance_structures"), &SDFMol::set_resonance_structures);
        ClassDB::bind_method(D_METHOD("get_resonance_structures"), &SDFMol::get_resonance_structures);
        ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "resonance_structures"), "set_resonance_structures", "get_resonance_structures");
    }

    void SDFMol::set_atoms(const Array& p_atoms) {
        atoms = p_atoms;
    }

    Array SDFMol::get_atoms() const {
        return atoms;
    }

    void SDFMol::set_bonds(const Array& p_bonds) {
        bonds = p_bonds;
    }

    Array SDFMol::get_bonds() const {
        return bonds;
    }

    void SDFMol::set_resonance_structures(const Array& p_resonance_structures) {
        resonance_structures = p_resonance_structures;
    }

    Array SDFMol::get_resonance_structures() const {
        return resonance_structures;
    }
}


