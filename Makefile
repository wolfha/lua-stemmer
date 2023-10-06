#
# Makefile for lua-stemmer
#
LUA=lua5.2

default:
	gcc -c -fPIC -Wpointer-sign -Wno-implicit-function-declaration -Wall -lstemmer -l$(LUA) -I/usr/include/$(LUA) src/stemmer.c -o src/lua-stemmer.o
	gcc -fPIC -Wl,-soname,lib$(LUA)-stemmer.so.0 -Wall -lstemmer -l$(LUA) -I/usr/include/$(LUA) src/lua-stemmer.o -o src/stemmer.so -shared

clean:
	rm -f src/*.0
	rm -f src/*.so
	rm -f src/*.o

