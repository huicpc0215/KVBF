objects=main.o BloomFilter.o BloomFilterCell.o 
INCLUDE=headers:src
main: main.o BloomFilterCell.o BloomFilter.o
	g++ $(objects) -o main

main.o: main.cpp main.h
	g++ -l$(INCLUDE) -c main.cpp -o main.o

BloomFilter.o: BloomFilter.cpp BloomFilter.h
	g++ -l$(INCLUDE) -c BloomFilter.cpp -o BloomFilter.o

BloomFilterCell.o: BloomFilterCell.cpp BloomFilterCell.h
	g++ -l$(INCLUDE) -c BloomFilterCell.cpp -o BloomFilterCell.o

clean:
	rm $(objects)

	
