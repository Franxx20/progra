TARGET = $(BIN_DIR)/myproj
OBJ_DIR = ../obj
BIN_DIR = ../bin
INC_DIR = ../inc
OBJS = $(OBJ_DIR)/main.o \
			 $(OBJ_DIR)/com.o \
			 $(OBJ_DIR)/diag.o \
			 $(OBJ_DIR)/init.o

SRC_DIR = .
CFLAGS = -g -Wall -I$(INC_DIR)

$(TARGET) : $(OBJS)
	mkdir -p $(BIN_DIR)
	gcc $(CFLAGS) $(OBJS) -o $(TARGET)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	gcc -c $(CFLAGS) $< -o $@

.PHONY : clean
clean: 
	rm -r $(OBJ_DIR) $(BIN_DIR)
