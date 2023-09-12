
# libprintfmt

wrapper for printf functions in C.

overrides fprintf, dprintf, and fprintf.
jcheck the header file for other wrapper functions.

compile with `-DVERBOSITY=5` for highest trace level. file descriptor numbers lower than verbosity gets filtered away.

for user builds, i suggest -DVERBOSITY=2 since this includes stderr, but not anything above it.

## build
```sh
mkdir -p ~/.local/lib/debug
cc -DVERBOSITY=2 -fPIC -shared -o ~/.local/lib/libprintfmt.so printfd.c
cc -DVERBOSITY=2 -fPIC -shared -o ~/.local/lib/debug/libprintfmt.so printfd.c
```

## usage

compile your programs with `-L$(PREFIX)/lib -lprintfmt`, and make sure to `#include <printfd.h>` in them

run your programs with `LD_LIBRARY_PATH=` set to either `~/.local/lib/debug` or `~/.local/lib`

you may want to place the `libprintfmt.so` on a well-known path, or link it statically. up to you tbh


