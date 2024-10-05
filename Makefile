CC:=gcc
CFLAGS:=-std=c11 -O2
IFLAGS:=-I./inc -I/usr/local/opt/ncurses/include
LFLAGS:=-L/usr/local/opt/ncurses/lib -lncurses

SRC_DIR:=./src
OBJ_DIR:=./obj
BIN_DIR:=./bin
SRC:=$(wildcard $(SRC_DIR)/*.c)
OBJ:=$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

all: $(OBJ)
	$(CC) $(OBJ) -o $(BIN_DIR)/pumpkin $(LFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $^ -o $@ $(CFLAGS) $(IFLAGS) -Wall


clean:
	rm $(BIN_DIR)/pumpkin
	rm $(OBJ)