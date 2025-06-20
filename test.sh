./run.sh
chmod +x build/ccinit
cp build/ccinit ../..
./../../cci tmp_test_project
rm -rf ../../tmp_test_project