CC=g++

all: main main_test

CXXFLAGS +=  -fprofile-arcs -ftest-coverage
LDFLAGS += -std=c++11 -lpthread -lz -lgcov

#-fprofile-arcs -ftest-coverage -lgcov --coverage

PROJECT_HOME = .


MAIN_OBJECTS = $(PROJECT_HOME)/src/main.o
PROJECT_OBJECTS = $(PROJECT_HOME)/src/text_query.o\
				  $(PROJECT_HOME)/src/common_tools.o\
				  $(PROJECT_HOME)/src/replace_headfile.o

PROJECT_MAIN = $(PROJECT_OBJECTS)\
			   $(MAIN_OBJECTS)


UNITTEST_COMMON_OBJECTS = $(PROJECT_HOME)/unit_test/Common/filetxtreader.o \
                          $(PROJECT_HOME)/unit_test/Common/dirnameparser.o \
						  $(PROJECT_HOME)/unit_test/Common/filenamereader.o\
						  $(PROJECT_HOME)/unit_test/Common/freefunc.o 



UNIT_TEST = $(PROJECT_HOME)/unit_test/gtest_main.o\
			$(PROJECT_HOME)/unit_test/common_tools_test.o\
			$(PROJECT_HOME)/unit_test/text_query_test.o


			   
PROJECT_UNITTEST = $(UNIT_TEST)\
					$(UNITTEST_COMMON_OBJECTS)\
					$(PROJECT_OBJECTS)

GTEST_INCLUDE = -I$(PROJECT_HOME)/unit_test/include 
GTEST_LIB = -L$(PROJECT_HOME)/unit_test/lib -lgmock

UNITEST_INC = -I$(PROJECT_HOME)/include/\
			  -I$(PROJECT_HOME)/unit_test/Common\
              -I$(PROJECT_HOME)/unit_test/Common/RapidXml\
			  $(GTEST_INCLUDE) 

main: $(PROJECT_MAIN)
	$(CC) $(PROJECT_MAIN)  $(CXXFLAGS) $(LDFLAGS) -o $@

main_test:$(PROJECT_UNITTEST) 
	$(CC) $(PROJECT_UNITTEST) $(GTEST_LIB) $(UNITEST_INC)  $(CXXFLAGS) $(LDFLAGS) -o $@ 
	
.cc.o:$(UNITEST_INC) 
	$(CC) $(CXXFLAGS) $(LDFLAGS) $(UNITEST_INC) -c $*.cc -o $*.o 

.PHONY: clean

clean:
	rm $(PROJECT_UNITTEST)
	rm $(MAIN_OBJECTS)
	rm main
	rm main_test
	find . -name "*.o" -exec rm {} \;
	find . -name "*.gcno" -exec rm {} \;
	find . -name "*.gcda" -exec rm {} \;
	find . -name "*~" -exec rm {} \;

