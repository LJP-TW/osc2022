CROSS_COMPILE ?= aarch64-linux-gnu-
CC := $(CROSS_COMPILE)gcc
LD := $(CROSS_COMPILE)ld

KERNEL_IMG := kernel8.img
KERNEL_ELF := kernel8.elf
IMG_NAME := myos.img

$(KERNEL_IMG): $(KERNEL_ELF)
	$(CROSS_COMPILE)objcopy -O binary $^ $(KERNEL_IMG)

$(KERNEL_ELF): linker.ld head.o
	$(LD) -T $< -o $(KERNEL_ELF) head.o

head.o: head.S
	$(CC) -c $^

qemu: $(KERNEL_IMG)
	qemu-system-aarch64 -M raspi3 -kernel $(KERNEL_IMG) -display none -serial null -serial stdio

image: $(KERNEL_IMG) $(IMG_NAME)
	./tools/buildimg.sh $^

# Empty Target
# Ref: https://www.gnu.org/software/make/manual/make.html#Empty-Targets
	@sudo touch image

$(IMG_NAME):
	./tools/createimg.sh $(IMG_NAME)

.PHONY: clean
clean:
	rm -f *.o $(KERNEL_ELF)

.PHONY: clean-all
clean-all: clean
	rm -f $(KERNEL_IMG) $(IMG_NAME)
	
