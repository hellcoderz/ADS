all: AVLtree Btree
	$(SUBDIRS)

AVLtree:
	$(MAKE) -C $@ 
Btree:
	$(MAKE) -C $@
run:
	@echo "running AVLtree"
	AVLtree/avltree
	@echo ""
	@echo "running Btree"
	Btree/btree
	@echo ""

.PHONY: AVLtree Btree clean run