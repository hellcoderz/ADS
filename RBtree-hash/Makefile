CC = g++
all: rbhash

rbhash:
	$(CC) -O3 $@.cpp -o $@
run:
	@echo "Running RBtree-hash"
	./rbhash
	@echo ""
clean:
	rm rbhash

.PHONY: rbhash clean