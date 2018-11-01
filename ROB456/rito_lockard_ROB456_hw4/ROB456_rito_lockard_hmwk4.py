#!/usr/bin/env python
# -*- coding: cp1252 -*-
# Authors: Aaron Rito, Robert Lockard
# Date: 11/13/17
# Client: ROB456 Homework 4
# Citations: Christian Careaga

#################################################################################################
# This program takes a n x n square graph and finds the shortest path by recursively            #
# searching through a list of visited cells. To make the visited list, a                        #
# starting cell is added to an open node list. Then, the algorithm searches                     #
# the neighboring cells recursively. Each open neighboring node is then added to the open list. #
# The starting node is then added to the visited list. For each node, we                        #
# keep track of the node's parent. The parent is set as the neighboring                         #
# node that has the lowest f value where (f = g + h where g is the cost of the path through     #
# the preceding parents (back to start), and h is the heuristic distance to the goal.) This     #
# continues on until each node in the list has been visited. Using the heapq library,           #           
# the open nodes are popped into a dictionary type array with their f values                    #
# as the key. The heap automatically sorts the key values, making the search                    #
# through the parents faster. This automatically implements the priority queue.                 #
# Once all the nodes have been visited, and thereby popped on to the visited set,               #
# then the set is iterated through and saved (backwards) in a path array. We reverse the path,  #
# print the results.                                                                            #
#################################################################################################

#imports
# numpy helps with calculations and array managment. (can be done with math library but easier with numpy)
import numpy
# import the heapq library for autosorted BST features
from heapq import *

# The heuristic function gives the user 3 options that can be set with the
# global variable "option": 0 = Manhattan, 1 = Euclidean, 2 = Dijkstra’s
# When using the 4 connected graph, the Manhattan works best. When using the
# 8 connected graph, the Euclidean gives the best result. To compare
# result accuracy against Dijkstra’s, run option 2 (no heuristic)
def heuristic(source, dest):
    # check the heuristic option and return the value
    if hur_option == 0:
        # return the Manhattan stlye heuristic
        return abs(dest[0] - source[0]) + abs(dest[1] - source[1])
    elif hur_option == 1:
        # return the Euclidean style heuristic
        return numpy.sqrt(abs((dest[0] - source[0])*(dest[0] - source[0]))+ abs((dest[1] - source[1])*(dest[1] - source[1])))
    else:
        # return 0 to all heuristic calculations (Dijkstra’s)
        return 0

