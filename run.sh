# rm -rf build
rm build/game
mkdir -p build; cd build
cmake ..
make
./game
