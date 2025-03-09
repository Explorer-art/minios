ASM?=nasm
ASMFLAGS?=-f obj
CC16?=/usr/bin/watcom/binl/wcc
CFLAGS16?=-i=include -4 -d3 -s -wx -ms -zl -zq -za99
LD16?=/usr/bin/watcom/binl/wlink

BUILD_DIR?=build

SOURCES_C=$(wildcard *.c) $(wildcard libc/*.c)
SOURCES_ASM=$(wildcard *.asm)

OBJECTS_C=$(patsubst %.c, $(BUILD_DIR)/c/%.obj, $(SOURCES_C))
OBJECTS_ASM=$(patsubst %.asm, $(BUILD_DIR)/asm/%.obj, $(SOURCES_ASM))

.PHONY: all clean

all: program

program: $(BUILD_DIR)/program.bin

$(BUILD_DIR)/program.bin: $(OBJECTS_ASM) $(OBJECTS_C)
	$(LD16) NAME $(BUILD_DIR)/program.bin FILE \{ $(OBJECTS_ASM) $(OBJECTS_C) \} OPTION MAP=$(BUILD_DIR)/program.map @linker.ld

$(BUILD_DIR)/c/%.obj: %.c always
	$(CC16) $(CFLAGS16) -fo=$@ $<

$(BUILD_DIR)/asm/%.obj: %.asm always
	$(ASM) $(ASMFLAGS) $< -o $@

always:
	mkdir -p $(BUILD_DIR)/c/libc
	mkdir -p $(BUILD_DIR)/asm

clean:
	rm -f $(BUILD_DIR)/program.bin
