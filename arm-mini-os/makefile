# Compilation tools
CC=gcc
AS=as
LD=ld
OBJCOPY=objcopy
OBJDUMP=objdump

# Directories
BUILD_DIR = build
SOURCE_DIR = source

# Assembler & linker files
LINKER_SCRIPT = kernel.ld
LISTING_FILE = kernel.list
MAP_FILE = kernel.map

# Output TinyOS image, fully-packaged
OUTPUT_IMAGE = kernel.img

COPTS = \
  -std=c11 \
  -march=armv6 \
  -mtune=arm1176jzf-s \
  -mfloat-abi=hard \
  -ffast-math

OBJECTS_AS := $(patsubst $(SOURCE_DIR)/%.s,$(BUILD_DIR)/%.o,$(wildcard $(SOURCE_DIR)/*.s))
OBJECTS_GCC := $(patsubst $(SOURCE_DIR)/%.c,$(BUILD_DIR)/%.o,$(wildcard $(SOURCE_DIR)/*.c))
OBJECTS := $(OBJECTS_AS) $(OBJECTS_GCC)



all: $(OUTPUT_IMAGE) $(LISTING_FILE) $(OBJECTS_GCC)

# Rule to make the object files from C source.
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) -I $(SOURCE_DIR) $< -c $(COPTS) -o $@

# Rule to make the listing file.
$(LISTING_FILE): $(BUILD_DIR)/output.elf
	$(OBJDUMP) -d $(BUILD_DIR)/output.elf > $(LISTING_FILE)

# Rule to make the image file.
$(OUTPUT_IMAGE): $(BUILD_DIR)/output.elf
	$(OBJCOPY) $(BUILD_DIR)/output.elf -O binary $(OUTPUT_IMAGE)

# Rule to make the elf file.
$(BUILD_DIR)/output.elf: $(OBJECTS) $(LINKER_SCRIPT)
	$(LD) --no-undefined $(OBJECTS) -Map $(MAP_FILE) -o $(BUILD_DIR)/output.elf -T $(LINKER_SCRIPT)

# Rule to make the object files from Assembly sources.
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.s
	$(AS) -I $(SOURCE_DIR)/ $< -mfpu=vfpv2 -o $@

# Rule to clean files.
clean:
	-rm -f $(BUILD_DIR)/*.o
	-rm -f $(BUILD_DIR)/output.elf
	-rm -f $(OUTPUT_IMAGE)
	-rm -f $(LISTING_FILE)
	-rm -f $(MAP_FILE)

c: clean

rebuild: c all
r: rebuild
