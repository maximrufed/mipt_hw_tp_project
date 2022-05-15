# rm -rf build
rm build/game
mkdir build
cd build
cmake ..
make
./game
