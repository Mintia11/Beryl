KERNEL_ELF = kernel.elf

RUSTFLAGS := -Cforce-frame-pointers -Crelocation-model=static
CARGOFLAGS :=
OUT_DIR := target/

ifeq ($(TARGET),x86_64)
override CARGOFLAGS += \
	--target x86_64-unknown-none

override OUT_DIR += x86_64-unknown-none/
endif

ifeq ($(NDEBUG),yes)
override CARGOFLAGS += --profile dev

override OUT_DIR += debug/
else
override CARGOFLAGS += --profile release

override OUT_DIR += release/
endif

.PHONY: all
all: kernel

kernel: $(KERNEL_ELF)

FORCE: ;

$(KERNEL_ELF): FORCE
	env RUSTFLAGS="$(RUSTFLAGS)" cargo build $(CARGOFLAGS)
	cp $(shell echo $(OUT_DIR) | sed "s/ //g")$(shell echo $(KERNEL_ELF) | sed "s/.elf//") $(KERNEL_ELF)