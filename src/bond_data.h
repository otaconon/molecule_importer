#pragma once

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/variant/array.hpp>

namespace godot {
    class BondData : public Resource {
        GDCLASS(BondData, Resource)

    private:
        Array bonds;

    protected:
        static void _bind_methods();

    public:
        BondData() = default;
        ~BondData() = default;

        void set_bonds(const Array& p_bonds);
        Array get_bonds() const;
    };
}

