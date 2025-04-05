ASM?=nasm
BUILD_DIR?=build

.PHONY: all clean

all: $(BUILD_DIR)/stage1.bin

$(BUILD_DIR)/stage1.bin:
	$(ASM) -f bin boot.asm -o $(BUILD_DIR)/boot.bin

clean:
	rm -f $(BUILD_DIR)/boot.bin