#!/bin/sh
set -e

mkdir -p ~/.local/lib
cc -DVERBOSITY="${VERBOSITY:-5}" -fPIC -shared -lncurses -o ~/.local/lib/libprintfmt.so printfd.c

