

.PHONY : all clean

all : test
	./test
	rm test

test : test.o 	
	g++ -o $@ $^

test.o : test.cc part1/AVL.hh part2/AVL.hh
	g++ -c -o $@ $<

display : display.o
	g++ -o $@ $^

display.o : display.cc part1/AVL.hh part2/AVL.hh
	g++ -c -o $@ $<

benchmark : benchmark.o
	g++ -o $@ $^

benchmark.o : benchmark.cc part2/AVL.hh
	g++ -c -o $@ $<

clean :
	rm -f *.o test display benchmark
