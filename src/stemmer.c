/**
  Copyright (c) 2023 Wolfgang Hauptfleisch <wh@augmentedlogic.com>

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
 **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <lua.h>
#include <lauxlib.h>
#include <libstemmer.h>

#define luaL_reg luaL_Reg
#define INC 10


static int l_stem(lua_State *L)
{
    char *charenc = NULL;
    size_t l;
    const char *input = luaL_checklstring(L, 1, &l);
    const char *language = luaL_checklstring(L, 2, &l);


    //char * language = "english";
    struct sb_stemmer * stemmer;
    stemmer = sb_stemmer_new(language, charenc);
    if (stemmer == 0) {
       fprintf(stderr, "language `%s' not available\n", language);
    }

    // check or nil? sb_stemmer_length(stemmer) > 0

    // signage check
    sb_symbol * b = input;
    // string to lower
    for(int i = 0; b[i]; i++){
      b[i] = tolower(b[i]);
    }


    int i = strlen(input);
    const sb_symbol *stemmed = sb_stemmer_stem(stemmer, b, i);
    const char *stemmed_s = stemmed;
    if (stemmed == NULL)
                {
                    fprintf(stderr, "Out of memory");
                    exit(1);
                }
    else {
       lua_pushstring(L, stemmed_s);
       sb_stemmer_delete(stemmer);
    }

    return 1;
}

// lua5.2 or newer
#if LUA_VERSION_NUM >= 502
static const struct luaL_Reg stemmer [] = {
    {"stem", l_stem},
    {NULL, NULL}
};
#endif

#if LUA_VERSION_NUM >= 502
int luaopen_stemmer(lua_State *L) {
    luaL_newlib(L, stemmer);
    return 1;
}
#endif


// 5.1
#if LUA_VERSION_NUM == 501

static const luaL_Reg lib[] = {
    {"stem", l_stem},
    {NULL, NULL}
};

#endif

// 5.1
#if LUA_VERSION_NUM == 501

LUALIB_API int luaopen_stemmer(lua_State *L) {
    luaL_register(L, "stem", lib);
    return 1;
}
#endif

