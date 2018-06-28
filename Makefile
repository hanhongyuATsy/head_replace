#all: main main_test
CC=g++
all: main 

CFLAGS = -std=c++11


#PROJECT_HOME = .

#UNIT_TEST = $(PROJECT_HOME)/unit_test/gtest_main.o

PROJECT_OBJECTS = text_query.o common_tools.o replace_headfile.o  

main: main.o $(PROJECT_OBJECTS)
	$(CC) main.o $(PROJECT_OBJECTS) -o $@

#main_test:

.cc.o:
	$(CC) $(CFLAGS) -c $*.cc -o $*.o 


clean:
	rm *.o 
	rm main
	rm *~
	rm .*~
