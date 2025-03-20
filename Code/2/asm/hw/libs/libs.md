# Dokumentácia k `gonio`

# Použitie

### `gonio` bez argumentov

vypíše nápovedu

```
➜ gonio
Usage:
        gonio sin <degrees>
        gonio cos <degrees>
        gonio tan <degrees>
```

---

### `gonio sin` vypíše sin(degrees)

```
➜ gonio sin 90
sin(90°) = 1.000000
```

---

### `gonio sicosn` vypíše cos(degrees)

```
➜ gonio cos 90
cos(90°) = 0.000000
```

---

### `gonio sin` vypíše tan(degrees)

```
➜ gonio tan 45
tan(45°) = 1.000000
```

# `gonio_dynamic` a `gonio_static`

```
➜ ldd ./gonio_dynamic.out
        linux-vdso.so.1 (0x00007737db81a000)
        libm.so.6 => /lib64/libm.so.6 (0x00007737db711000)
        libc.so.6 => /lib64/libc.so.6 (0x00007737db51e000)
        /lib64/ld-linux-x86-64.so.2 (0x00007737db81c000)

➜ ldd ./gonio_static.out
        not a dynamic executable
```

# `matrix_dynamic_tes` a `matrix_static_test`

```
➜ ldd ./out/matrix_dynamic_test.out
        linux-vdso.so.1 (0x00007e92e13ae000)
        libmatrix.so => lib/libmatrix.so (0x00007e92e13a3000)
        libm.so.6 => /lib64/libm.so.6 (0x00007e92e12a0000)
        libc.so.6 => /lib64/libc.so.6 (0x00007e92e10ad000)
        /lib64/ld-linux-x86-64.so.2 (0x00007e92e13b0000)

➜ ldd ./out/matrix_static_test.out
        not a dynamic executable
```

### vytvorené pomocou `libmatrix.so` a `libmatrix.a`

# makefile

```
preloží knižnice libmatrix.so a libratrix.a zo zdroja
preloží matrix_dynamic_test a matrix_static_test zo zdroja

pre matrix_dynamic_test je potrebné nastaviť cestu k dynamickej knižnici, ak nie je v systémových cestách
eg. ./lib

➜ ls ./lib
libmatrix.so
```

```
➜ LD_LIBRARY_PATH=../lib ldd ./matrix_dynamic_test.out
	linux-vdso.so.1 (0x000074a01975b000)
	libmatrix.so => ../lib/libmatrix.so (0x000074a019750000)
	libm.so.6 => /lib64/libm.so.6 (0x000074a01964d000)
	libc.so.6 => /lib64/libc.so.6 (0x000074a01945a000)
	/lib64/ld-linux-x86-64.so.2 (0x000074a01975d000)
```

preloží gonio_dynamic zo zdroja (dynamická knižnica math) preloží gonio_static
zo zdroja (statická knižnica math)

```
#
```
