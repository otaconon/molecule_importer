#pragma once

#include <godot_cpp/classes/resource.hpp>

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
	uint16_t atom_a_idx = 0;
	uint16_t atom_b_idx = 0;
	BondType bond_type = BondType::SINGLE;

protected:
	static void _bind_methods();

public:
	Bond() = default;
	~Bond() override = default;

	void set_atom_a_idx(const uint16_t &p_atom_a_idx);
	[[nodiscard]] int get_atom_a_idx() const;

	void set_atom_b_idx(const uint16_t &p_atom_b_idx);
	[[nodiscard]] int get_atom_b_idx() const;

	void set_bond_type(BondType p_bond_type);
	[[nodiscard]] BondType get_bond_type() const;
};
} //namespace godot

VARIANT_ENUM_CAST(godot::Bond::BondType);
