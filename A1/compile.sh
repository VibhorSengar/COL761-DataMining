CXX="g++"
CXXFLAGS="-std=c++11 -O2"

$CXX $CXXFLAGS -o encrypt -I . fptree.cpp encrypt.cpp

$CXX $CXXFLAGS decrypt.cpp -o decrypt
