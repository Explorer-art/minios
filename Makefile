ASM = nasm

SRC_DIR = src
BUILD_DIR = build

.PHONY: all, bootloader, kernel, clean, always

all: $(BUILD_DIR)/minios.img

$(BUILD_DIR)/minios.img: bootloader kernel
	dd if=/dev/zero of=$(BUILD_DIR)/minios.img bs=512 count=2880
	mkfs.fat -F 12 -n "NBOS" $(BUILD_DIR)/minios.img
	dd if=$(BUILD_DIR)/bootloader.bin of=$(BUILD_DIR)/minios.img conv=notrunc
	mcopy -i $(BUILD_DIR)/minios.img $(BUILD_DIR)/kernel.bin "::kernel.bin"

bootloader: $(BUILD_DIR)/bootloader.bin

$(BUILD_DIR)/bootloader.bin: always
	$(ASM) -f bin $(SRC_DIR)/bootloader/boot.asm -o $(BUILD_DIR)/bootloader.bin

kernel: $(BUILD_DIR)/kernel.bin

$(BUILD_DIR)/kernel.bin: always
	$(ASM) -f bin $(SRC_DIR)/kernel/main.asm -o $(BUILD_DIR)/kernel.bin

always:
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)