#Call this to build important files from host OS.

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

os-iso: limine tenguloader
	rm -f $(IMAGE).iso
	xorriso -as mkisofs -b boot/limine-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table \
		--efi-boot boot/limine-cd-efi.bin \
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		iso-root/ -o $(IMAGE_NAME).iso
	limine/limine-deploy $(IMAGE_NAME).iso

#Install OS loader to /boot
tenguloader:
	make -C iso-root/src/tenguloader install

clean:
	rm -f $(IMAGE_NAME).iso
	make -C iso-root/src/tenguloader clean
