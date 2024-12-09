TARGET_DIR="/usr/local"

mkdir -p $TARGET_DIR
cp ./src/main $TARGET_DIR/bin/guess
cp -r ./src/ru $TARGET_DIR/bin/
mkdir -p $TARGET_DIR/share/man/man1
cp ./doxygen-doc/man/man1/guess.c.1 $TARGET_DIR/share/man/man1/guess.1