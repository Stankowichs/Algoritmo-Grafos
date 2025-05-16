CPP = g++
CFLAGS = -std=c++11 -Wall

SRC = floydwarshall.cpp
BIN_DIR = ../Floyd-Warshall/
OUT = $(BIN_DIR)floydwarshall.bin

all: $(OUT)

$(OUT): $(SRC)
	@mkdir -p $(BIN_DIR)
	$(CPP) $(CFLAGS) -o $@ $<

clean:
	rm -f $(OUT)