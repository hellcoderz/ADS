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

.PHONY: btreehash clean