# ==========================================
# © 2020 EExuke. All Rights Reserved.
# ==========================================

DIR_OBJ = ./obj
DIR_SRC = ./src
INC_SRC = -I./inc

LD_LIBS = -ljansson -lm #-lcurl #-lsqlite3
#gcc
#INC_SRC += -I/home/xuke/Downloads/jansson-2.13.1/src
#DIR_LIB += -L/usr/local/lib
#arm-linux-gcc
#INC_SRC += -I/home/xuke/workspace/ir8/system/jansson-2.13.1/src
#DIR_LIB += -L/home/xuke/workspace/ir8/system/target/IR8-qcom-ipq4029/usr/lib

SRC = $(wildcard ${DIR_SRC}/*.c)
OBJ = $(patsubst %.c, ${DIR_OBJ}/%.o, $(notdir $(SRC)))

BIN_TARGET = test

#CC = arm-linux-gcc
#CC = mipsel-linux-gcc
CC = gcc
CFLAGS = -g -Wall $(INC_SRC) -ljansson
GTK_FLAGS = `pkg-config --cflags --libs gtk+-3.0`

${BIN_TARGET}: ${OBJ}
	$(warning Building $(BIN_TARGET) ...)
	@$(CC) $(OBJ) -o $@ $(LD_LIBS) $(DIR_LIB) -pthread $(GTK_FLAGS)

${DIR_OBJ}/%.o: ${DIR_SRC}/%.c
	$(warning Comping $< ...)
	@$(CC) $(CFLAGS) -c $< -o $@ $(GTK_FLAGS)

# Prevent naming conflicts such as the existence of a file named clean.
.PHONY: clean

clean:
	@find ${DIR_OBJ} -name *.o -exec rm -rf {} \;
	@rm -rf $(BIN_TARGET)

