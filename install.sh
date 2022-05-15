rm -rf build
mkdir build; cd build
cmake .. -DCMAKE_INSTALL_PREFIX=$1
make
make install
