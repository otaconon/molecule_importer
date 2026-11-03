#pragma once

#include <godot_cpp/classes/editor_import_plugin.hpp>
#include <godot_cpp/classes/resource_saver.hpp>

#include "load_molecule_data.h"

namespace godot {

class MoleculeImportPlugin : public EditorImportPlugin {
	GDCLASS(MoleculeImportPlugin, EditorImportPlugin)

protected:
	static void _bind_methods();

	static Ref<Mol> import_molecule_data(const String &p_source_file, Error &r_error);

public:
	MoleculeImportPlugin() = default;
	~MoleculeImportPlugin() override = default;

	[[nodiscard]] String _get_importer_name() const override;
	[[nodiscard]] String _get_visible_name() const override;
	[[nodiscard]] PackedStringArray _get_recognized_extensions() const override;
	[[nodiscard]] String _get_save_extension() const override;
	[[nodiscard]] String _get_resource_type() const override;

	[[nodiscard]] int32_t _get_preset_count() const override;
	[[nodiscard]] String _get_preset_name(int32_t p_preset) const override;
	[[nodiscard]] TypedArray<Dictionary> _get_import_options(const String &p_path,
			int32_t p_preset) const override;
	[[nodiscard]] bool _get_option_visibility(const String &p_path,
			const StringName &p_option_name,
			const Dictionary &p_options) const override;

	[[nodiscard]] Error _import(const String &p_source_file, const String &p_save_path,
			const Dictionary &p_options,
			const TypedArray<String> &p_platform_variants,
			const TypedArray<String> &p_gen_files) const override;
};
} // namespace godot
