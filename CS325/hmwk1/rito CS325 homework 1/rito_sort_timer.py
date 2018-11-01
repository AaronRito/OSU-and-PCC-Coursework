#Author Aaron Rito
#Date: 7/1/17
#Client: Cs325 homework 1 problem 5
import time
import random
import sys

sys.setrecursionlimit(40000)

def sort_timer(A):
        X = [random.random() for i in range(A)]
        start_time = time.time()
        insertionsort(X)
        elapsed_time = start_time - time.time()
        print('n = ' "%s" % (A), 't = ' "%s" % (elapsed_time))


def merge_timer(A):
        X = [random.random() for i in range(A)]
        start_time = time.time()
        merge_sort(X)
        elapsed_time = start_time - time.time()
        print('n = ' "%s" % (A), 't = ' "%s" % (elapsed_time))
        
def stooge_timer(A):
        X = [random.random() for i in range(A)]
        start_time = time.time()
        stoogesort(X)
        elapsed_time = start_time - time.time()
        print('n = ' "%s" % (A), 't = ' "%s" % (elapsed_time))
        
        
def insertionsort(A):
    for j in range(1,len(A)):
        key = A[j]
        i = j-1
        while (i > -1) and key < A[i]:
            A[i+1]=A[i]
            i=i-1
        A[i+1] = key
    return A
        
def merge_sort(lst):

    if len(lst) <= 1:
        return lst
    mid = len(lst) // 2
    left = merge_sort(lst[:mid])
    right = merge_sort(lst[mid:])
    return merge(left, right)
    

def merge(left, right):

    if not left:
        return right
    if not right:
        return left
    if left[0] < right[0]:
        return [left[0]] + merge(left[1:], right)
    return [right[0]] + merge(left, right[1:])
    
    
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


M = [10,20,50,100,200,350,500]
print("Insertion sort speed per n:")
for i in M:
        sort_timer(i)

print("Merge sort speed per n:")
for j in M:
        merge_timer(j)

print("Stooge sort speed per n:")        
for k in M:
        stooge_timer(k)
