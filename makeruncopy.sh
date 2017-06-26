g++ converter.cpp -o converter
./converter $1
rm converter
cat melody.ino | pbcopy
