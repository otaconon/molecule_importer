#pragma once

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/variant/array.hpp>

#include "atom.h"

namespace godot {
class Bond : public Resource {
	GDCLASS(Bond, Resource)
public:
	enum BondType {
		SINGLE,
		DOUBLE,
		TRIPLE
	};

private:
	int atom_a_idx = 0;
	int atom_b_idx = 0;
	BondType bond_type = BondType::SINGLE;

protected:
	static void _bind_methods();

public:
	Bond() = default;
	~Bond() = default;

	void set_atom_a_idx(const int &p_atom_a_idx);
	int get_atom_a_idx() const;

	void set_atom_b_idx(const int &p_atom_b_idx);
	int get_atom_b_idx() const;

	void set_bond_type(BondType p_bond_type);
	BondType get_bond_type() const;
};
} //namespace godot

VARIANT_ENUM_CAST(godot::Bond::BondType);
