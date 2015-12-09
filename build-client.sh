mkdir target
mkdir target/client
cd target/client
/opt/cmake/bin/cmake -DCMAKE_PREFIX_PATH=/opt/qt/5.5/gcc_64 -DCMAKE_IS_SERVER=False ../../
make all .