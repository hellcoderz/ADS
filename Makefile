all: AVLtree AVLtree-hash Btree Btree-hash RBtree RBtree-hash
	

AVLtree:
	$(MAKE) -C $@ 
Btree:
	$(MAKE) -C $@
AVLtree-hash:
	$(MAKE) -C $@
RBtree-hash:
	$(MAKE) -C $@
Btree-hash:
	$(MAKE) -C $@
RBtree:
	$(MAKE) -C $@
run:
	$(MAKE) -C AVLtree run
	$(MAKE) -C Btree run
	$(MAKE) -C AVLtree-hash run
	$(MAKE) -C Btree-hash run
	$(MAKE) -C RBtree-hash run
	$(MAKE) -C RBtree run
clean:
	$(MAKE) -C AVLtree clean
	$(MAKE) -C Btree clean
	$(MAKE) -C AVLtree-hash clean
	$(MAKE) -C Btree-hash clean
	$(MAKE) -C RBtree-hash clean
	$(MAKE) -C RBtree clean

.PHONY: AVLtree Btree AVLtree-hash Btree-hash RBtree-hash RBtree clean run