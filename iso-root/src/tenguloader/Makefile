CC := gcc
LD := ld

LDFLAGS ?=
CFLAGS ?=

DEF_LDFLAGS := \
		-nostdlib\
		-static\
		-m elf_x86_64\
		-z max-page-size=0x1000\
		-T linker.ld

DEF_CFLAGS := \
    -Wall \
    -std=gnu11 \
    -ffreestanding \
    -fno-stack-protector \
    -fno-stack-check \
    -fno-lto \
    -fno-PIE \
    -fno-PIC \
    -m64 \
    -march=x86-64 \
    -mabi=sysv \
    -mno-80387 \
    -mno-mmx \
    -mno-sse \
    -mno-sse2 \
    -mno-red-zone \
    -mcmodel=kernel \
		-I../../usr/include

override LDFLAGS += $(DEF_LDFLAGS)
override CFLAGS += $(DEF_CFLAGS)

OBJ := main.o string.o console.o

tenguloader.elf: $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) -o $@

%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@

clean:
	rm -f tenguloader.elf
	rm -f $(OBJ)

install: tenguloader.elf
	mv $< ../../boot
