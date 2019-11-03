a.out : test.o msg_data.o
		gcc -o a.out test.o msg_data.o
		rm *.o


test.o : test.c
		gcc -c test.c 


msg_data.o : msg_data.c msg_data.h
		gcc -c msg_data.c

.PHONY : clean
clean :
		rm *.out *.o                           