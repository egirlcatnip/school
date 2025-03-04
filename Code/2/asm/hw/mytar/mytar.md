# Dokumentácia k `mytar`

# 1. Použitie

### `mytar` bez argumentov
vypíše nápovedu

```
➜ mytar
Usage:
        mytar --list <tar>
        mytar -l <tar>
        mytar --cat <tar> <filename> [<filename> ...]
        mytar -x <tar> <filename> [<filename> ...]
```

---

### `mytar -l `
vypíše obsah tar súboru

```
➜ mytar --list <tar>
alebo
➜ mytar -l <tar>
```

---

### `mytar -x `
vypíše obsah súboru/súborov z tar súboru


```
➜ mytar --cat <tar> <filename> [<filename> ...]
alebo
➜ mytar -x <tar> <filename> [<filename> ...]
 ```

---

# 2. Implementácia

## Použité knižnice
`stdbool.h`:

```
true, false
```

---

`stdio.h`:

```
printf()
fopen(), fclose()
fread(), fseek(), rewind()
```

---

`stdlib.h`:

```
malloc(), free(), strtol()
exit(), EXIT_SUCCESS, EXIT_FAILURE
```

---

`string.h`:

```
strcmp()
```

## Control flow

### Enum Operacia:
```
INVALID, LIST, CAT
```

```
Výber pomocou strcmp()
```

---

`Switch pre operácie`

`LIST`:
```
 list_files() - vypíše obsah tar súboru
```

`CAT`:
```
cat_files() - vypíše obsah súboru/súborov z tar súboru
```

`INVALID`:
```
vypíše nápovedu
```

---

## Funkcie

`list_files()`:
```
otvorí súbor
čita `tar_file` po 512B
vypíše názov súboru
skočí na začiatok ďalšieho súboru
opakuje pre všetky súbory
zatvorí súbor
ak nedošlo k chybe, return EXIT_SUCCESS
```

`cat_files()`:
```
otvorí súbor
čita `tar_file` po 512B
ak je súbor v argumentoch, vypíše obsah
skočí na začiatok ďalšieho súboru
opakuje pre všetky súbory
ak súbor nebol nájdený, vypíše chybu
zatvorí súbor
ak nedošlo k chybe, return EXIT_SUCCESS
```

`usage()`:
```
vypíše nápovedu:

Usage:
        mytar --list <tar>
        mytar -l <tar>
        mytar --cat <tar> <filename> [<filename> ...]
        mytar -x <tar> <filename> [<filename> ...]

```

#