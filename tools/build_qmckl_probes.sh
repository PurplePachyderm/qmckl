#!/bin/bash

CC=$1
FC=$2
VFC_CI=$3

echo $CC
echo $FC
echo $VFC_CI

if [[ "$VFC_CI" == "true" ]]; then
  VFC_CI="-D VFC_CI"

else
  VFC_CI=""
fi

echo $VFC_CI

# Make vfc_probes.o and copy header
$CC -c -fPIC tools/qmckl_probes.c -o src/qmckl_probes.o $VFC_CI
cp tools/qmckl_probes.h src/qmckl_probes.h

# Build Fortran module
$FC -c tools/qmckl_probes_f.f90 -o src/qmckl_probes_f.o $VFC_CI
