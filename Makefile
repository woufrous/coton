BIN			= coton

SRC			= main.c linalg.c photon.c atmosphere.c
OBJ			= $(SRC:%.c=%.o)

CFLAGS		+= -W -Wall -pedantic -O2 -flto -std=c99
LDFLAGS		+= -flto -lm

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) -o $@ $(LDFLAGS) $^

clean:
	rm $(OBJ) $(BIN)

.PHONY: all clean
