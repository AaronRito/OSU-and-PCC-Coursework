#Author: Aaron Rito
#Date: 7/1/17
#Client: CS325 hwmk2 prob 5

import sys

sys.setrecursionlimit(40000)

def stoogesort(L, i=0, j=None):
  if j is None:
    j = len(L) - 1
  if L[j] < L[i]:
    L[i], L[j] = L[j], L[i]
  if j - i > 1:
    t = (j - i + 1) // 3
    stoogesort(L, i  , j-t)
    stoogesort(L, i+t, j  )
    stoogesort(L, i  , j-t)
  return L
  

with open('data.txt') as f:
        with open('stooge.out',"w") as g:
                for line in f:
                        numbers = map(int, line.strip().split(" "))
                        M = stoogesort(numbers)
                        g.write("%s\n" % (M))

print("See file stooge.out for results")

