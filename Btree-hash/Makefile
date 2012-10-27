CC = g++
all: btreehash

btreehash:
	$(CC) -O3 $@.cpp -o $@
run:
	@echo "Running Btree-hash"
	./btreehash
	@echo ""
clean:
	rm btreehash
debug:
	$(CC) -g btreehash.cpp -o btreehash

.PHONY: btreehash clean run debug