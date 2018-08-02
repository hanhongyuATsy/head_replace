CXX?=g++
AR?=ar

DESTINATION?=/usr/local/lib

PAT_VERSION:=6.0
PNR_VERSION:=3.5
ERR_VERSION:=1.0
FRONT_VERSION:=5.0

PROJECT_HOME=.
SRC_DIR=$(PROJECT_HOME)/src

CPPFLAGS?=-I$(PROJECT_HOME)/include -I$(SRC_DIR) -fPIC -Wno-deprecated -D_REENTRANT -DMTHREAD -D_TRACE

ifeq ($(DEBUG), TRUE)
CPPFLAGS+=-g -O0
else
CPPFLAGS+=-g -O2
endif

uname_S:=$(shell sh -c 'uname -s 2>/dev/null || echo not')

ifneq ($(uname_S), Linux)
include .env_win
endif

########################################################################################################################

ifeq ($(MODE), BESTBUY)
COMMON_CXXFLAGS=-pipe -DBESTBUY
else
COMMON_CXXFLAGS=
endif

COMMON_CXXFLAGS+=-I$(BOOST_HOME)/include -I$(ZLIB_HOME)/include

include $(SRC_DIR)/common.src

########################################################################################################################

ifeq ($(MODE), BESTBUY)
ERRORREQUEST_CXXFLAGS=-pipe -DBESTBUY
else
ERRORREQUEST_CXXFLAGS=
endif

ERRORREQUEST_CXXFLAGS+=-I$(BOOST_HOME)/include

include $(SRC_DIR)/errorrequest.src

########################################################################################################################

ifeq ($(MODE), BESTBUY)
ERRORRESULT_CXXFLAGS=-pipe -DBESTBUY
else
ERRORRESULT_CXXFLAGS=
endif

ERRORRESULT_CXXFLAGS+=-I$(BOOST_HOME)/include

include $(SRC_DIR)/errorresult.src

########################################################################################################################

ifeq ($(MODE), BESTBUY)
OCREQUEST_CXXFLAGS=-pipe -DBESTBUY
else
OCREQUEST_CXXFLAGS=
endif

OCREQUEST_CXXFLAGS+=-I$(BOOST_HOME)/include -I$(ZLIB_HOME)/include

include $(SRC_DIR)/ocrequest.src

########################################################################################################################

ifeq ($(MODE), BESTBUY)
REQUESTBASE_CXXFLAGS=-pipe -DBESTBUY
else
REQUESTBASE_CXXFLAGS=
endif

REQUESTBASE_CXXFLAGS+=-I$(BOOST_HOME)/include

include $(SRC_DIR)/requestbase.src

########################################################################################################################

ifeq ($(MODE), BESTBUY)
REQUEST_CXXFLAGS=-pipe -DBESTBUY
else
REQUEST_CXXFLAGS=
endif

REQUEST_CXXFLAGS+=-I$(BOOST_HOME)/include -I$(ZLIB_HOME)/include

include $(SRC_DIR)/request.src

########################################################################################################################

ifeq ($(MODE), BESTBUY)
RESULTBASE_CXXFLAGS=-pipe -DBESTBUY
else
RESULTBASE_CXXFLAGS=
endif

RESULTBASE_CXXFLAGS+=-I$(BOOST_HOME)/include

include $(SRC_DIR)/resultbase.src

########################################################################################################################

ifeq ($(MODE), BESTBUY)
RESULT_CXXFLAGS=-pipe -DBESTBUY
else
RESULT_CXXFLAGS=
endif

RESULT_CXXFLAGS+=-I$(BOOST_HOME)/include -I$(ZLIB_HOME)/include

include $(SRC_DIR)/result.src

########################################################################################################################

ifeq ($(MODE), BESTBUY)
OCRESULT_CXXFLAGS=-pipe -DBESTBUY
else
OCRESULT_CXXFLAGS=
endif

OCRESULT_CXXFLAGS+=-I$(BOOST_HOME)/include -I$(ZLIB_HOME)/include

include $(SRC_DIR)/ocresult.src

########################################################################################################################

AVGROUPS_CXXFLAGS=-pipe -DBESTBUY -I$(BOOST_HOME)/include

include $(SRC_DIR)/avgroups.src

########################################################################################################################

ifeq ($(MODE), BESTBUY)
DISPLAY_CXXFLAGS=-pipe -DBESTBUY
else
DISPLAY_CXXFLAGS=
endif

