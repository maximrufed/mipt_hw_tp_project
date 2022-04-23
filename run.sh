# rm -rf build
rm build/main
mkdir build
cd build
cmake ..
make
./main
