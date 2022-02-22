# ==========================================
# © 2020 EExuke. All Rights Reserved.
# ==========================================

BIN_TARGET = test

CFLAGS = -g -Wall
GTK_FLAGS = `pkg-config --cflags --libs gtk+-3.0`

$(BIN_TARGET):
	gcc *.c  -o $(BIN_TARGET) $(CFLAGS) $(GTK_FLAGS)

# Prevent naming conflicts such as the existence of a file named clean.
.PHONY: clean

clean:
	@rm -rf $(BIN_TARGET) *.o

