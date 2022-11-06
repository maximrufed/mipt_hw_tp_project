rm -f build/game
mkdir -p build; cd build
cmake ..
make
./game
