VERSION = 1.0.0
OS_NAME = omphalos
EXEC = kernel
BIN_PATH = archx86/
SRC_PATH = src/
OBJ_PATH = build/
KERNEL_BIN = $(BIN_PATH)boot/kernel.bin
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, build/%.o, $(SRC))
ASM = $(patsubst src/%.asm, build/%.o, $(SRC))

CC = gcc
ASSEMBLER = nasm
LINKER = ld
EMULATOR = qemu-system-i386

ASFLAGS = -f elf32
CFLAGS = -m32 -ffreestanding
LDFLAGS= -m elf_i386 -T $(SRC_PATH)link.ld
EMULATOR_FLAGS = -kernel

run: all
	$(EMULATOR) $(EMULATOR_FLAGS) $(KERNEL_BIN)

test:
	$(EMULATOR) $(EMULATOR_FLAGS) $(KERNEL_BIN)

all: header $(EXEC) asm
	@mkdir -p archx86/
	@mkdir -p archx86/boot/grub/
	@cp grub.cfg archx86/boot/grub/grub.cfg
	$(LINKER) $(LDFLAGS) -o $(KERNEL_BIN) $(OBJ_PATH)kasm.o $(OBJ)

kernel: $(OBJ)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) -I./include -o $@ -c $< $(CFLAGS)

asm: $(OBJ_PATH)kasm.o

$(OBJ_PATH)kasm.o: $(SRC_PATH)kernel.asm
	$(ASSEMBLER) $(ASFLAGS) -o $(OBJ_PATH)kasm.o $(SRC_PATH)kernel.asm

build: all
	grub-mkrescue -o $(OS_NAME).iso $(BIN_PATH)

header:
	@figlet $(OS_NAME)
	@echo "\n"
	$(info version $(VERSION))
	$(info author NotBad4U)
	$(info https://github.com/NotBad4U)

.PHONY: clean mrproper

clean:
	@rm -rf $(OBJ_PATH)*.o

mrproper: clean
	@rm -rf $(BIN_PATH)
