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

### `gonio sin`
vypíše sin(degrees)
```
➜ gonio sin 90
sin(90°) = 1.000000
```

---

### `gonio sicosn`
vypíše cos(degrees)
```
➜ gonio cos 90
cos(90°) = 0.000000
```

---

### `gonio sin`
vypíše tan(degrees)

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



# Dokumentácia k `matrix.so` a `matrix.a`

