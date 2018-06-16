all: main

main: main.o text_query.o common_tools.o
	g++ main.cc text_query.cc common_tools.cc replace_headfile.cc -o main 

clean:
	rm *.o 
	rm main
	rm *~
	rm .*~
