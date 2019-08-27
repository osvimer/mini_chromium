#!/bin/bash

GN_BIN=depot_tools/gn
OUTDIR=out/r
NINJA=depot_tools/ninja

$GN_BIN gen --check $OUTDIR
$NINJA -C $OUTDIR
