#!/usr/bin/python
#Author: Aaron Rito
#Date: 7/1/17
#Client: CS325 hmwk 1 prob 4

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


with open('data.txt') as f:
	with open('merge.txt',"w") as g:
    		for line in f:
        		numbers = line.strip().split(" ")
			del numbers[0]
			M = merge_sort(numbers)
			g.write("%s\n" % (M))
				
print("See file merge.txt for results")
