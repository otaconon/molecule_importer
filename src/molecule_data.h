#pragma once

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/variant/array.hpp>

namespace godot {
    class MoleculeData : public Resource {
        GDCLASS(MoleculeData, Resource)

    private:
        Array atoms;
        Array bonds;
        Array resonance_structures;

    protected:
        static void _bind_methods();

    public:
        MoleculeData() = default;
        ~MoleculeData() = default;

        void set_atoms(const Array& p_atoms);
        Array get_atoms() const;

        void set_bonds(const Array& p_bonds);
        Array get_bonds() const;

        void set_resonance_structures(const Array& p_resonance_structures);
        Array get_resonance_structures() const;
    };
}


