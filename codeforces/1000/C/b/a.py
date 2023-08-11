import heapq
import sys

t = int(sys.stdin.readline().strip())

heap = []

heapq.heapify(heap)

d = {}

for i in range(t):
  inputs = [int(x) for x in sys.stdin.readline().strip().split()]
  l = inputs[0]
  r = inputs[1]

  heapq.heappush(heap, (l, 1))
  heapq.heappush(heap, (r + 1, -1))

  d[i] = 0

d[t] = 0

cnt = 0

idx, c = heapq.heappop(heap)
start = idx
cnt += c

while(heap):
  idx, c = heapq.heappop(heap)
  d[cnt] += idx - start
  cnt += c
  start = idx

s = ""

for k, v in d.items():
  if k > 0:
    s += str(v) + " "

print(s)

