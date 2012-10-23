all: AVLtree Btree
	$(SUBDIRS)

AVLtree:
	$(MAKE) -C $@ 
Btree:
	$(MAKE) -C $@
run:
	@echo "running AVLtree"
	AVLtree/avltree
	@echo "running Btree"
	Btree/btree

.PHONY: AVLtree Btree clean run