#include "atom.h"

#include <godot_cpp/core/class_db.hpp>

namespace godot {
    void Atom::_bind_methods() {
        ClassDB::bind_method(D_METHOD("set_symbol", "symbol"), &Atom::set_symbol);
        ClassDB::bind_method(D_METHOD("get_symbol"), &Atom::get_symbol);
        ADD_PROPERTY(PropertyInfo(Variant::STRING, "symbol"), "set_symbol", "get_symbol");

        ClassDB::bind_method(D_METHOD("set_position", "position"), &Atom::set_position);
        ClassDB::bind_method(D_METHOD("get_position"), &Atom::get_position);
        ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "position"), "set_position", "get_position");
    }

    void Atom::set_symbol(const String& p_symbol) {
        symbol = p_symbol;
    }

    String Atom::get_symbol() const {
        return symbol;
    }

    void Atom::set_position(const Vector3& p_position) {
        position = p_position;
    }

    Vector3 Atom::get_position() const {
        return position;
    }
}

