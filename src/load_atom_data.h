#include <Geometry/point.h>
#include <GraphMol/FileParsers/FileParsers.h>
#include <GraphMol/FileParsers/MolSupplier.h>
#include <GraphMol/GraphMol.h>

#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/classes/resource_saver.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include <string>

#include "Atom.h"

using namespace godot;

static Array load_atom_data(const String &file_path) {
  Array atom_data_array;

  String real_path =
      ProjectSettings::get_singleton()->globalize_path(file_path);
  std::string path_str = real_path.utf8().get_data();

  RDKit::SDMolSupplier supplier(path_str, false, false, false);

  while (!supplier.atEnd()) {
    std::unique_ptr<RDKit::ROMol> mol(supplier.next());
    if (!mol || mol->getNumConformers() == 0) {
      continue;
    }

    const RDKit::Conformer &conf = mol->getConformer();

    for (const auto atom : mol->atoms()) {
      String symbol(atom->getSymbol().c_str());
      RDGeom::Point3D pos = conf.getAtomPos(atom->getIdx());

      Ref<Atom> new_atom;
      new_atom.instantiate();

      new_atom->set_symbol(symbol);
      new_atom->set_position(Vector3(pos.x, pos.y, pos.z));
      
      atom_data_array.push_back(new_atom);
    }
  }

  return atom_data_array;
}
