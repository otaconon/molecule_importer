#pragma once

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/variant/array.hpp>

namespace godot {
    class Atom : public Resource {
        GDCLASS(Atom, Resource)

    private:
        String symbol;
        Vector3 position;

    protected:
        static void _bind_methods();

    public:
        Atom() = default;
        ~Atom() = default;

        void set_symbol(const String& p_symbol);
        String get_symbol() const;

        void set_position(const Vector3& p_position);
        Vector3 get_position() const;
    };
}

