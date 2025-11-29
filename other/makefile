# makefile for program3
compiler = g++
flags = -std=c++17 -Wall     
compile = $(compiler) $(flags) -c 
link = $(compiler) $(flags) -o 

style : word_search_functions.cc 
	ls

word_search_functions.o : word_search_functions.cc word_search_functions.h
	$(compile) $<

program3.o : program3.cc word_search_functions.h
	$(compile) $<

program3 : word_search_functions.o program3.o
	$(link) $@ $^

test : program3
	./$<

clean :
	rm *.o program3 

