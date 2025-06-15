clear
rm -rf build
git add -f *
git commit -a -m "..."
git push -f
./run.sh
./test.sh