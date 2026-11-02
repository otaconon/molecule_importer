#pragma once

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/variant/array.hpp>

namespace godot {
class Mol : public Resource {
	GDCLASS(Mol, Resource)

private:
	String name;
	Array atoms;
	Array bonds;
	Array resonance_structures;
	String smiles;
	Ref<Texture2D> texture;

protected:
	static void _bind_methods();

public:
	Mol() = default;
	~Mol() = default;

	void set_atoms(const Array &p_atoms);
	Array get_atoms() const;

	void set_bonds(const Array &p_bonds);
	Array get_bonds() const;

	void set_resonance_structures(const Array &p_resonance_structures);
	Array get_resonance_structures() const;

	void set_smiles(const String &p_smiles);
	String get_smiles() const;

	void set_texture(const Ref<Texture2D> &p_texture);
	Ref<Texture2D> get_texture() const;
};
} //namespace godot
