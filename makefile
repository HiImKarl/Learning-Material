

.PHONY : clean

test : test.o 	
	g++ -o $@ $^

test.o : test.cc part1/AVL.hh part2/AVL.hh
	g++ -c -o $@ $<


display : display.o
	g++ -o $@ $^

display.o : display.cc part1/AVL.hh part2/AVL.hh
	g++ -c -o $@ $<


clean :
	rm -f *.o test display
