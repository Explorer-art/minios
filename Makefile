ASM=nasm

BUILD_DIR=build
FLOPPY_IMAGE=minios.img

.PHONY: all bootloader kernel clean always

all: clean $(FLOPPY_IMAGE)

$(FLOPPY_IMAGE): $(BUILD_DIR)/$(FLOPPY_IMAGE)

$(BUILD_DIR)/$(FLOPPY_IMAGE): bootloader kernel program
	dd if=/dev/zero of=$(BUILD_DIR)/$(FLOPPY_IMAGE) bs=512 count=2880
	mkfs.fat -F 12 -n "NBOS" $(BUILD_DIR)/$(FLOPPY_IMAGE)
	dd if=$(BUILD_DIR)/boot.bin of=$(BUILD_DIR)/$(FLOPPY_IMAGE) conv=notrunc
	mcopy -i $(BUILD_DIR)/$(FLOPPY_IMAGE) $(BUILD_DIR)/kernel.bin "::kernel.bin"
	mcopy -i $(BUILD_DIR)/$(FLOPPY_IMAGE) file.txt "::file.txt"
	mcopy -i $(BUILD_DIR)/$(FLOPPY_IMAGE) $(BUILD_DIR)/program.bin "::program.bin"
	mmd -i $(BUILD_DIR)/$(FLOPPY_IMAGE) "::dir"
	mcopy -i $(BUILD_DIR)/$(FLOPPY_IMAGE) file.txt "::dir/file.txt"

#
# Bootloader
#

bootloader: $(BUILD_DIR)/boot.bin

$(BUILD_DIR)/boot.bin: always
	$(MAKE) -C bootloader BUILD_DIR=$(abspath $(BUILD_DIR))

#
# Kernel
#

kernel: $(BUILD_DIR)/kernel.bin

$(BUILD_DIR)/kernel.bin:
	$(MAKE) -C kernel BUILD_DIR=$(abspath $(BUILD_DIR))

#
# Userland
#

program: $(BUILD_DIR)/program.bin

$(BUILD_DIR)/program.bin:
	$(MAKE) -C userland-assembly BUILD_DIR=$(abspath $(BUILD_DIR))

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
	$(MAKE) -C bootloader BUILD_DIR=$(abspath $(BUILD_DIR)) clean
	$(MAKE) -C kernel BUILD_DIR=$(abspath $(BUILD_DIR)) clean
	rm -rf $(BUILD_DIR)/*
