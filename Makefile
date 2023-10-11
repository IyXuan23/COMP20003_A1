#first target
dict1: main1.o listops.o functions.o
	gcc -g -Wall -o dict1 main1.o listops.o functions.o

#2nd target
dict2: main2.o listops.o functions.o
	gcc -g -Wall -o dict2 main2.o listops.o functions.o

main1.o: main1.c 
	gcc -g -Wall -c main1.c

main2.o: main2.c
	gcc -g -Wall -c main2.c

listops.o: listops.c listops.h
	gcc -g -Wall -c listops.c

functions.o: functions.c functions.h
	gcc -g -Wall -c functions.c


