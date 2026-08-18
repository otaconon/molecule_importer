#include "resonance_structure.h"

#include <godot_cpp/core/class_db.hpp>

namespace godot {
    void ResonanceStructure::_bind_methods() {
        ClassDB::bind_method(D_METHOD("set_charges", "charges"), &ResonanceStructure::set_charges);
        ClassDB::bind_method(D_METHOD("get_charges"), &ResonanceStructure::get_charges);
        ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "charges"), "set_charges", "get_charges");

        ClassDB::bind_method(D_METHOD("set_bond_types", "bond_types"), &ResonanceStructure::set_bond_types);
        ClassDB::bind_method(D_METHOD("get_bond_types"), &ResonanceStructure::get_bond_types);
        ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "bond_types"), "set_bond_types", "get_bond_types");
    }

    void ResonanceStructure::set_charges(const Array& p_charges) {
        charges = p_charges;
    }

    Array ResonanceStructure::get_charges() const {
        return charges;
    }

    void ResonanceStructure::set_bond_types(const Array& p_bond_types) {
        bond_types = p_bond_types;
    }

    Array ResonanceStructure::get_bond_types() const {
        return bond_types;
    }
}
