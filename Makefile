.PHONY: all clean

#compiler flags
CC = g++
CFLAGS = -Wall -g -I $(CURDIR)/include/ -D MESSAGING_SERVICE_DEBUG 

#directories
SRC_DIR = $(CURDIR)/src/
OBJ_DIR = $(CURDIR)/obj/
BIN_DIR = $(CURDIR)/bin/

#final executable
EXEC = $(BIN_DIR)/messaging_service

#sources and objects
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

#building the executable from object files
$(EXEC): $(OBJECTS) 
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXEC)

#building object files from source files
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS)-c $< -o $@

objects: $(OBJECTS)

all: $(EXEC)

clean:
	rm -f $(EXEC) $(OBJ_DIR)/*.o

