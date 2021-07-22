#!/bin/bash

FC=$1

if [[ "$CC" == "verificarlo-f" && "$FC" == "verificarlo-f" ]]; then
    VFC_CI="-DVFC_CI -lvfc_probes -lvfc_probes_f"
else
    VFC_CI=""
fi

# Make vfc_probes.o and copy header
# cp tools/qmckl_probes.h src/qmckl_probes.h
# cp tools/qmckl_probes.c src/qmckl_probes.c
# $CC -c -fPIC src/qmckl_probes.c -o src/qmckl_probes.o $VFC_CI
# $CC -shared -o src/qmckl_probes.so src/qmckl_probes.o

# Build Fortran module
echo "Building qmckl_probes_f module..."
cp tools/qmckl_probes_f.f90 src/qmckl_probes_f.f90
$FC -c src/qmckl_probes_f.f90 -o src/qmckl_probes_f.o $VFC_CI
