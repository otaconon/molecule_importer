#include "bond_data.h"
#include <godot_cpp/core/class_db.hpp>

namespace godot {
    void BondData::_bind_methods() {
        ClassDB::bind_method(D_METHOD("set_bonds", "bonds"), &BondData::set_bonds);
        ClassDB::bind_method(D_METHOD("get_bonds"), &BondData::get_bonds);

        ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "bonds"), "set_bonds", "get_bonds");
    }

    void BondData::set_bonds(const Array& p_bonds) {
        bonds = p_bonds;
    }

    Array BondData::get_bonds() const {
        return bonds;
    }
}

