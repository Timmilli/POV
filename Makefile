.PHONY = clean build install os

FILE ?= main

SRC_DIR = src
BUILD_DIR = build

LIB_DIR = /usr/lib/avr/include/
INCLUDE_FLAGS = -I$(LIB_DIR)

SRC = $(filter-out $(SRC_DIR)/$(FILE).c, $(wildcard $(SRC_DIR)/*.c))
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))
ELF = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.elf, $(SRC))
BIN = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.bin, $(SRC))

MMCU=atmega328p

ifeq ($(OS),Windows_NT)
  BINARY_TYPE = ihex
  PORT = ''
  FLASH_FILE = flash:w:$<:i
  MKDIR_FLAG = $(BUILD_DIR)
  CLEAN_CLI = @if exist $(BUILD_DIR) rd /s /q $(BUILD_DIR)
  BUILD_CLI = if not exist $(BUILD_DIR) mkdir $(BUILD_DIR) 
else
  BINARY_TYPE = binary
  PORT = -P /dev/ttyACM0
  FLASH_FILE = flash:w:$<
  MKDIR_FLAG = -p $(BUILD_DIR)
  CLEAN_CLI = rm -rf $(BUILD_DIR)
  BUILD_CLI = mkdir -p $(BUILD_DIR) 
endif


default: all

os:
	@echo $(OS)
	@echo $(BINARY_TYPE)
	@echo $(PORT)
	@echo $(FLASH_FILE)
	@echo $(MKDIR_FLAG)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	avr-gcc $(CFLAGS) $(INCLUDE_FLAGS) -c -o $@ $<

$(BUILD_DIR)/$(FILE).elf: $(OBJ)
	avr-gcc $(CFLAGS) $(INCLUDE_FLAGS) -o $@ $(SRC_DIR)/$(FILE).c $^

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf
	avr-objcopy -O $(BINARY_TYPE) $< $@ 

install: $(BUILD_DIR)/$(FILE).bin
	avrdude -p atmega328p -c usbasp $(PORT) -U $(FLASH_FILE)

build: _build $(BUILD_DIR)/$(FILE).elf

_build:
	$(BUILD_CLI)
	
com: 
	minicom -b 38400 -o -D /dev/ttyACM0

clean:
	$(CLEAN_CLI)
	
all: build install
