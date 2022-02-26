#!/bin/bash

N=500
Q=3000
B=1000000000

tst=0
ret=0
while [ true ] ; do
  tst=$((tst + 1))
  echo "Trying test $tst..."
  echo "$N $Q $B" | ./gen > t1
  ./sol < t1 > my
  ./brute < t1 > sys
  diff my sys
  ret=$?
  if [ $ret -eq 0 ]; then
    echo "OK"
  else
    echo "Failed"
    break
  fi
done
