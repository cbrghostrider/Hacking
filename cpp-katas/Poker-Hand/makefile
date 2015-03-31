# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.
GTEST_DIR = ../gmock/gtest

# Where to find user code.
USER_DIR = .

# Flags passed to the preprocessor.
CPPFLAGS += -I$(GTEST_DIR)/include
CXX = /usr/intel/pkgs/gcc/4.8.1/bin/g++
# Flags passed to the C++ compiler.
CXXFLAGS += -O3 -std=c++11 -Wall -Wextra -pthread 

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TESTS = poker-tests

EXE = PokerHand

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# House-keeping build targets.

all : $(TESTS) $(EXE)

clean :
	rm -f $(TESTS) $(EXE) gtest.a gtest_main.a *.o

# Builds gtest.a and gtest_main.a.

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS)  -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# Builds a sample test.  A test should link with either gtest.a or
# gtest_main.a, depending on whether it defines its own main()
# function.

main.o :$(USER_DIR)/main.cpp
	$(CXX) $(CXXFLAGS)-c $^ -o $@
	
PokerHand.o : $(USER_DIR)/poker-hand.cpp
	$(CXX) $(CXXFLAGS)-c $^ -o $@
	
PokerHandUnitTests.o : poker-hand-tests.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c  $^ -o $@
	
PokerHand : PokerHand.o main.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS)  $^ -o $@
	
$(TESTS): PokerHandUnitTests.o PokerHand.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lrt $^ -o $@
	
