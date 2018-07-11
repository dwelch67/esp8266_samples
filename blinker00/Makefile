
XTENSA = xtensa-lx106-elf

AOPS = --warn 
COPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding
xCOPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding -save-temps

all : blinker00.esp.bin

clean:
	rm -f *.bin
	rm -f *.o
	rm -f *.elf
	rm -f *.list
	rm -f toolbin

#---------------------------------

vectors.o : vectors.s
	$(XTENSA)-as $(AOPS) vectors.s -o vectors.o

blinker00.o : blinker00.c
	$(XTENSA)-gcc $(COPS) -c blinker00.c -o blinker00.o

blinker00.bin :     memmap vectors.o blinker00.o
	$(XTENSA)-ld -T memmap vectors.o blinker00.o -o blinker00.elf
	$(XTENSA)-objdump -D blinker00.elf > blinker00.list
	$(XTENSA)-objcopy blinker00.elf blinker00.bin -O binary

toolbin : toolbin.c
	gcc toolbin.c -o toolbin

blinker00.esp.bin : blinker00.bin toolbin
	./toolbin blinker00.bin blinker00.esp.bin




