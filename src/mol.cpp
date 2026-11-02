#include "mol.h"

#include <godot_cpp/core/class_db.hpp>

namespace godot {
void Mol::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_atoms", "atoms"), &Mol::set_atoms);
	ClassDB::bind_method(D_METHOD("get_atoms"), &Mol::get_atoms);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "atoms"), "set_atoms", "get_atoms");

	ClassDB::bind_method(D_METHOD("set_bonds", "bonds"), &Mol::set_bonds);
	ClassDB::bind_method(D_METHOD("get_bonds"), &Mol::get_bonds);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "bonds"), "set_bonds", "get_bonds");

	ClassDB::bind_method(D_METHOD("set_resonance_structures", "resonance_structures"), &Mol::set_resonance_structures);
	ClassDB::bind_method(D_METHOD("get_resonance_structures"), &Mol::get_resonance_structures);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "resonance_structures"), "set_resonance_structures", "get_resonance_structures");
}

void Mol::set_atoms(const Array &p_atoms) {
	atoms = p_atoms;
}

Array Mol::get_atoms() const {
	return atoms;
}

void Mol::set_bonds(const Array &p_bonds) {
	bonds = p_bonds;
}

Array Mol::get_bonds() const {
	return bonds;
}

void Mol::set_resonance_structures(const Array &p_resonance_structures) {
	resonance_structures = p_resonance_structures;
}

Array Mol::get_resonance_structures() const {
	return resonance_structures;
}
void Mol::set_smiles(const String &p_smiles) {
	smiles = p_smiles;
}

String Mol::get_smiles() const {
	return smiles;
}

void Mol::set_texture(const Ref<Texture2D> &p_texture) {
	texture = p_texture;
}

Ref<Texture2D> Mol::get_texture() const {
	return texture;
}

} //namespace godot
