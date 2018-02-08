

.PHONY : test display benchmark clean

test : test_tmp 
	./test_tmp
	rm test_tmp

test_tmp : test.o
	g++ -o $@ $^

test.o : test.cc part1/AVL.hh part2/AVL.hh
	g++ -c -o $@ $<

display : display.o
	g++ -o $@ $^

display.o : display.cc part1/AVL.hh part2/AVL.hh
	g++ -c -o $@ $<

benchmark : benchmark_tmp
	./benchmark_tmp
	rm benchmark_tmp
	
benchmark_tmp : benchmark.o
	g++ -o $@ $^

benchmark.o : benchmark.cc part2/AVL.hh
	g++ -c -o $@ $<

clean :
	rm -f *.o display 
