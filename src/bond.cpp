#include "bond.h"

namespace godot {
    void Bond::_bind_methods() {
        BIND_ENUM_CONSTANT(BondType::SINGLE);
        BIND_ENUM_CONSTANT(BondType::DOUBLE);
        BIND_ENUM_CONSTANT(BondType::TRIPLE);

        ClassDB::bind_method(D_METHOD("set_atom_a_idx", "atom_a_idx"), &Bond::set_atom_a_idx);
        ClassDB::bind_method(D_METHOD("get_atom_a_idx"), &Bond::get_atom_a_idx);
        ADD_PROPERTY(PropertyInfo(Variant::INT, "atom_a_idx"), "set_atom_a_idx", "get_atom_a_idx");

        ClassDB::bind_method(D_METHOD("set_atom_b_idx", "atom_b_idx"), &Bond::set_atom_b_idx);
        ClassDB::bind_method(D_METHOD("get_atom_b_idx"), &Bond::get_atom_b_idx);
        ADD_PROPERTY(PropertyInfo(Variant::INT, "atom_b_idx"), "set_atom_b_idx", "get_atom_b_idx");

        ClassDB::bind_method(D_METHOD("set_bond_type", "bond_type"), &Bond::set_bond_type);
        ClassDB::bind_method(D_METHOD("get_bond_type"), &Bond::get_bond_type);
        ADD_PROPERTY(PropertyInfo(Variant::INT, "bond_type", PROPERTY_HINT_ENUM, "SINGLE,DOUBLE,TRIPLE"), "set_bond_type", "get_bond_type");
    }

    void Bond::set_atom_a_idx(const int& p_atom_a_idx) {
        atom_a_idx = p_atom_a_idx;
    }

    int Bond::get_atom_a_idx() const {
        return atom_a_idx;
    }

    void Bond::set_atom_b_idx(const int& p_atom_b_idx) {
        atom_b_idx = p_atom_b_idx;
    }

    int Bond::get_atom_b_idx() const {
        return atom_b_idx;
    }

    void Bond::set_bond_type(BondType p_bond_type) {
        bond_type = p_bond_type;
    }

    Bond::BondType Bond::get_bond_type() const {
        return bond_type;
    }
}