# TODO Generalizar esse makefile para o diretório examples/
# TODO Melhorar esse makefile

CC=gcc
CC_FLAGS=-c -Wall -DDEBUG=1
LD_FLAGS=
C_FILES=$(wildcard src/*.c)
DIRS=obj
OBJ_FILES=$(addprefix obj/,$(notdir $(C_FILES:.c=.o)))

all: $(DIRS) btree

btree: $(OBJ_FILES) 
	$(CC) $(LD_FLAGS) $^ -o $@

obj/%.o: src/%.c
	$(CC) $(CC_FLAGS) $< -o $@

$(DIRS):
	mkdir -p $(DIRS)

clean:
	rm -f -r obj/ btree
