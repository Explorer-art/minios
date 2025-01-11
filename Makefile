ASM=nasm

SRC_DIR=src
BUILD_DIR=build
FLOPPY_IMAGE=minios.img

.PHONY: all bootloader kernel clean always

all: clean $(FLOPPY_IMAGE)

$(FLOPPY_IMAGE): $(BUILD_DIR)/$(FLOPPY_IMAGE)

$(BUILD_DIR)/$(FLOPPY_IMAGE): bootloader
	dd if=/dev/zero of=$(BUILD_DIR)/$(FLOPPY_IMAGE) bs=512 count=2880
	mkfs.fat -F 12 -n "NBOS" $(BUILD_DIR)/$(FLOPPY_IMAGE)
	dd if=$(BUILD_DIR)/stage1.bin of=$(BUILD_DIR)/$(FLOPPY_IMAGE) conv=notrunc
	mcopy -i $(BUILD_DIR)/$(FLOPPY_IMAGE) $(BUILD_DIR)/stage2.bin "::stage2.bin"
	mcopy -i $(BUILD_DIR)/$(FLOPPY_IMAGE) file.txt "::file.txt"
	mmd -i $(BUILD_DIR)/$(FLOPPY_IMAGE) "::dir"
	mcopy -i $(BUILD_DIR)/$(FLOPPY_IMAGE) file.txt "::dir/file.txt"

#
# Bootloader
#

bootloader: stage1 stage2

stage1: $(BUILD_DIR)/stage1.bin

$(BUILD_DIR)/stage1.bin: always
	$(MAKE) -C $(SRC_DIR)/bootloader/stage1 BUILD_DIR=$(abspath $(BUILD_DIR))

stage2: $(BUILD_DIR)/stage2.bin

$(BUILD_DIR)/stage2.bin: $(BUILD_DIR)/stage2.bin
	$(MAKE) -C $(SRC_DIR)/bootloader/stage2 BUILD_DIR=$(abspath $(BUILD_DIR))

#
# Kernel
#

kernel: $(BUILD_DIR)/kernel.bin

$(BUILD_DIR)/kernel.bin: always
	$(MAKE) -C $(SRC_DIR)/kernel BUILD_DIR=$(abspath $(BUILD_DIR))

#
# Protected Mode Bootloader
#

pmode: clean always
	nasm -f bin boot.asm -o $(BUILD_DIR)/bootloader.bin
	dd if=/dev/zero of=$(BUILD_DIR)/$(FLOPPY_IMAGE) bs=512 count=2880
	mkfs.fat -F 12 -n "NBOS" $(BUILD_DIR)/$(FLOPPY_IMAGE)
	dd if=$(BUILD_DIR)/bootloader.bin of=$(BUILD_DIR)/$(FLOPPY_IMAGE) conv=notrunc

always:
	mkdir -p $(BUILD_DIR)

clean:
	$(MAKE) -C $(SRC_DIR)/bootloader/stage1 BUILD_DIR=$(abspath $(BUILD_DIR)) clean
	$(MAKE) -C $(SRC_DIR)/bootloader/stage2 BUILD_DIR=$(abspath $(BUILD_DIR)) clean
	rm -rf $(BUILD_DIR)/*
