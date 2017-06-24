SRC_DIR = src
HEADERS_DIR = include
OBJ_DIR = obj
#COMP = g++
#EXE = exe
DIRECTIVES = -Wall -std=c++11 -I$(HEADERS_DIR)

CPP_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(addprefix $(OBJ_DIR)/,$(notdir $(CPP_FILES:.cpp=.o)))
HPP_FILES = $(wildcard $(HEADERS_DIR)/*.hpp)


all: obj_dir compile


#cria os arquivos .o
obj/%.o : src/%.cpp $(HPP_FILES)
	g++ -c -o $@ $< $(DIRECTIVES)

#junta os .o em um arquivo executavel
compile: $(OBJ_FILES)
	g++ -o exe $^

#cria a pasta para os arquivos .o caso nao exista
obj_dir :
	mkdir -p obj

#compila e roda o programa
run : all
	./exe

#deleta a pasta dos arquivos .o e o executavel
clean :
	rm -f -r obj
	rm -f exe

###########################################################################