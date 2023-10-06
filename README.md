# lua-stemmer

This is a lua binding to libstemmer.

```
local stemmer = require("stemmer");

local r = stemmer.stem("Programmers", "english");
print(r)
```
