CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra
LIBS := -lcurl -ljsoncpp

SRC := test.cpp
DEPS := doctest.h
TARGET := test

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC) $(DEPS)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)