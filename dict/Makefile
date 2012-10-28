SOURCES = avltree avlhash btree btreehash rbtree rbhash dictionary
EXT = cpp
EXE = exe

all: $(SOURCES)
	
$(SOURCES):
	g++ -O3 $@.$(EXT) -o $@

run:
	./dictionary
clean:
	rm $(SOURCES)

.PHONY: avltree avlhash btree btreehash rbtree rbhash dictionary clean run