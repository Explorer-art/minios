BUILD_DIR?=build
ASM?=nasm

.PHONY: all clean

all: kernel

kernel: $(BUILD_DIR)/main.bin

$(BUILD_DIR)/main.bin:
	$(ASM) -f bin main.asm -o $(BUILD_DIR)/kernel.bin

clean:
	rm -f $(BUILD_DIR)/kernel.bin