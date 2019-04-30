#!/bin/bash
while [ true ]
do
    ./gen.exe > t1
    ./brute.exe < t1 > sys
    ./C.exe < t1 > my
    diff my sys
done
