all: main

main: main.o text_query.o common_tools.o replace_headfile.o
	g++ -o main main.o text_query.o common_tools.o replace_headfile.o  

main.o:
	g++ -c main.cc -std=c++11 
text_query.o:
	g++ -c text_query.cc -std=c++11 
common_tools.o:
	g++ -c common_tools.cc -std=c++11 
replace_headfile.o:
	g++ -c replace_headfile.cc -std=c++11 


clean:
	rm *.o 
	rm main
	rm *~
	rm .*~
