CC = avr-gcc
MCU = atmega328p
CFLAGS = -mmcu=$(MCU) -Wall -Os

PROGRAM_NAME = Proj1

BUILD_DIR = build
CODE_DIR = code

INCLUDES = $(sort $(shell find $(CODE_DIR) -type f -name '*.h' -printf "%h\n"))
INC_FLAGS = $(patsubst %, -I%, $(INCLUDES))

SOURCES = $(shell find $(CODE_DIR) -type f -name '*.c')
OBJS = $(subst $(CODE_DIR), $(BUILD_DIR), $(patsubst %.c, %.o, $(SOURCES)))
DEPENDS = $(patsubst %.c, %.o, $(OBJS))


$(PROGRAM_NAME): $(OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$(PROGRAM_NAME).elf $^ -Xlinker -Map=$(BUILD_DIR)/$(PROGRAM_NAME).map
	avr-objcopy -j .text -j .data -O ihex $(BUILD_DIR)/$(PROGRAM_NAME).elf $(BUILD_DIR)/$(PROGRAM_NAME).hex

$(BUILD_DIR):
	mkdir -pv $(BUILD_DIR)

-include $(patsubst %.o, %.d, $(OBJS))

$(BUILD_DIR)/%.o: $(CODE_DIR)/%.c
	mkdir -pv $(dir $@)
	$(CC) $(CFLAGS) $(INC_FLAGS) -MMD -MP -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

upload:
	avrdude -c usbasp-clone -p $(MCU) -U flash:w:$(BUILD_DIR)/$(PROGRAM_NAME).hex

fuse_read:
	avrdude -c usbasp-clone -p $(MCU) -U lfuse:r:-:h -U hfuse:r:-:h -U efuse:r:-:h