rm -f include/*.h
file2str build.py build_py.h
file2str CMakeLists.txt CMakeLists_txt.h
file2str .gitignore dot_gitignore.h
file2str conanfile.txt conanfile_txt.h
file2str README.md README_md.h
mkdir include
mv *.h* include
