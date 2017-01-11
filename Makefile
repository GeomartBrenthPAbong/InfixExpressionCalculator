INC_PATH := include
SRC_PATH := src
OBJ_PATH := objs
BIN_PATH := bin

OPTIONS := -std=c++11
CC := g++
DEBUG := -g
CFLAGS := -Wall -c $(DEBUG) $(OPTIONS)
LFLAGS := -Wall $(DEBUG)

PLATFORM ?= linux
MODE ?= debug
NAME ?= Calculator

CPP_FILES := $(wildcard $(SRC_PATH)/*.cpp)

CPP_FILES := $(CPP_FILES:$(SRC_PATH)/LinkedListQueue.cpp=)
CPP_FILES := $(CPP_FILES:$(SRC_PATH)/QueueNode.cpp=)

OBJ_FILES := $(addprefix $(OBJ_PATH)/, $(notdir $(CPP_FILES:.cpp=.o)))

TEMPLATED_FILES := LinkedListQueue.hpp QueueNode.hpp
TEMPLATED_HPP_FILES := $(addprefix $(INC_PATH)/, $(TEMPLATED_FILES))
TEMPLATED_OBJ_FILES := $(addprefix $(OBJ_PATH)/_, $(notdir $(TEMPLATED_HPP_FILES:.hpp=.o)))

all: build$(PLATFORM)

buildlinux: $(BIN_PATH)/$(MODE)/$(NAME) clean

buildwindows: $(BIN_PATH)/$(MODE)/$(NAME).exe clean_windows

$(BIN_PATH)/$(MODE)/$(NAME).exe: $(OBJ_FILES)
	$(CC) $(LFLAGS) -o $@ $^

$(BIN_PATH)/$(MODE)/$(NAME): $(OBJ_FILES)
	$(CC) $(LFLAGS) -o $@ $^

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
	$(CC) $(CFLAGS) -I$(INC_PATH) -I$(SRC_PATH) -o $@ $<

$(OBJ_PATH)/_%.o: $(INC_PATH)/%.hpp
	$(CC) $(CFLAGS) -I$(INC_PATH) -I$(SRC_PATH) -o $@ $<

.PHONY: print-% clean_all

print-%: ; @echo $* = $($*)

clean:
	rm -f $(OBJ_PATH)/*.o

clean_windows:
	del /Q $(OBJ_PATH)\*.o

clean_all: clean
	rm -f $(BIN_PATH)/$(MODE)/*

clean_all_windows: clean_windows
	del /Q $(BIN_PATH)\$(MODE)\*
