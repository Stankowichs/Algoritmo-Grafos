CPP = g++
CFLAGS = -Wall -O2

BIN_DIR = ../Bat1/
SRC_DIR = .
OBJ_DIR = $(BIN_DIR)obj

BIN = $(BIN_DIR)dijkstra.bin

$(BIN): $(SRC_DIR)/dijkstra.cpp | $(BIN_DIR)
	$(CPP) $(CFLAGS) -o $@ $<

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -f $(BIN)
	rm -rf $(OBJ_DIR)
