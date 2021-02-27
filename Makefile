
.PHONY: all clean

KERNEL := ecos
ARCH := x86
WARNING := no
SERIAL_DEBUG := yes
KERNEL_NAME := $(KERNEL)_$(ARCH)

PROJDIRS := kernel drivers libraries systems components

C_SRCFILES := $(shell find $(PROJDIRS) -type f -name \*.c)
CXX_SRCFILES := $(shell find $(PROJDIRS) -type f -name \*.cpp)
HDRFILES := $(shell find $(PROJDIRS) -type f -name \*.h)
OBJFILES := $(patsubst %.c,%.o,$(C_SRCFILES)) $(patsubst %.cpp,%.o,$(CXX_SRCFILES))
ASMFILES := $(shell find $(PROJDIRS) -type f -name \*.asm)
ASMOBJFILES := $(patsubst %.asm,%.o,$(ASMFILES))

CC := i386-elf-gcc
CXX := i386-elf-g++
LD := i386-elf-ld
AR := ar
AS := as

ifeq ($(WARNING),yes)
	WARNINGS := -Wall -Wextra -Wshadow
	ASMWARNINGS := -W-all
else
	WARNINGS := -w
	ASMWARNINGS := -w-all
endif

ifeq ($(SERIAL_DEBUG),yes)
	SERIAL_DEBUG_DEFINE := -DSERIAL_DEBUG
else
	SERIAL_DEBUG_DEFINE :=
endif

CFLAGS := -g $(WARNINGS) $(SERIAL_DEBUG_DEFINE) -D$(ARCH) -I./ -mno-sse -nostdlib -nostdinc -nodefaultlibs -ffreestanding -m32
CXXFLAGS := $(CFLAGS) -fno-exceptions -fno-rtti

ifeq ($(ARCH),x86)
        LDFLAGS := -m elf_i386
				NASM_FLAGS := -f elf32
else
        LDFLAGS :=
				NASM_FLAGS :=
endif

run: iso
	@echo "[RUN  ] ..."
	@qemu-system-i386 -boot d -cdrom build/$(KERNEL_NAME)-live.iso -vga std -m 128 -serial stdio -no-acpi

iso: all
	@echo "[ISO  ] build/$(KERNEL_NAME)-live.iso"
	@mkisofs -quiet -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o ./build/$(KERNEL_NAME)-live.iso ./bin > /dev/null


all: $(OBJFILES) $(ASMOBJFILES)
	@echo "[LINK ] bin/$(KERNEL_NAME)"
	@$(LD) $(LDFLAGS) -o bin/$(KERNEL_NAME) $(OBJFILES) $(ASMOBJFILES) -T kernel/$(ARCH)/link.ld > /dev/null

%.o: %.c
	@echo "[BUILD .c  ] $<"
	@$(CC) -c $(CFLAGS) $(WARNINGS) -o $@ $<

%.o: %.cpp
	@echo "[BUILD .cpp] $<"
	@$(CC) -c $(CXXFLAGS) $(WARNINGS) -o $@ $<

%.o: %.asm
	@echo "[BUILD .asm] $<"
	@nasm $< -o $@ $(NASM_FLAGS) $(ASMWARNINGS)

clean:
	@-rm -rf $(OBJFILES) $(ASMOBJFILES) bin/$(KERNEL_NAME) build/$(KERNEL_NAME)-live.iso
