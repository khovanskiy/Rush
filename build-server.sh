mkdir target
mkdir target/server
cd target/server
/opt/cmake/bin/cmake -DCMAKE_PREFIX_PATH=/opt/qt/5.5/gcc_64 -DCMAKE_IS_SERVER=True ../../
make all .