CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra

SRC := test.cpp
DEPS := doctest.h
TARGET := test.exe

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC) $(DEPS)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)