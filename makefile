all: compile run

compile:
	g++ -I ./include/ -o ./lib/HuffmanNode.o -c ./src/HuffmanNode.cpp
	g++ -I ./include/ -o ./lib/HuffmanTree.o -c ./src/HuffmanTree.cpp
	g++ -I ./include/ -o ./bin/test ./lib/HuffmanTree.o ./lib/HuffmanNode.o ./src/main.cpp
	
run:	
	./bin/test