import os
import sys
import glob

env = SConscript("godot-cpp/SConstruct")
env.VariantDir("build/obj", "src", duplicate=0)
sources = Glob("build/obj/*.cpp")

if sys.platform == "win32":
    env.Append(CXXFLAGS=["/std:c++20"])
else:
    env.Append(CXXFLAGS=["-std=c++20"])

target_path = "bin/bin/molecule_importer" + env["suffix"] + env["SHLIBSUFFIX"]
dest_dir = os.path.dirname(target_path)
rdkit_root = ARGUMENTS.get("RDKIT_ROOT")
if rdkit_root:
    base_include_path = os.path.join(rdkit_root, "include")
    rdkit_include_path = os.path.join(base_include_path, "rdkit")
    lib_path = os.path.join(rdkit_root, "lib")
    bin_path = os.path.join(rdkit_root, "bin")

    env.Append(CPPDEFINES=["RDKIT_DYN_LINK"])
    env.Append(CPPPATH=[base_include_path, rdkit_include_path])
    env.Append(LIBPATH=[lib_path])
    env.Append(LIBS=["RDKitGraphMol", "RDKitFileParsers", "RDKitRDGeometryLib", "RDKitRDGeneral"])

    dll_patterns = [
        "RDKit*.dll",
        "boost_serialization*.dll",
        "boost_iostreams*.dll",
        "libexpat*.dll",
        "zlib*.dll",
        "libbz2*.dll",
        "zstd*.dll",
    ]
    installed = []
    for pattern in dll_patterns:
        for src in glob.glob(os.path.join(bin_path, pattern)):
            installed.append(env.Install(dest_dir, src))

    if sys.platform == "win32":
        runtime_dlls = ["msvcp140.dll", "vcruntime140.dll", "vcruntime140_1.dll", "vcomp140.dll"]
        for name in runtime_dlls:
            for candidate_dir in [bin_path]:
                candidate = os.path.join(candidate_dir, name)
                if os.path.exists(candidate):
                    installed.append(env.Install(dest_dir, candidate))
                    break
else:
    print("Error: RDKIT_ROOT not found")
    installed = []

lib = env.SharedLibrary(target=target_path, source=sources)
env.Tool('compilation_db')
compiledb = env.CompilationDatabase("compile_commands.json")
env.Alias('compiledb', compiledb)
Default(lib, installed)
