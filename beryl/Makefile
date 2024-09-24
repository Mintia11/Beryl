BUILD_DIR = ../build/beryl
SRC_DIR = src
INC_DIR = include
VENDOR_DIR = vendor

KERNEL_ELF = $(BUILD_DIR)/../bekrnl.elf

CFLAGS ?= -pipe -Wall -Wextra -DTARGET=$(TARGET) -DKERNEL $(DEFINES)
CPPFLAGS ?= -I $(INC_DIR) -I src/$(VENDOR_DIR) -DPRINTF_DISABLE_SUPPORT_FLOAT -DPRINTF_DISABLE_SUPPORT_EXPONENTIAL
LDFLAGS ?=

ifeq ($(NDEBUG),yes)
	CFLAGS += -O2
else
	CFLAGS += -O0 -g
endif

override CFLAGS +=               \
	-target riscv64-unknown-none \
	-fno-omit-frame-pointer      \
	-std=c11                     \
	-ffreestanding               \
	-fno-stack-protector         \
	-fno-stack-check             \
	-fno-lto                     \
	-fno-pie                     \
	-fno-pic                     \
	-MMD                         \
	-MP                          \
	-I.                          \
	-ffunction-sections          

override LDFLAGS +=         \
	-nostdlib               \
	-T linker-$(TARGET).ld  \
	-gc-sections               

ifeq ($(TARGET),riscv64)
override CFLAGS +=   \
	-march=rv64imac  \
	-mabi=lp64       \
	-mno-relax

override LDFLAGS +=  \
	-m elf64lriscv   \
	--no-relax
endif

override CFILES := $(shell find $(SRC_DIR) -not -path '*/.*' -not -path '*/arch/*' -type f -name '*.c')
override SFILES := $(shell find $(SRC_DIR) -not -path '*/.*' -not -path '*/arch/*' -type f -name '*.S')

override CFILES += $(shell find $(SRC_DIR) -path '*/arch/$(TARGET)/*' -type f -name '*.c')
override SFILES += $(shell find $(SRC_DIR) -path '*/arch/$(TARGET)/*' -type f -name '*.S')

override OBJ := $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(CFILES:.c=.o) $(ASFILES:.S=.o))
override HEADER_DEPS := $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(CFILES:.c=.d) $(ASFILES:.S=.d))

.PHONY: all
all: kernel

kernel: $(KERNEL_ELF)

$(KERNEL_ELF): $(OBJ)
	@printf "[LD]\tbekrnl.elf\n"
	@$(LD) $(OBJ) $(LDFLAGS) -o $@

-include $(HEADER_DEPS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@printf "[CC]\t$<\n"
	@mkdir -p $(dir $@)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.S
	@printf "[AS]\t$<\n"
	@mkdir -p $(dir $@)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@