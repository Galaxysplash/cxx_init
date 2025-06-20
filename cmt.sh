clear
./refresh
rm -rf build
git add -f *
git commit -a -m "..."
git push -f
./test.sh