rm -rf build
cmake . -B build
make -C build
rm -rf tmp_test_project
rm -rf build