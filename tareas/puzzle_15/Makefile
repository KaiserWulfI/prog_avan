CXX      := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -pedantic
LDFLAGS  := -lncurses
TARGET   := puzzle15
SRC      := M644168P1.cpp

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -f $(TARGET)

