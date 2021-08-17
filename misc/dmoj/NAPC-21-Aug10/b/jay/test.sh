for i in {1..100}
do
  yes $1 | ./gen > t1
  ./b < t1 > myout
  ./brute < t1 > sysout
  if ! diff myout sysout; then
    break
  fi
done
