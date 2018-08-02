CXX?=g++

GMOCK_HOME=../../../../lib/googlemock
PROJECT_HOME=../..
SRC_DIR=$(PROJECT_HOME)/src
TEST_SRC_DIR=$(SRC_DIR)/UnitTest

CPPFLAGS=-g -O0 -fprofile-arcs -ftest-coverage -DUNITTEST \
         -I$(GMOCK_HOME)/include -I$(PROJECT_HOME)/include -I$(SRC_DIR) -I$(TEST_SRC_DIR)

LDFLAGS=-lgcov --coverage

uname_S:=$(shell sh -c 'uname -s 2>/dev/null || echo not')

ifneq ($(uname_S), Linux)
LDFLAGS+=-L$(GMOCK_HOME)/lib/win64
else
LDFLAGS+=-L$(GMOCK_HOME)/lib -lpthread
endif

all: gmock_test

########################################################################################################################

GMOCK_TEST_CXXFLAGS=
GMOCK_TEST_LDFLAGS=-lgmock_main

GMOCK_TEST_OBJS=gmock_test.o

gmock_test: $(GMOCK_TEST_OBJS)
	$(CXX) $(LDFLAGS) $(GMOCK_TEST_LDFLAGS) -o $@ $(GMOCK_TEST_OBJS)

$(GMOCK_TEST_OBJS): %.o: %.cc
	$(CXX) $(CPPFLAGS) $(GMOCK_TEST_CXXFLAGS) -MMD -c $< -o $@

########################################################################################################################

OBJS=$(GMOCK_TEST_OBJS)

-include $(OBJS:.o=.d)

BINARY=gmock_test

.PHONY: all clean

clean:
	@find -name "*.o" -exec rm {} \;
	@find -name "*.d" -exec rm {} \;
	@find -name "*.gcda" -exec rm {} \;
	@find -name "*.gcno" -exec rm {} \;
	@rm -f $(BINARY)
