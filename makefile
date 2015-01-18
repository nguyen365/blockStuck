COMP = g++
SOURCES = $(wildcard $(SRC)*.cpp)
SDL_LIB = -L/usr/local/lib -Wl,-rpath=/usr/local/lib
SDL_INCLUDE = -I/usr/local/include -D_GNU_SOURCE=1 -D_REENTRANT
#COMP_FLAGS = -Wall -c -std=c++11 $(SDL_INCLUDE)
OBJECTS = $(subst $(SRC),$(OBJ), $(patsubst %.cpp,%.o, $(SOURCES)))
SDL_LIB = -lSDL2 -lSDL2_image
LIB_FLAGS = -Wall -std=c++11 $(SDL_LIB) $(SDL_INCLUDE)
COMP_FLAGS = -Wall -c -std=c++11 $(SDL_LIB)
EXE = blockStuck
BIN = ./bin/
OBJ = ./obj/
SRC = ./src/

all: $(BIN)$(EXE)

$(BIN)$(EXE): $(OBJECTS)
	$(COMP) $(OBJECTS) -o $@ $(LIB_FLAGS)

$(OBJ)%.o: $(SRC)%.cpp
	$(COMP) $(COMP_FLAGS) $< -o $(subst $(SRC), $(OBJ), $@)

clean:
#rm $(wildcard $(OBJ)*.o) && rm $(BIN)$(EXE) && rm $(wildcard $(SRC)*.o)
	rm $(OBJECTS)
	rm $(BIN)$(EXE)
	rm $(wildcard $(SRC)*~)
