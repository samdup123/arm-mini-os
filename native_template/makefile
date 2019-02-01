# The toolchain to use. arm-none-eabi works, but there does exist 
# arm-bcm2708-linux-gnueabi. ARMGNU ?= arm-none-eabi

CC=arm-none-eabi-gcc
AS=arm-none-eabi-as
LD=arm-none-eabi-ld
OBJCOPY=arm-none-eabi-objcopy
OBJDUMP=arm-none-eabi-objdump

BUILD_DIR = build/
SOURCE_DIR = source/

LIST = kernel.list    # output listing file
MAP = kernel.map      # output map file
LINKER = kernel.ld    # linker script

TARGET = kernel.img   # name of fully-packaged TinyOS image

# The names of all object files that must be generated. Deduced from the 
# c and assembly code files in source.

OBJECTS_AS := $(patsubst $(SOURCE_DIR)%.s,$(BUILD_DIR)%.o,$(wildcard $(SOURCE_DIR)*.s))
OBJECTS_GCC := $(patsubst $(SOURCE_DIR)%.c,$(BUILD_DIR)%.o,$(wildcard $(SOURCE_DIR)*.c))
OBJECTS := $(OBJECTS_AS) $(OBJECTS_GCC)

# Rule to make everything.
all: $(TARGET) $(LIST) $(OBJECTS_GCC)

# Rule to remake everything. Does not include clean.
rebuild: all

# Rule to make the object files from C source.
$(BUILD_DIR)%.o: $(SOURCE_DIR)%.c
	$(CC) -I $(SOURCE_DIR) $< -c -std=gnu99 -march=armv6 -mtune=arm1176jzf-s -mfloat-abi=hard -ffast-math -o $@

# Rule to make the listing file.
$(LIST) : $(BUILD_DIR)output.elf
	$(OBJDUMP) -d $(BUILD_DIR)output.elf > $(LIST)

# Rule to make the image file.
$(TARGET) : $(BUILD_DIR)output.elf
	$(OBJCOPY) $(BUILD_DIR)output.elf -O  binary $(TARGET) 

# Rule to make the elf file.
$(BUILD_DIR)output.elf : $(OBJECTS) $(LINKER)
	$(LD) --no-undefined $(OBJECTS) -Map $(MAP) -o $(BUILD_DIR)output.elf -T $(LINKER)

# Rule to make the object files from Assembly sources.
$(BUILD_DIR)%.o: $(SOURCE_DIR)%.s
	$(AS) -I $(SOURCE_DIR) $< -mfpu=vfpv2 -o $@

# Rule to clean files.
clean : 
	-rm -f $(BUILD_DIR)*.o 
	-rm -f $(BUILD_DIR)output.elf
	-rm -f $(TARGET)
	-rm -f $(LIST)
	-rm -f $(MAP)

c : clean
