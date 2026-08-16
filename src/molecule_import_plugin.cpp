#include "molecule_import_plugin.h"

#include "molecule_data.h"

namespace godot {
void MoleculeImportPlugin::_bind_methods() {
	// Empty, but required for GDExtension registration
}

String MoleculeImportPlugin::_get_preset_name(int32_t p_preset) const {
	return "Default";
}
String MoleculeImportPlugin::_get_importer_name() const {
	return "molecule.rdkit.importer";
}

String MoleculeImportPlugin::_get_visible_name() const {
	return "Molecule (RDKit)";
}

PackedStringArray MoleculeImportPlugin::_get_recognized_extensions() const {
	PackedStringArray exts;
	exts.push_back("mol");
	exts.push_back("sdf");
	return exts;
}

String MoleculeImportPlugin::_get_save_extension() const {
	return "res";
}

String MoleculeImportPlugin::_get_resource_type() const {
	return "AtomData";
}

int32_t MoleculeImportPlugin::_get_preset_count() const {
	return 0;
}

TypedArray<Dictionary>
MoleculeImportPlugin::_get_import_options(const String &p_path,
		int32_t p_preset) const {
	return TypedArray<Dictionary>();
}

bool MoleculeImportPlugin::_get_option_visibility(
		const String &p_path, const StringName &p_option_name,
		const Dictionary &p_options) const {
	return true;
}

Error MoleculeImportPlugin::_import(
		const String &p_source_file, const String &p_save_path,
		const Dictionary &p_options, const TypedArray<String> &p_platform_variants,
		const TypedArray<String> &p_gen_files) const {
	Error r_error = OK;

	Ref<MoleculeData> molecule_data = import_molecule_data(p_source_file, r_error);
	if (r_error != OK) {
		return r_error;
	}

	String out_path = vformat("%s.%s", p_save_path, _get_save_extension());
	return ResourceSaver::get_singleton()->save(molecule_data, out_path, ResourceSaver::FLAG_BUNDLE_RESOURCES);
}

Ref<MoleculeData> MoleculeImportPlugin::import_molecule_data(const String &p_source_file, Error &r_error) const {
	Ref<MoleculeData> molecule_data;
	String real_path =
			ProjectSettings::get_singleton()->globalize_path(p_source_file);
	std::string file_path = real_path.utf8().get_data();
	try {
		molecule_data = load_molecule_data(file_path);
	} catch (const std::exception &e) {
		UtilityFunctions::printerr("Failed to parse '", p_source_file,
				"': ", e.what());
		r_error = ERR_PARSE_ERROR;
		return Ref<MoleculeData>();
	} catch (...) {
		UtilityFunctions::printerr("Failed to parse '", p_source_file,
				"': unknown error");
		r_error = ERR_PARSE_ERROR;
		return Ref<MoleculeData>();
	}

	return molecule_data;
}
} // namespace godot
