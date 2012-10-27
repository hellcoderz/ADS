SOURCES = avltree avlhash btree btreehash rbtree rbhash dictionary
EXT = cpp
EXE = exe

all: $(SOURCES)
	
avltree:
	g++ -O3 $@.cpp -o avltree
avlthash:
	g++ -O3 $@.cpp -o avlhash
btree:
	g++ -O3 $@.cpp -o btree
btreehash:
	g++ -O3 $@.cpp -o btreehash
rbtree:
	g++ -O3 $@.cpp -o rbtree
rbhash:
	g++ -O3 $@.cpp -o rbhash
dictionary:
	g++ -O3 $@.cpp -o dictionary

run:
	./dictionary
clean:
	rm $(SOURCES)

.PHONY: avltree avlhash btree btreehash rbtree rbhash dictionary clean run