./run.sh
chmod +x build/cci
cp build/cci ../..
./../../cci test
rm -rf ../../test