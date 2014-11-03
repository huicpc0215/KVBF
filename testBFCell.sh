g++ -c ./testBFCell.cpp -I ./headers/
g++ -c ./src/BloomFilterCell.cpp -I ./headers/
g++ testBFCell.o BloomFilterCell.o -o test
./test
