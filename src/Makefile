PWD := $(shell pwd)

CXX := g++
ARM_CXX := arm-linux-gnueabi-g++

CXXFLAGS := -std=c++11 -msse3 -Wall -I../include
ARM_CXXFLAGS := -std=c++11 -march=armv7-a -mfloat-abi=softfp -mfpu=neon -DARM -I../include

.PHONY : all
all: test_sse test_neon gen_input

test_sse: run_test.cc ../include/sse2neon.h
	$(CXX) $(CXXFLAGS) -o test_sse run_test.cc

gen_input: gen_input.cc
	$(CXX) $(CXXFLAGS) -o gen_input gen_input.cc

test_neon: run_test.cc ../include/sse2neon.h
	$(ARM_CXX) $(ARM_CXXFLAGS) -o test_neon run_test.cc


.PHONY : install
install:
	cp test_sse test_neon gen_input $(PWD)/../bin/


.PHONY : cleanall cleanobj
clean : cleanobj cleandiff
	-rm -rf test_sse test_neon gen_input

cleanobj :
	-rm -rf *.o
