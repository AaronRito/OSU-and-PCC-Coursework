#Author: Aaron Rito
#Date: 7/15/17
#Client: CS325 hmwk 4 prob 4

import time
#this function finds the least number of coins needed to make change.
#passing in the denomination list, the amount to change,
# the length of the denom list, and an array to hold the values used
def dpMakeChange(coinValueList,change,minCoins,coinsUsed):  
    current_time = time.time()                             #note the time
    for cents in range(change+1):                          #loop through the amount and make some 1 cent coins. 
        coinCount = cents
        newCoin = 1
        for j in [c for c in coinValueList if c <= cents]: #loop through the coin values and match up with the amount
            if minCoins[cents-j] + 1 < coinCount:          #starting at 1, add coins until the check if the goal has been reached
                coinCount = minCoins[cents-j]+1            #coinCount holds the solutions
                newCoin = j                                #update the coin to the value next in the list
        minCoins[cents] = coinCount                        #holds the number of coins used
        coinsUsed[cents] = newCoin                         #holds the list of coins used
    elapsed_time = current_time - time.time()              #note the time
    print elapsed_time, 'seconds'                          #show the time 
    return minCoins[change]                                #return the number of coins needed 

    
#this function prints the coins used, and how many of them
#it also writes the data to a file in a strange format.
#no more comments as code is straightforward/human readable. 
def printCoins(coinsUsed, c_list, change):                  
    coin = change
    coin_list = []
    counter = 0
    while coin > 0:  
        thisCoin = coinsUsed[coin]
        print(thisCoin)
        coin_list.insert(counter, thisCoin)
        coin = coin - thisCoin
        counter += 1
    print(coin_list)
    val_list = []
    val_index = 0
    val_count = 0
    for i in range (0, len(c_list)):
        for j in range (0, len(coin_list)):
            if coin_list[j] == c_list[i]:       #this nested loop finds how many of each coin was used.
                val_count += 1                  #if the coin matches one from the list, increase the counter.
        val_list.insert(val_index, val_count) 
        val_count = 0
        val_index += 1
        val_size = len(val_list)
    print(val_list)
    with open('change.txt', "a") as outfile:    #write the data with no commas or deliminaters. 
        outfile.write("%s\n" % (c_list))
        outfile.write("%s\n" % (change))
        outfile.write("%s\n" % (val_list))
        outfile.write("%s\n" % (val_size))
        outfile.write("\n")       

# the code to drive the functions
amnt = [None]
even_odd_flag = 0
two_line_flag = 0
with open('amount.txt') as infile:
        for line in infile:
            if not even_odd_flag:                                          # if it's an even line, it's the coin value data...
                clist = map(int, line.strip().split(" "))
                even_odd_flag = 1
            else:                                                          # if it's an odd line, it's the amount to make change for....
                a = map(int, line.strip().split(" "))
                amnt = a[0]
                print(amnt)
                even_odd_flag = 0
                two_line_flag = 1
                coinsUsed = [0]*(amnt+1)
                coinCount = [0]*(amnt+1)
            if two_line_flag:                                              # the program read two lines, now process the data and continue to the next set...
                print "Making change for",amnt,"requires"
                print dpMakeChange(clist,amnt,coinCount,coinsUsed),"coins"
                print"They are:"
                printCoins(coinsUsed,clist, amnt)
                two_line_flag = 0

print('See file "change.txt" for formatted results.')
