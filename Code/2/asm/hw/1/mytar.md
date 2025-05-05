# Dokumentácia k `mytar`

# Použitie

### `mytar` bez argumentov

vypíše nápovedu

```
➜ mytar
Usage:
        mytar --list <tar>
        mytar -l <tar>
        mytar --cat <tar> [<filename> ...]
        mytar -x <tar> [<filename> ...]
```

---

### `mytar -l`

vypíše obsah tar súboru

```
➜ mytar --list <tar>

➜ mytar -l <tar>
```

---

### `mytar -x`

vypíše obsah súboru/súborov z tar súboru

```
➜ mytar --cat <tar> <filename> [<filename> ...]

➜ mytar -x <tar> <filename> [<filename> ...]
```

# Implementácia

## Použité knižnice

`stdbool.h`:

```
true, false
```

---

`stdio.h`:

```
printf(), fprintf()
fopen(), fclose()
fread(), fseek(), rewind()
NULL
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
strcmp(), memcpy()
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

`return podľa úspešnosti operácie`

```
EXIT_SUCCESS -> úspešné ukončenie
EXIT_FAILURE -> chyba pri operácii
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
```

`cat_files()`:

```
otvorí súbor
čita `tar_file` po 512B
ak niesu špecifikované súbory, vypíše obsah všetkých súborov
inak vypíše obsah špecifikovaných súborov
skočí na začiatok ďalšieho súboru
opakuje pre všetky súbory
ak súbor nebol nájdený, vypíše chybu
zatvorí súbor
```

`usage()`:

```
vypíše nápovedu:
```

```
Usage:
        mytar --list <tar>
        mytar -l <tar>
        mytar --cat <tar> [<filename> ...]
        mytar -x <tar> [<filename> ...]
```

# makefile

```
preloží mytar zo zdroja
vytvorí .tar súbor obsahuji 1.dat 2.dat 3.dat
```

#
