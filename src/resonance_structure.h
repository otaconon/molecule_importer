#pragma once

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/variant/array.hpp>

#include "atom.h"

namespace godot {
class ResonanceStructure : public Resource {
	GDCLASS(ResonanceStructure, Resource)

private:
    Array charges;
	Array bond_types;

protected:
	static void _bind_methods();

public:
	ResonanceStructure() = default;
	~ResonanceStructure() override = default;

	void set_charges(const Array &p_charges);
	[[nodiscard]] Array get_charges() const;

	void set_bond_types(const Array &p_bond_types);
	[[nodiscard]] Array get_bond_types() const;
};
} //namespace godot


