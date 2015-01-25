TCHIP=TM4C123GH6PM
CC=arm-none-eabi-gcc
CFLAGS=-mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16
CPPFLAGS= -Idevice/include -Icmsis/include -D$(TCHIP)
vpath %.h device/include cmsis/include
vpath %.c ../source device/source
vpath %.S device/source

all: salida.elf
main.o: main.c
startup_ARMCM4.o: startup_ARMCM4.S
system_TM4C123.o: system_TM4C123.c
#all:main.o func.o startup_ARMCM4.o exit.o
salida.elf: main.o startup_ARMCM4.o system_TM4C123.o
	$(CC) $(CFLAGS) -Ldevice -Tgcc_arm.ld  $^  -o $@
#main.o:main.c
#func.o:func.c
#exit.o:exit.c
#startup_ARMCM4.o:startup_ARMCM4.S
.PHONY:clean rebuild
clean:
	rm -f *.o *.elf
rebuild: clean all
