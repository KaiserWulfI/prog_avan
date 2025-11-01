# Makefile para Árbol Binario de Búsqueda
# Alejandro Longoria Gonzalez - 644168

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g
TARGET = M644168P1
SOURCES = M644168P1.cpp
HEADERS = ABB.h

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
