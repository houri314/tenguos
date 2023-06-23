#Call this to build important files from host OS.
TENGU6_STANDALONE ?= yes

TENGULOADER_CFLAGS ?= -Ofast
TENGULOADER_LDFLAGS ?=

#For now Tengu6 is forced to compiled to be standalone.
TENGU6_CFLAGS ?= -Os
TENGU6_LDFLAGS ?= 

ifeq ($(strip $(TENGU6_STANDALONE)),yes)
override TENGU6_CFLAGS:=$(TENGU6_CFLAGS)\ -DTENGU6_STANDALONE
endif

IMAGE_NAME := tenguos

all: os-iso

#Download firmware for UEFI testing with QEMU.
ovmf:
	mkdir -p ovmf
	cd ovmf && curl -Lo OVMF-X64.zip https://efi.akeo.ie/OVMF/OVMF-X64.zip && unzip OVMF-X64.zip
 
limine:
	git clone https://github.com/limine-bootloader/limine.git --branch=v4.x-branch-binary --depth=1
	make -C limine/
	cp -f limine/limine.sys limine/limine-cd.bin limine/limine-cd-efi.bin iso-root/boot/

os-iso: limine tenguloader tengu6
	rm -f $(IMAGE).iso
	xorriso -as mkisofs -b boot/limine-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table \
		--efi-boot boot/limine-cd-efi.bin \
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		iso-root/ -o $(IMAGE_NAME).iso
	limine/limine-deploy $(IMAGE_NAME).iso

#Install OS loader to /boot.
tenguloader:
ifneq ($(strip $(TENGU6_STANDALONE)),yes)
	make -C iso-root/src/tenguloader \
		CFLAGS=$(TENGULOADER_CFLAGS) \
		LDFLAGS=$(TENGULOADER_LDFLAGS) install
endif

tengu6:
	make -C iso-root/src/tengu6 \
		CFLAGS=$(TENGU6_CFLAGS) \
		LDFLAGS=$(TENGU6_LDFLAGS) install

clean:
	rm -f $(IMAGE_NAME).iso
	make -C iso-root/src/tenguloader clean
	make -C iso-root/src/tengu6 clean
