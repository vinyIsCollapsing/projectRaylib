# Nome do executável
TARGET = build/mygame

# Diretórios
SRCDIR = src
INCDIR = include
BUILDDIR = build

# Arquivos fonte
SRC = main.cpp $(wildcard $(SRCDIR)/*.cpp)

# Diretório de instalação da Raylib
RAYLIB_PATH = /usr/local

# Diretório de include da Raylib
INCLUDE_DIR = $(RAYLIB_PATH)/include

# Diretório das bibliotecas da Raylib
LIB_DIR = $(RAYLIB_PATH)/lib

# Flags de compilação
CXX = g++
CXXFLAGS = -Wall -I$(INCDIR) -I$(INCLUDE_DIR)
LDFLAGS = -L$(LIB_DIR) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Arquivos objeto
OBJECTS = $(SRC:%.cpp=$(BUILDDIR)/%.o)

# Regra padrão para compilar o executável
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Regra para compilar os arquivos objeto
$(BUILDDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para limpar os arquivos gerados
clean:
	rm -rf $(BUILDDIR) $(TARGET)

# Regra para rodar o jogo
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run
