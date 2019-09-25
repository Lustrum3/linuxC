
b.out : httpd.o html.o
	gcc -o b.out httpd.o html.o


httpd.o : httpd.c
	gcc -c httpd.c 


html.o : html.c html.h
	gcc -c html.c

.PHONY : clean
clean :
	rm *.out *.o
