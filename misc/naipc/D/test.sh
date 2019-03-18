#!/bin/sh

while [ 1 ]
do
    ./gen > t1
    b=$(./D < t1)
    echo $b
done

