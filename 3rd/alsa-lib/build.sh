#
# build pc
#./configure --prefix="$PWD/../../usr" --disable-shared

# cross build
./configure --prefix="$PWD/../../usr" --disable-shared --target=arm-linux --host=arm-linux
make V=1
make install

