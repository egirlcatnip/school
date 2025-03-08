all: avl_tree matrix mytar libs

avl_tree:
	$(MAKE) -C hw/avl_tree

matrix:
	$(MAKE) -C hw/matrix

mytar:
	$(MAKE) -C hw/mytar

libs:
	$(MAKE) -C hw/libs



pack: clean mkdir
	tar -cvJf out/avl_tree.tar.xz  -C hw/ avl_tree
	tar -cvJf out/matrix.tar.xz    -C hw/ matrix
	tar -cvJf out/mytar.tar.xz     -C hw/ mytar
	tar -cvJf out/libs.tar.xz      -C hw/ libs

mkdir:
	mkdir -p out

clean:
	$(MAKE) -C hw/avl_tree clean
	$(MAKE) -C hw/matrix clean
	$(MAKE) -C hw/mytar clean
	$(MAKE) -C hw/libs clean
	rm -rf out

