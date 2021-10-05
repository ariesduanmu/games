## [Compile](https://www.devdungeon.com/content/compiling-sqlite3-c)

* compile sqlite.exe `gcc sqlite3.c shell.c -o sqlite3`
* compile sqlite.o `gcc sqlite3.c -c`
* compile main: `g++ main.cpp sqlite3.o -I.`