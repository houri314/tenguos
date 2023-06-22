#Call this to build important files from host OS.

TENGULOADER_CFLAGS ?= -Ofast
TENGULOADER_LDFLAGS ?=

TENGU6_CFLAGS ?= -Os
TENGU6_LDFLAGS ?= 

IMAGE_NAME := tenguos

all: os-iso

#Download firmware for UEFI testing with QEMU
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

#Install OS loader to /boot
tenguloader:
	make -C iso-root/src/tenguloader \
		CFLAGS=$(TENGULOADER_CFLAGS) \
		LDFLAGS=$(TENGULOADER_LDFLAGS) install

tengu6:
	make -C iso-root/src/tengu6 \
		CFLAGS=$(TENGU6_CFLAGS) \
		LDFLAGS=$(TENGU66_CFLAGS) install

clean:
	rm -f $(IMAGE_NAME).iso
	make -C iso-root/src/tenguloader clean
	make -C iso-root/src/tengu6 clean
