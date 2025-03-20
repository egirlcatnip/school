# Dokumentácia k `matrix`

# makefile

```
➜ make O3 # Array 5x5
mkdir -p build
gcc -Wall -Wextra -O0 -c src/matrix.c -o build/matrix.o
gcc -Wall -Wextra -O0 -c src/test.c -o build/test.o
gcc -Wall -Wextra -O0 build/*.o -o matrix.out

➜ ./matrix.out
Matrix 1:
00000.00 00001.00 00002.00 00003.00 00004.00
00010.00 00011.00 00012.00 00013.00 00014.00
00021.00 00022.00 00023.00 00024.00 00025.00
00030.00 00031.00 00032.00 00033.00 00034.00
00040.00 00041.00 00042.00 00043.00 00044.00

Matrix 2:
00099.00 00098.00 00097.00 00096.00 00095.00
00089.00 00088.00 00087.00 00086.00 00085.00
00079.00 00078.00 00077.00 00076.00 00075.00
00069.00 00068.00 00067.00 00066.00 00065.00
00059.00 00058.00 00057.00 00056.00 00055.00

Matrix 1 + Matrix 2:
00099.00 00099.00 00099.00 00099.00 00099.00
00099.00 00099.00 00099.00 00099.00 00099.00
00100.00 00100.00 00100.00 00100.00 00100.00
00099.00 00099.00 00099.00 00099.00 00099.00
00099.00 00099.00 00099.00 00099.00 00099.00

Matrix 1 * Matrix 2:
00690.00 00680.00 00670.00 00660.00 00650.00
04640.00 04580.00 04520.00 04460.00 04400.00
08985.00 08870.00 08755.00 08640.00 08525.00
12540.00 12380.00 12220.00 12060.00 11900.00
16490.00 16280.00 16070.00 15860.00 15650.00

Square root of Matrix 1:
    -nan 00001.00 00001.41 00001.73 00002.00
00003.16 00003.32 00003.46 00003.61 00003.74
00004.58 00004.69 00004.80 00004.90 00005.00
00005.48 00005.57 00005.66 00005.74 00005.83
00006.32 00006.40 00006.48 00006.56 00006.63
```

# Meranie času

## na poli 1000x1000

## `time ./test.out` s `-O0`

```
➜ make O0

➜ time ./matrix.out
...
real	0m6.734s
user	0m6.687s
sys 	0m0.015s
```

## `time ./test.out` s `-O1`

```
➜ make O1

➜ time ./matrix.out
...
real	0m0.968s
user	0m0.950s
sys	  0m0.011s
```

## `time ./test.out` with `-O2`

```
➜ make O2
➜ time ./matrix.out
...
real	0m0.912s
user	0m0.897s
sys 	0m0.010s
```

## `time ./test.out` s `-O3`

```
➜ make O3
➜ time ./matrix.out
...
real	0m0.864s
user	0m0.851s
sys 	0m0.009s
```

## Porovnanie

```
the biggest difference is between -O0 and -O1
-O0 disables all optimatization
-O1 enables some optimatization

difference: 5.766 seconds

other optimatization levels have deminishing results
```

# Záver

```
most time is taken by sqrt(), as it's a more complex operation than addition or multiplication

use -O0 -g when you need maximum information for debugging the program
use -01 to apply quick optimatizations
use -O3 to apply maxium execution speed optimatization, at the cost of compilation speed
```

# makefile

```
preloží matrix zo zdroja pre všetky optimatizačné
```

#
