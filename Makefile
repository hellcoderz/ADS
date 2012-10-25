all: AVLtree Btree AVLtree-hash Btree-hash
	

AVLtree:
	$(MAKE) -C $@ 
Btree:
	$(MAKE) -C $@
AVLtree-hash:
	$(MAKE) -C $@
run:
	$(MAKE) -C AVLtree run
	$(MAKE) -C Btree run
	$(MAKE) -C AVLtree-hash run
	$(MAKE) -C Btree-hash run
clean:
	$(MAKE) -C AVLtree clean
	$(MAKE) -C Btree clean
	$(MAKE) -C AVLtree-hash clean
	$(MAKE) -C Btree-hash run

.PHONY: AVLtree Btree AVLtree-hash Btree-hash clean run