# Makefile
# @author: Alyssa Quek
#
# SYNOPSIS:
#
#   make [all]  - makes everything.
#   make TARGET - makes the given target.
#   make clean  - removes all files generated by make.

# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.
GTEST_DIR = ../gtest

# Where to find user code.
USER_DIR = .

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(GTEST_DIR)/include

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TESTS = unittest.out

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h
GTEST_OBJECT = gtest/gtest_main.a 
# House-keeping build targets.

all : $(TESTS)

cleanall : 
	rm -f $(TESTS) gtest.a gtest_main.a *.o

clean : 
	rm -f $(TESTS) *.o

# Builds gtest.a and gtest_main.a.

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

.INTERMEDIATE : gtest_main.o gtest-all.o gtest.a gtest_main.a 
# Builds a sample test.  A test should link with either gtest.a or
# gtest_main.a, depending on whether it defines its own main()
# function.

heap.o : $(USER_DIR)/heap.cpp $(USER_DIR)/heap.h $(GTEST_OBJECT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/heap.cpp

unittest.o : $(USER_DIR)/unittest.cpp \
             heap.o $(GTEST_OBJECT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/unittest.cpp

$(TESTS) : heap.o unittest.o $(GTEST_OBJECT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@