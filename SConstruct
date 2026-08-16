import os
import sys
import glob

env = SConscript("godot-cpp/SConstruct")
sources = Glob("src/*.cpp")
env.Tool('compilation_db')
env.Alias('compiledb', env.CompilationDatabase('compile_commands.json'))

if sys.platform == "win32":
    env.Append(CXXFLAGS=["/std:c++20"])
else:
    env.Append(CXXFLAGS=["-std=c++20"])

target_path = "bin/bin/molecule_importer" + env["suffix"] + env["SHLIBSUFFIX"]
dest_dir = os.path.dirname(target_path)

conda_prefix = os.environ.get("CONDA_PREFIX")
if conda_prefix:
    base_include_path = os.path.join(conda_prefix, "Library", "include")
    rdkit_include_path = os.path.join(base_include_path, "rdkit")
    conda_lib_path = os.path.join(conda_prefix, "Library", "lib")
    conda_bin_path = os.path.join(conda_prefix, "Library", "bin")

    env.Append(CPPDEFINES=["RDKIT_DYN_LINK"])
    env.Append(CPPPATH=[base_include_path, rdkit_include_path])
    env.Append(LIBPATH=[conda_lib_path])
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
        for src in glob.glob(os.path.join(conda_bin_path, pattern)):
            installed.append(env.Install(dest_dir, src))

    if sys.platform == "win32":
        runtime_dlls = ["msvcp140.dll", "vcruntime140.dll", "vcruntime140_1.dll", "vcomp140.dll"]
        for name in runtime_dlls:
            for candidate_dir in (conda_prefix, conda_bin_path):
                candidate = os.path.join(candidate_dir, name)
                if os.path.exists(candidate):
                    installed.append(env.Install(dest_dir, candidate))
                    break
else:
    print("Error: CONDA_PREFIX environment variable not found. Is your environment activated?")
    installed = []

lib = env.SharedLibrary(target=target_path, source=sources)
Default(lib)
Default(installed)
