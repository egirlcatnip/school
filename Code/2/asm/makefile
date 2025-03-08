all: clean avl_tree matrix mytar libs git_remove_ignored pack

avl_tree:
	$(MAKE) -C hw/avl_tree

matrix:
	$(MAKE) -C hw/matrix

mytar:
	$(MAKE) -C hw/mytar

libs:
	$(MAKE) -C hw/libs

pack: mkdir
	tar -cvJf packed/avl_tree.tar.xz -C hw/ avl_tree
	tar -cvJf packed/matrix.tar.xz   -C hw/ matrix
	tar -cvJf packed/mytar.tar.xz    -C hw/ mytar
	tar -cvJf packed/libs.tar.xz     -C hw/ libs

mkdir:
	mkdir -p packed

clean:
	$(MAKE) -C hw/avl_tree clean
	$(MAKE) -C hw/matrix clean
	$(MAKE) -C hw/mytar clean
	$(MAKE) -C hw/libs clean
	rm -rf packed

git_remove_ignored:
	git rm -r --cached hw/avl_tree
	git rm -r --cached hw/matrix
	git rm -r --cached hw/mytar
	git rm -r --cached hw/libs