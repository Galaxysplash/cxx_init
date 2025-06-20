./run.sh
chmod +x build/cci_exec
cp build/cci_exec ../..
./../../cci_exec tmp_test_project
rm -rf ../../tmp_test_project