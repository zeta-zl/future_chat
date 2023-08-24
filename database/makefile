CC = g++
CFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS = -lsqlite3

SRC_DIR = ./database_operations
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(SRC_DIR)/%.o,$(SRC_FILES))

PLATFORM = $(shell uname)

ifeq ($(PLATFORM), Linux)
    ADDITIONAL_SRC_DIR = ./database_operations_linux
else ifeq ($(PLATFORM), Windows)
    ADDITIONAL_SRC_DIR = ./database_operations_windows
endif

ADDITIONAL_SRC_FILES = $(wildcard $(ADDITIONAL_SRC_DIR)/*.cpp)
ADDITIONAL_OBJ_FILES = $(patsubst $(ADDITIONAL_SRC_DIR)/%.cpp,$(ADDITIONAL_SRC_DIR)/%.o,$(ADDITIONAL_SRC_FILES))

all: init_database test_database

init_database: $(OBJ_FILES) $(ADDITIONAL_OBJ_FILES) $(SRC_DIR)/init_database.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test_database: $(OBJ_FILES) $(ADDITIONAL_OBJ_FILES) $(SRC_DIR)/test_database.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/database_operations.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(ADDITIONAL_SRC_DIR)/%.o: $(ADDITIONAL_SRC_DIR)/%.cpp $(SRC_DIR)/database_operations.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f init_database test_database $(SRC_DIR)/*.o $(ADDITIONAL_SRC_DIR)/*.o

