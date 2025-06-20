clear
./gen.sh
./refresh
rm -rf build
git add -f *
git commit -a -m "..."
git push -f
./install.sh
./test.sh