all: AVLtree Btree AVLtree-hash
	$(SUBDIRS)

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
clean:
	$(MAKE) -C AVLtree clean
	$(MAKE) -C Btree clean
	$(MAKE) -C AVLtree-hash clean

.PHONY: AVLtree Btree AVLtree-hash clean run