#!/bin/bash

for file in ./tracks/*.in; do
    filename="${file%.*}"
    echo $filename
    time ./a.exe < $filename.in
done
