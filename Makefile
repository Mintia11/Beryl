TARGET ?= riscv64

NDEBUG ?= yes

KERNEL_NAME := bekrnl.elf

BUILD_DIR = build
ISO_DIR=$(BUILD_DIR)/iso_root
IMAGE_TARGET=$(BUILD_DIR)/Beryl.iso

KERNEL_ELF=$(BUILD_DIR)/$(KERNEL_NAME)

.PHONY: all
all: image

image: limine/limine $(IMAGE_TARGET)

$(IMAGE_TARGET): kernel limine_config
	@echo "Creating ISO image..."
	@rm -rf $(ISO_DIR)
	@mkdir -p $(ISO_DIR)/EFI/BOOT
	@mkdir -p $(ISO_DIR)/boot/limine
	@cp $(KERNEL_ELF) $(ISO_DIR)/boot
	@cp limine.conf limine/limine-uefi-cd.bin $(ISO_DIR)/boot/limine
	@cp -v limine/BOOTRISCV64.EFI $(ISO_DIR)/EFI/BOOT/
	@xorriso -as mkisofs \
		--efi-boot boot/limine/limine-uefi-cd.bin \
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		$(ISO_DIR) -o $(IMAGE_TARGET)

kernel: $(KERNEL_ELF)

$(KERNEL_ELF): FORCE
	@CC=clang LD=ld.lld TARGET=$(TARGET) NDEBUG=$(NDEBUG) $(MAKE) -C beryl

limine/limine: limine/limine.c
	@$(MAKE) -C limine

limine_config: limine.conf

FORCE: ;

ovmf/ovmf-code-$(TARGET).fd:
	mkdir -p ovmf
	curl -Lo $@ https://github.com/osdev0/edk2-ovmf-nightly/releases/latest/download/ovmf-code-$(KARCH).fd
	case "$(TARGET)" in \
		riscv64) dd if=/dev/zero of=$@ bs=1 count=0 seek=33554432 2>/dev/null;; \
	esac

ovmf/ovmf-vars-$(TARGET).fd:
	mkdir -p ovmf
	curl -Lo $@ https://github.com/osdev0/edk2-ovmf-nightly/releases/latest/download/ovmf-vars-$(KARCH).fd
	case "$(TARGET)" in \
		riscv64) dd if=/dev/zero of=$@ bs=1 count=0 seek=33554432 2>/dev/null;; \
	esac

run: image ovmf/ovmf-code-$(TARGET).fd ovmf/ovmf-vars-$(TARGET).fd
	@echo "Running in QEMU..."
ifeq ($(TARGET),riscv64)
	@qemu-system-$(TARGET) \
		-M virt \
		-cpu rv64 \
		-device ramfb \
		-device qemu-xhci \
		-device usb-kbd \
		-device usb-mouse \
		-drive if=pflash,unit=0,format=raw,file=ovmf/ovmf-code-$(TARGET).fd,readonly=on \
		-drive if=pflash,unit=1,format=raw,file=ovmf/ovmf-vars-$(TARGET).fd \
		-cdrom $(IMAGE_TARGET) \
		-serial stdio
endif

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR) $(ISO_DIR) $(IMAGE_TARGET)
	@$(MAKE) -C beryl clean