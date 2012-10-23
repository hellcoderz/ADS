all: AVLtree Btree
	$(SUBDIRS)

AVLtree:
	$(MAKE) -C $@ 
Btree:
	$(MAKE) -C $@
run:
	$(MAKE) -C AVLtree run
	$(MAKE) -C Btree run
clean:
	$(MAKE) -C AVLtree clean
	$(MAKE) -C Btree clean

.PHONY: AVLtree Btree clean run