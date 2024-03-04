CC = gcc
CFLAGS = -Wall
MY_GRAPH = my_graph
MY_KNAPSACK = my_Knapsack

StrList: StrList.c main.c
	$(CC) $(CFLAGS) -g -o $@ $^

all: StrList

clean:
	rm -f StrList main
