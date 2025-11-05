FILE ?= main

SRC_DIR = src
BUILD_DIR = build

LIB_DIR = /usr/lib/avr/include/
INCLUDE_FLAGS = -I$(LIB_DIR)

SRC = $(filter-out $(SRC_DIR)/$(FILE).c, $(wildcard $(SRC_DIR)/*.c))
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))
ELF = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.elf, $(SRC))
BIN = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.bin, $(SRC))

MMCU = atmega328p

CFLAGS = -mmcu=$(MMCU) -Os

ifdef USE_RANDOM
CFLAGS += -DUSE_RANDOM
endif

default: all

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	avr-gcc $(CFLAGS) $(INCLUDE_FLAGS) -c -o $@ $<

$(BUILD_DIR)/$(FILE).elf: $(OBJ)
	avr-gcc $(CFLAGS) $(INCLUDE_FLAGS) -o $@ $(SRC_DIR)/$(FILE).c $^

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf
	avr-objcopy -O binary $< $@ 

install: build $(BUILD_DIR)/$(FILE).bin
	avrdude -p $(MMCU) -c usbasp -P /dev/ttyACM0 -U flash:w:$(BUILD_DIR)/$(FILE).bin

build: _build $(BUILD_DIR)/$(FILE).elf

_build:
	mkdir -p $(BUILD_DIR)

com: 
	minicom -b 38400 -o -D /dev/ttyACM0

clean:
	rm -rf $(BUILD_DIR)

all: build