DISPLAY_CXXFLAGS+=-I$(BOOST_HOME)/include -I$(ZLIB_HOME)/include

include $(SRC_DIR)/display.src

########################################################################################################################

ifeq ($(MODE), BESTBUY)
PAT_CXXFLAGS=-pipe -DLINUX -DBESTBUY -DWITHCACHE -DWITH_TODE -DDO_NOT_CHCEK_CACHE_STATUS
else
PAT_CXXFLAGS=-DXMLTRACE -DWITHCACHE
endif

PAT_CXXFLAGS+=-I$(BOOST_HOME)/include -I$(ZLIB_HOME)/include \
              -I$(ORACLE_HOME)/rdbms/demo -I$(ORACLE_HOME)/rdbms/public \
              -I$(TOSF_HOME)/include -I$(TOSF_HOME)/fml \
              -I$(TOSF_HOME)/tosftools/include -I$(TOSF_HOME)/tsc/include \
              -I$(TODEHOMEDIR)/include -I$(TODEHOMEDIR)/public/fml

PAT_LDFLAGS=-L$(PROJECT_HOME) \
            -L$(BOOST_HOME)/lib -lboost_serialization \
            -L$(ZLIB_HOME)/lib -lz \
            -L$(ORACLE_HOME)/lib -locci -lclntsh \
            -L$(TOSF_HOME)/tosftools -ltosftool \
            -L$(TODEHOMEDIR)/lib -ltode -ltodecli

PAT_LDFLAGS+=-lcommon -lerrorrequest -lrequestbase -lrequest -locrequest -lresultbase -lresult -locresult
ifeq ($(MODE), BESTBUY)
PAT_LDFLAGS+=-lavgroups
endif

include $(SRC_DIR)/pat_comm.src
ifeq ($(MODE), BESTBUY)
-include $(SRC_DIR)/pat_dbpric.src
else
-include $(SRC_DIR)/pat_dpric.src
endif

########################################################################################################################

ifeq ($(MODE), BESTBUY)
FRONT_CXXFLAGS=-pipe -DLINUX -DBESTBUY -DWITHCACHE -DWITH_TODE -DDO_NOT_CHCEK_CACHE_STATUS
else
FRONT_CXXFLAGS=-DXMLTRACE
endif

FRONT_CXXFLAGS+=-I$(BOOST_HOME)/include -I$(ZLIB_HOME)/include -I$(XERCES_HOME)/include \
                -I$(TODEHOMEDIR)/include -I$(TODEHOMEDIR)/public/fml \
                -I$(TOSF_HOME)/include -I$(TOSF_HOME)/fml -I$(TOSF_HOME)/tosftools/include

FRONT_LDFLAGS=-L$(PROJECT_HOME) \
              -L$(BOOST_HOME)/lib -lboost_serialization -L$(ZLIB_HOME)/lib -lz \
              -L$(XERCES_HOME)/lib -lxerces-c \
              -L$(TOSF_HOME)/tosftools -ltosftool

FRONT_LDFLAGS+=-lcommon -lerrorrequest -lrequestbase -lrequest -locrequest -lresultbase -lresult -lerrorresult -locresult -ldisplay
ifeq ($(MODE), BESTBUY)
FRONT_LDFLAGS+=-lavgroups
endif

include $(SRC_DIR)/front_comm.src
ifeq ($(MODE), BESTBUY)
-include $(SRC_DIR)/front_dbpric.src
else
-include $(SRC_DIR)/front_dpric.src
endif

########################################################################################################################

PNR_CXXFLAGS=-DWITHCACHE \
             -I$(BOOST_HOME)/include -I$(ZLIB_HOME)/include \
             -I$(ORACLE_HOME)/rdbms/demo -I$(ORACLE_HOME)/rdbms/public \
             -I$(TOSF_HOME)/include -I$(TOSF_HOME)/fml \
             -I$(TOSF_HOME)/tosftools/include -I$(TOSF_HOME)/tsc/include \
             -I$(TODEHOMEDIR)/include -I$(TODEHOMEDIR)/public/fml

PNR_LDFLAGS=-L$(PROJECT_HOME) -lcommon -lrequestbase -lresultbase -ldisplay \
            -L$(BOOST_HOME)/lib -lboost_serialization -L$(ZLIB_HOME)/lib -lz \
            -L$(ORACLE_HOME)/lib -locci -lclntsh \
            -L$(TOSF_HOME)/tosftools -ltosftool \
		    -L$(TODEHOMEDIR)/lib -ltode

