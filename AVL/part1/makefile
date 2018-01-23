
.PHONY : all clean


all : test


test : test.o
	g++ -o $@ $^

test.o : test.cc AVL.hh
	g++ -c -o $@ $<

clean: 
	rm -f *.o test
