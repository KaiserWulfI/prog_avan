# Makefile para el juego de Gato Inteligente
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = M644168P1
SOURCE = M644168P1.cpp

# Compilación por defecto
all: $(TARGET)

# Regla para compilar el programa
$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

# Regla para compilar con información de debug adicional
debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

# Regla para limpiar archivos compilados
clean:
	rm -f $(TARGET)

# Regla para ejecutar el programa
run: $(TARGET)
	./$(TARGET)

# Regla para mostrar ayuda
help:
	@echo "Comandos disponibles:"
	@echo "  make        - Compila el programa"
	@echo "  make debug  - Compila con información de debug"
	@echo "  make run    - Compila y ejecuta el programa"
	@echo "  make clean  - Elimina archivos compilados"
	@echo "  make help   - Muestra esta ayuda"

.PHONY: all debug clean run help
