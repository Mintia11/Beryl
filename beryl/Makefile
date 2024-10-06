BUILD_DIR = ../build/beryl
SRC_DIR = src
INC_DIR = include
VENDOR_DIR = vendor

KERNEL_ELF = $(BUILD_DIR)/../bekrnl.elf

CFLAGS ?= -std=c11 -pipe -Wall -Wextra -DTARGET=$(TARGET) -DKERNEL -DNDEBUG=$(NDEBUG)
CPPFLAGS ?= -I $(INC_DIR) -I src/$(VENDOR_DIR) -DPRINTF_DISABLE_SUPPORT_FLOAT -DPRINTF_DISABLE_SUPPORT_EXPONENTIAL
LDFLAGS ?=

ifeq ($(NDEBUG),yes)
	CFLAGS += -O0 -g
else
	CFLAGS += -O2
endif

override CFLAGS +=               \
	-fno-omit-frame-pointer      \
	-std=gnu23                   \
	-ffreestanding               \
	-fno-stack-protector         \
	-fno-stack-check             \
	-fno-lto                     \
	-fno-pic                     \
	-MMD                         \
	-MP                          \
	-I.                          \
	-ffunction-sections          \
	-fdata-sections              

override LDFLAGS +=         \
	-nostdlib               \
	-T linker-$(TARGET).ld  \
	-gc-sections            \
	-static

ifeq ($(TARGET),riscv64)
override CFLAGS +=   \
	-target riscv64-unknown-none \
	-march=rv64imac  \
	-mabi=lp64       \
	-mno-relax

override LDFLAGS +=  \
	-m elf64lriscv   \
	--no-relax
endif

ifeq ($(TARGET),x86_64)
override CFLAGS +=			    \
	-target x86_64-unknown-none \
	-m64 						\
    -march=x86-64 				\
    -mno-80387 					\
    -mno-mmx 					\
    -mno-sse 					\
    -mno-sse2 					\
    -mno-red-zone 				\
    -mcmodel=kernel

override LDFLAGS +=  \
	-m elf_x86_64

override ASMFLAGS += \
	-F dwarf -g -f elf64
endif

override CFILES := $(shell find $(SRC_DIR) -not -path '*/.*' -not -path '*/arch/*' -type f -name '*.c')
override SFILES := $(shell find $(SRC_DIR) -not -path '*/.*' -not -path '*/arch/*' -type f -name '*.S')

override CFILES += $(shell find $(SRC_DIR) -path '*/arch/$(TARGET)/*' -type f -name '*.c')
override ASFILES += $(shell find $(SRC_DIR) -path '*/arch/$(TARGET)/*' -type f -name '*.S')

ifeq ($(TARGET),x86_64)
override ASMFILES := $(shell find $(SRC_DIR) -path '*/arch/$(TARGET)/*' -type f -name '*.asm')
endif

override OBJ := $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(CFILES:.c=.c.o) $(ASFILES:.S=.S.o))

ifeq ($(TARGET),x86_64)
override OBJ += $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(ASMFILES:.asm=.asm.o))
endif

override HEADER_DEPS := $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(CFILES:.c=.d) $(ASFILES:.S=.d))

.PHONY: all
all: kernel

kernel: $(KERNEL_ELF)

$(KERNEL_ELF): $(OBJ)
	@printf "[LD]\tbekrnl.elf\n"
	@$(LD) $(OBJ) $(LDFLAGS) -o $@

-include $(HEADER_DEPS)

$(BUILD_DIR)/%.c.o: $(SRC_DIR)/%.c
	@printf "[CC]\t$<\n"
	@mkdir -p $(dir $@)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.S.o: $(SRC_DIR)/%.S
	@printf "[AS]\t$<\n"
	@mkdir -p $(dir $@)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

ifeq ($(TARGET),x86_64)
$(BUILD_DIR)/%.asm.o: $(SRC_DIR)/%.asm
	@printf "[NASM]\t$<\n"
	@mkdir -p $(dir $@)
	@nasm $(ASMFLAGS) $< -o $@
endif