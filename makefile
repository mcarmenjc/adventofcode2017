CC = g++
CFLAGS  = -g -Wall -std=c++11
RM = rm

all: day_1 day_2 day_3 day_4 day_5 day_6 day_7 day_8 day_9 day_10 day_11 day_12 day_13 day_15 day_16 day_17 day_18 day_19 day_20 day_21 day_22 day_23 day_24 day_25

day_1:  day_1/day_1.cpp
	$(CC) $(CFLAGS) -o bin/day_1 day_1/day_1.cpp

day_2:  day_2/day_2.cpp
	$(CC) $(CFLAGS) -o bin/day_2 day_2/day_2.cpp

day_3:  day_3/day_3.cpp
	$(CC) $(CFLAGS) -o bin/day_3 day_3/day_3.cpp

day_4:  day_4/day_4.cpp
	$(CC) $(CFLAGS) -o bin/day_4 day_4/day_4.cpp

day_5:  day_5/day_5.cpp
	$(CC) $(CFLAGS) -o bin/day_5 day_5/day_5.cpp

day_6:  day_6/day_6.cpp
	$(CC) $(CFLAGS) -o bin/day_6 day_6/day_6.cpp

day_7:  day_7/day_7.cpp
	$(CC) $(CFLAGS) -o bin/day_7 day_7/day_7.cpp

day_8:  day_8/day_8.cpp
	$(CC) $(CFLAGS) -o bin/day_8 day_8/day_8.cpp

day_9:  day_9/day_9.cpp
	$(CC) $(CFLAGS) -o bin/day_9 day_9/day_9.cpp

day_10:  bin/day_10.o bin/KnotHash.o
	$(CC) $(CFLAGS) -o bin/day_10 bin/day_10.o bin/KnotHash.o

day_11:  day_11/day_11.cpp
	$(CC) $(CFLAGS) -o bin/day_11 day_11/day_11.cpp

day_12:  day_12/day_12.cpp
	$(CC) $(CFLAGS) -o bin/day_12 day_12/day_12.cpp

day_13:  day_13/day_13.cpp
	$(CC) $(CFLAGS) -o bin/day_13 day_13/day_13.cpp

day_14:  bin/day_14.o bin/KnotHash.o
	$(CC) $(CFLAGS) -o bin/day_14 bin/day_14.o bin/KnotHash.o

day_15:  day_15/day_15.cpp
	$(CC) $(CFLAGS) -o bin/day_15 day_15/day_15.cpp

day_16:  day_16/day_16.cpp
	$(CC) $(CFLAGS) -o bin/day_16 day_16/day_16.cpp

day_17:  day_17/day_17.cpp
	$(CC) $(CFLAGS) -o bin/day_17 day_17/day_17.cpp

day_18:  day_18/day_18.cpp
	$(CC) $(CFLAGS) -o bin/day_18 day_18/day_18.cpp

day_19:  day_19/day_19.cpp
	$(CC) $(CFLAGS) -o bin/day_19 day_19/day_19.cpp

day_20:  day_20/day_20.cpp
	$(CC) $(CFLAGS) -o bin/day_20 day_20/day_20.cpp

day_21:  day_21/day_21.cpp
	$(CC) $(CFLAGS) -o bin/day_21 day_21/day_21.cpp

day_22:  day_22/day_22.cpp
	$(CC) $(CFLAGS) -o bin/day_22 day_22/day_22.cpp

day_23:  day_23/day_23.cpp
	$(CC) $(CFLAGS) -o bin/day_23 day_23/day_23.cpp

day_24:  day_24/day_24.cpp
	$(CC) $(CFLAGS) -o bin/day_24 day_24/day_24.cpp

day_25:  day_25/day_25.cpp
	$(CC) $(CFLAGS) -o bin/day_25 day_25/day_25.cpp

bin/day_10.o:  day_10/day_10.cpp lib/KnotHash.h 
	$(CC) $(CFLAGS) -c day_10/day_10.cpp -o bin/day_10.o

bin/day_14.o:  day_14/day_14.cpp lib/KnotHash.h 
	$(CC) $(CFLAGS) -c day_14/day_14.cpp -o bin/day_14.o

bin/KnotHash.o:  lib/KnotHash.cpp lib/KnotHash.h 
	$(CC) $(CFLAGS) -c lib/KnotHash.cpp -o bin/KnotHash.o

clean: 
	$(RM) bin/day_* bin/*.o