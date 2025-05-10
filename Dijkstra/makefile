CPP = g++
CFLAGS = -std=c++11 -Wall

SRC = dijkstra.cpp
BIN_DIR = ../bat1/
OUT = $(BIN_DIR)dijkstra.bin

all: $(OUT)

$(OUT): $(SRC)
	@mkdir -p $(BIN_DIR)
	$(CPP) $(CFLAGS) -o $@ $<

clean:
	rm -f $(OUT)