#!/bin/sh
set -e

mkdir -p ~/.local/lib
cc -DVERBOSITY="${VERBOSITY:-5}" -fPIC -shared -o ~/.local/lib/libprintfmt.so printfd.c

