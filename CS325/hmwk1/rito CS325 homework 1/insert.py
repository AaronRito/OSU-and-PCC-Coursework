#Author: Aaron Rito
#Date: 7/1/17
#Client: CS325 hwmk1 prob 4

def insertionsort(A):
    for j in range(1,len(A)):
        key = A[j] 
        i = j-1 
        while (i > -1) and key < A[i]: 
            A[i+1]=A[i] 
            i=i-1 
        A[i+1] = key
    return A

with open('data.txt') as f:
        with open('insert.txt',"w") as g:
                for line in f:
                        numbers = map(int, line.strip().split(" "))
                        M = insertionsort(numbers)
                        g.write("%s\n" % (M))

print("See file insert.txt for results")

