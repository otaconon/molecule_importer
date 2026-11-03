#pragma once

#include <godot_cpp/classes/resource.hpp>

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
        ~Atom() override = default;

        void set_symbol(const String& p_symbol);
        [[nodiscard]] String get_symbol() const;

        void set_position(const Vector3& p_position);
        [[nodiscard]] Vector3 get_position() const;
    };
}

