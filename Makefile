CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lglfw -lGL -lGLEW

TARGET = conway
SRCS = main.c conway.c utils.c
BIN_DIR = bin

all: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(SRCS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$(TARGET) $(SRCS) $(LDFLAGS)

run: $(BIN_DIR)/$(TARGET)
	./$(BIN_DIR)/$(TARGET)

clean:
	rm -f $(BIN_DIR)/$(TARGET)
