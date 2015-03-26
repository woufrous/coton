BIN			= coton

SRC			= main.c linalg.c photon.c atmosphere.c
OBJ			= $(SRC:%.c=%.o)

CFLAGS		+= -W -Wall -g -O2 -fPIC -std=c99
CFLAGS		+= -pedantic
LDFLAGS		+= -lm

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) -o $@ $(LDFLAGS) $^

clean:
	rm $(OBJ) $(BIN)

.PHONY: all clean