include $(SRC_DIR)/pnr.src

########################################################################################################################

ERR_CXXFLAGS=-I$(BOOST_HOME)/include \
             -I$(TOSF_HOME)/include -I$(TOSF_HOME)/tosftools/include \
             -I$(TODEHOMEDIR)/include

ERR_LDFLAGS=-L$(PROJECT_HOME) -lcommon -lerrorrequest -lerrorresult \
            -L$(BOOST_HOME)/lib -lboost_serialization \
            -L$(TOSF_HOME)/tosftools -ltosftool \
            -L$(TODEHOMEDIR)/lib -ltode -ltodecli

include $(SRC_DIR)/err.src

########################################################################################################################

OBJS=$(COMMON_OBJS) $(ERRORREQUEST_OBJS) \
     $(REQUESTBASE_OBJS) $(REQUEST_OBJS) $(OCREQUEST_OBJS) \
     $(RESULTBASE_OBJS) $(RESULT_OBJS) $(ERRORRESULT_OBJS) $(OCRESULT_OBJS) \
     $(AVGROUPS_OBJS) $(DISPLAY_OBJS) \
     $(PAT_OBJS) $(FRONT_OBJS) $(PNR_OBJS) $(ERR_OBJS)

ifeq ($(MODE), BESTBUY)
all: libpat.so.$(PAT_VERSION) libfarefront.so.$(FRONT_VERSION) liberr.so.$(ERR_VERSION)
else
all: libpat.so.$(PAT_VERSION) libfarefront.so.$(FRONT_VERSION) libpnr.so.$(PNR_VERSION)
endif

-include $(OBJS:.o=.d)

libcommon.a: $(COMMON_OBJS)
	$(AR) rucs $@ $(COMMON_OBJS)

liberrorrequest.a: $(ERRORREQUEST_OBJS)
	$(AR) rucs $@ $(ERRORREQUEST_OBJS)

librequestbase.a: $(REQUESTBASE_OBJS)
	$(AR) rucs $@ $(REQUESTBASE_OBJS)

librequest.a: $(REQUEST_OBJS)
	$(AR) rucs $@ $(REQUEST_OBJS)

libocrequest.a: $(OCREQUEST_OBJS)
	$(AR) rucs $@ $(OCREQUEST_OBJS)

libresultbase.a: $(RESULTBASE_OBJS)
	$(AR) rucs $@ $(RESULTBASE_OBJS)

libresult.a: $(RESULT_OBJS)
	$(AR) rucs $@ $(RESULT_OBJS)

liberrorresult.a: $(ERRORRESULT_OBJS)
	$(AR) rucs $@ $(ERRORRESULT_OBJS)

libocresult.a: $(OCRESULT_OBJS)
	$(AR) rucs $@ $(OCRESULT_OBJS)

libavgroups.a: $(AVGROUPS_OBJS)
	$(AR) rucs $@ $(AVGROUPS_OBJS)

libdisplay.a: $(DISPLAY_OBJS)
	$(AR) rucs $@ $(DISPLAY_OBJS)

ifeq ($(MODE), BESTBUY)
libpat.so.$(PAT_VERSION): libcommon.a liberrorrequest.a librequestbase.a librequest.a libocrequest.a libresultbase.a libresult.a libocresult.a libavgroups.a $(PAT_OBJS)
	$(CXX) -shared -o $@ $(PAT_OBJS) $(PAT_LDFLAGS)
else
libpat.so.$(PAT_VERSION): libcommon.a liberrorrequest.a librequestbase.a librequest.a libocrequest.a libresultbase.a libresult.a libocresult.a $(PAT_OBJS)
	$(CXX) -shared -o $@ $(PAT_OBJS) $(PAT_LDFLAGS)
endif

ifeq ($(MODE), BESTBUY)
libfarefront.so.$(FRONT_VERSION): libcommon.a liberrorrequest.a librequestbase.a librequest.a libocrequest.a libresultbase.a libresult.a liberrorresult.a libocresult.a libavgroups.a libdisplay.a $(FRONT_OBJS)
	$(CXX) -shared -o $@ $(FRONT_OBJS) $(FRONT_LDFLAGS)
