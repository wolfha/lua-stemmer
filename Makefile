#
# Makefile for lua-stemmer
#
LUA=lua5.2

default:
	gcc -c -fPIC -Wpointer-sign -Wno-implicit-function-declaration -Wall -lstemmer -l$(LUA) -I/usr/include/$(LUA) src/stemmer.c -o src/lua-stemmer.o
	gcc -fPIC -Wl,-soname,lib$(LUA)-stemmer.so.0 -Wall -lstemmer -l$(LUA) -I/usr/include/$(LUA) src/lua-stemmer.o -o src/stemmer.so -shared

deb:
	$(eval LUA=lua5.1)
	gcc -c -fPIC -Wpointer-sign -Wno-implicit-function-declaration -Wall -lstemmer -l$(LUA) -I/usr/include/$(LUA) src/stemmer.c -o src/$(LUA)-stemmer.o
	gcc -fPIC -Wl,-soname,lib$(LUA)-stemmer.so.0 -Wall -lstemmer -l$(LUA) -I/usr/include/$(LUA) src/$(LUA)-stemmer.o -o src/lib$(LUA)-stemmer.so.0.0.0 -shared
	$(eval LUA=lua5.2)
	gcc -c -fPIC -Wpointer-sign -Wno-implicit-function-declaration -Wall -lstemmer -l$(LUA) -I/usr/include/$(LUA) src/stemmer.c -o src/$(LUA)-stemmer.o
	gcc -fPIC -Wl,-soname,lib$(LUA)-stemmer.so.0 -Wall -lstemmer -l$(LUA) -I/usr/include/$(LUA) src/$(LUA)-stemmer.o -o src/lib$(LUA)-stemmer.so.0.0.0 -shared
	$(eval LUA=lua5.3)
	gcc -c -fPIC -Wpointer-sign -Wno-implicit-function-declaration -Wall -lstemmer -l$(LUA) -I/usr/include/$(LUA) src/stemmer.c -o src/$(LUA)-stemmer.o
	gcc -fPIC -Wl,-soname,lib$(LUA)-stemmer.so.0 -Wall -lstemmer -l$(LUA) -I/usr/include/$(LUA) src/$(LUA)-stemmer.o -o src/lib$(LUA)-stemmer.so.0.0.0 -shared


clean:
	rm -f src/*.0
	rm -f src/*.so
	rm -f src/*.o

