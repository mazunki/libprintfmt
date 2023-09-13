
# libprintfmt

wrapper for printf functions in C.

supports more file descriptors than only stdout and stderr. puts everything on stdout with known prefixes and colours

overrides fprintf, dprintf, and fprintf.
check the header file for other wrapper functions.

compile with `-DVERBOSITY=5` for highest trace level. file descriptor numbers lower than verbosity gets filtered away.

for user builds, i suggest -DVERBOSITY=2 since this includes stderr, but not anything above it.

## build
```sh
: ${PREFIX:=${HOME:?}/.local}
mkdir -p "${PREFIX}/lib/debug"
cc -DVERBOSITY=2 -fPIC -shared -lncurses -o ${PREFIX}/lib/libprintfmt.so printfd.c
cc -DVERBOSITY=5 -fPIC -shared -lncurses -o ${PREFIX}/lib/debug/libprintfmt.so printfd.c
```

we build with ncurses to check for colours, it's usually installed anyway, so eh

alternatively you can slap on `-DNO_COLOR` to just disable colours altogether, which doesn't need ncurses; or specify `-DFORCE_COLOR=8` to hardcode in support for 8 colours (which is what we need for our thing anyway)

## usage

compile your programs with `-L$(PREFIX)/lib -lprintfmt`, and make sure to `#include <printfd.h>` in them

run your programs with `LD_LIBRARY_PATH=` set to either `${PREFIX}/lib/debug` or `${PREFIX}/lib` or whatever

you may want to place the `libprintfmt.so` on a well-known path, or link it statically. up to you tbh

## showcase

![example screenshot](./screenshot.png)

