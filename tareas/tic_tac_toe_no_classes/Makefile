CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
TARGET = M644168P1
SRC = M644168P1.cpp

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

debug: $(TARGET)
	./$(TARGET) --debug

help: $(TARGET)
	./$(TARGET) --help
