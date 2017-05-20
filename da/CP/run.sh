make
./prog learn --input learn --output stat
./prog classify --stats stat --input class --output resultfile
cat resultfile
make clear