else
libfarefront.so.$(FRONT_VERSION): libcommon.a liberrorrequest.a librequestbase.a librequest.a libocrequest.a libresultbase.a libresult.a liberrorresult.a libocresult.a libdisplay.a $(FRONT_OBJS)
	$(CXX) -shared -o $@ $(FRONT_OBJS) $(FRONT_LDFLAGS)
endif

libpnr.so.$(PNR_VERSION): libcommon.a librequestbase.a libresultbase.a libdisplay.a $(PNR_OBJS)
	$(CXX) -shared -o $@ $(PNR_OBJS) $(PNR_LDFLAGS)

liberr.so.$(ERR_VERSION): libcommon.a liberrorrequest.a liberrorresult.a $(ERR_OBJS)
	$(CXX) -shared -o $@ $(ERR_OBJS) $(ERR_LDFLAGS)

$(COMMON_OBJS): %.o: %.cc
	$(CXX) $(CPPFLAGS) $(COMMON_CXXFLAGS) -MMD -c $< -o $@

$(ERRORREQUEST_OBJS): %.o: %.cc
	$(CXX) $(CPPFLAGS) $(ERRORREQUEST_CXXFLAGS) -MMD -c $< -o $@

$(REQUESTBASE_OBJS): %.o: %.cc
	$(CXX) $(CPPFLAGS) $(REQUESTBASE_CXXFLAGS) -MMD -c $< -o $@

$(REQUEST_OBJS): %.o: %.cc
	$(CXX) $(CPPFLAGS) $(REQUEST_CXXFLAGS) -MMD -c $< -o $@

$(OCREQUEST_OBJS): %.o: %.cc
	$(CXX) $(CPPFLAGS) $(OCREQUEST_CXXFLAGS) -MMD -c $< -o $@

$(RESULTBASE_OBJS): %.o: %.cc
	$(CXX) $(CPPFLAGS) $(RESULTBASE_CXXFLAGS) -MMD -c $< -o $@

$(RESULT_OBJS): %.o: %.cc
	$(CXX) $(CPPFLAGS) $(RESULT_CXXFLAGS) -MMD -c $< -o $@

$(ERRORRESULT_OBJS): %.o: %.cc
	$(CXX) $(CPPFLAGS) $(ERRORRESULT_CXXFLAGS) -MMD -c $< -o $@

$(OCRESULT_OBJS): %.o: %.cc
	$(CXX) $(CPPFLAGS) $(OCRESULT_CXXFLAGS) -MMD -c $< -o $@

$(AVGROUPS_OBJS): %.o: %.cc
	$(CXX) $(CPPFLAGS) $(AVGROUPS_CXXFLAGS) -MMD -c $< -o $@

$(DISPLAY_OBJS): %.o: %.cc
	$(CXX) $(CPPFLAGS) $(DISPLAY_CXXFLAGS) -MMD -c $< -o $@

$(PAT_OBJS): %.o: %.cc
	$(CXX) $(CPPFLAGS) $(PAT_CXXFLAGS) -MMD -c $< -o $@

$(FRONT_OBJS): %.o: %.cc
	$(CXX) $(CPPFLAGS) $(FRONT_CXXFLAGS) -MMD -c $< -o $@

$(PNR_OBJS): %.o: %.cc
	$(CXX) $(CPPFLAGS) $(PNR_CXXFLAGS) -MMD -c $< -o $@

$(ERR_OBJS): %.o: %.cc
	$(CXX) $(CPPFLAGS) $(ERR_CXXFLAGS) -MMD -c $< -o $@

.PHONY: all install clean

ifeq ($(MODE), BESTBUY)
install: all
	@mkdir -p $(DESTINATION)
	install libpat.so.$(PAT_VERSION) $(DESTINATION)
	install libfarefront.so.$(FRONT_VERSION) $(DESTINATION)
	install liberr.so.$(ERR_VERSION) $(DESTINATION)
else
install: all
	@mkdir -p $(DESTINATION)
	install libpat.so.$(PAT_VERSION) $(DESTINATION)
	install libfarefront.so.$(FRONT_VERSION) $(DESTINATION)
	install libpnr.so.$(PNR_VERSION) $(DESTINATION)
endif

clean:
	@find $(PROJECT_HOME) -name "*.d" -exec rm {} \;
	@find $(PROJECT_HOME) -name "*.o" -exec rm {} \;
	@find $(PROJECT_HOME) -name "*.a" -exec rm {} \;
	@find $(PROJECT_HOME) -name "*.so*" -exec rm {} \;