# The aStarSearch performs the recursive A* algorithm.
# It gets passed the world map, and the starting and ending points.
def aStarSearch(array, start, goal):

    # check if we want to run the search using 4 or 8 connected graph. 
    if four_connected:
        neighbors_positions_list = [(0,1),(0,-1),(1,0),(-1,0)]
    else:
        neighbors_positions_list = [(0,1),(0,-1),(1,0),(-1,0),(1,1),(1,-1),(-1,1),(-1,-1)]

    # init the set of visited nodes
    close_set = set()
    # init the list of parents
    came_from = {}
    # init the g cost (shortest path through previous parents)
    g_value = {start:0}
    # init the f cost (g + h) 
    f_final = {start:heuristic(start, goal)}
    # init the open list in an array
    oheap = []
    # push the node start and final keys to the heap
    heappush(oheap, (f_final[start], start))

    # while there are still open nodes on the heap
    while oheap:
        # pop the lowest f value node from the heap
        current_node = heappop(oheap)[1]
        # if we found the goal
        if current_node == goal:
            # init the shortest path array 
            path_list = []
            # while there are still parents in the list
            while current_node in came_from:
                # pop the parent into the path array
                path_list.append(current_node)
                # update the recursive position 
                current_node = came_from[current_node]
            # return the path array
            return path_list
        # otherwise add the node to the visited list
        close_set.add(current_node)
        for i, j in neighbors_positions_list:
            # iterate through the nearby nodes
            neighbor = current_node[0] + i, current_node[1] + j
            # update the f_value for the node (f = g + h)
            f_value = g_value[current_node] + heuristic(current_node, neighbor)
            # check if the neighbor is within the bounds of the map array
            if 0 <= neighbor[0] < array.shape[0]:
                if 0 <= neighbor[1] < array.shape[1]:                
                    if array[neighbor[0]][neighbor[1]] == 1:
                        continue
                else:
                    # array bound y walls
                    continue
            else:
                # array bound x walls
                continue
            # if the neighbor is valid, check if we have visited it already
            # or if it is itself??
            if neighbor in close_set and f_value >= g_value.get(neighbor, 0):
                continue
            # if the neighbor's f value is greater than the node, or
            # if the neighbor has already been visited
            if  f_value < g_value.get(neighbor, 0) or neighbor not in [i[1]for i in oheap]:
                # update teh parent
                came_from[neighbor] = current_node
                # update the parents g value
                g_value[neighbor] = f_value
                # update and lock in the f value to the parent
                f_final[neighbor] = f_value + heuristic(neighbor, goal)
                # $$$$$$ MONEY LINE $$$$$ This is the recursive statement that
                # allows the algortithm to search through the graph without
                # using brute force iteration through the nodes.
                # Since each node has neighbors, and each neighbor has neighbors
                # the call will keep popping each open neighbor
                # onto the heap until all the nodes(and neighbors) have been
                # visited and removed from the open list. The f_final is the key
                # that we use later to print the path
                heappush(oheap, (f_final[neighbor], neighbor))
                
    return False


# The main code
print("These are the results of the optimal path analyis from the map array supplied in world.csv.\n")
print("NOTE: Optimal path may not be the shortest path.")

# Set the map using numpy array
world = numpy.array([[0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0],
                     [1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0],
                     [1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0],
                     [1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,0,0,0,0,0],
                     [1,1,1,0,1,1,1,1,0,0,1,1,1,1,1,0,0,0,0,0],
                     [1,1,1,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0],
                     [0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0],
                     [0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0],
                     [0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0],
                     [0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0],
                     [0,0,0,0,1,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0],
                     [0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0],
                     [0,0,0,0,1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0],
                     [0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                     [0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0],
                     [0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,1,0,0,0],
                     [0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0],
                     [0,0,0,0,0,0,1,1,1,0,0,0,0,1,1,0,0,0,0,0],
                     [0,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0],
                     [0,0,0,0,0,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0]])

# set the heuristic calculation function option
# 0 = Manhattan, 1 = Euclidean, 2 = Dijkstra’s
hur_option = 0
# set the graph search type: True = 4 connected (cardinal co-ordinates), False = 8 connected (all diagonals)
four_connected = True
# run the search with the new options
four_path = aStarSearch(world, (0,0), (19,19))
# reverse the path list so it prints nicely
four_path.reverse()
# print the results
print("\nUsing cardinal coordinates and Manhattan heuristic,")
print ("the optimal path was %d steps. The path taken was:\n" % len(four_path))
print four_path
# try some of the other options and print the results for comparison
hur_option = 2
D_four_path = aStarSearch(world, (0,0), (19,19))
D_four_path.reverse()
print("\nUsing cardinal coordinates and pure Dijkstra’s, no heuristic,")
print ("the optimal path was %d steps. The path taken was:\n" % len(D_four_path))
print D_four_path
hur_option = 1
four_connected = False
eight_path = aStarSearch(world, (0,0), (19,19))
eight_path.reverse()
print("\nUsing diagonals and Euclidean heuristic,")
print ("the optimal path was %d steps. The path taken was:\n" % len(eight_path))
print eight_path
hur_option = 2
D_eight_path = aStarSearch(world, (0,0), (19,19))
D_eight_path.reverse()
print("\nUsing diagonals and pure Dijkstra’s, no heuristic,")
print ("the optimal path was %d steps. The path taken was:\n" % len(D_eight_path))
print D_eight_path
