CC = g++
CPPFLAGS = -Wall -g -std=c++11

main:			main.o table.o supplied.o

main.o:			table.h

clist.o:		table.h

.PHONY: clean	
clean:				# clean the directory
				$(info -- cleaning the directory --)
				rm -f table.o main.o main
