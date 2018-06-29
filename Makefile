CC=g++

all: main main_test

CFLAGS = -std=c++11 -lpthread


PROJECT_HOME = .


MAIN_OBJECTS = main.o
PROJECT_OBJECTS = text_query.o common_tools.o replace_headfile.o  

PROJECT_MAIN = $(PROJECT_OBJECTS)\
			   $(MAIN_OBJECTS)

UNIT_TEST = $(PROJECT_HOME)/unit_test/gtest_main.o\
			$(PROJECT_HOME)/unit_test/common_tools_test.o

			   

PROJECT_UNITTEST = $(PROJECT_OBJECTS)\
				   $(UNIT_TEST)

GTEST_INCLUDE = -I$(PROJECT_HOME)/unit_test/include 
GTEST_LIB = -L$(PROJECT_HOME)/unit_test/lib -lgmock

UNITTEST_INC = -I$(PROJECT_HOME)/unittest/Common \
               -I$(PROJECT_HOME)/unittest/Common/RapidXml \
				$(GTEST_INCLUDE) 

main: $(PROJECT_MAIN)
	$(CC) $(PROJECT_MAIN) -o $@

main_test:$(PROJECT_UNITTEST) 
	$(CC) $(PROJECT_UNITTEST) $(GTEST_LIB) $(UNITEST_INC) $(CFLAGS) -o $@
	

.cc.o:
	$(CC) $(CFLAGS) -c $*.cc -o $*.o 


clean:
	rm *.o 
	rm $(UNIT_TEST) 
	rm main
	rm *~
	rm .*~
	rm main_test
