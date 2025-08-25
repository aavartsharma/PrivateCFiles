# Makefile
MCU=atmega328p
F_CPU=16000000
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-std=c99 -Wall -g -Os -mmcu=${MCU} -DF_CPU=${F_CPU} -I.
TARGET=main
TARGET_DIR = build/${TARGET}
SRCS=${TARGET}.c
PORT = /dev/ttyACM0
SERIAL=-P ${PORT} -b 115200

all:
	mkdir -p build
	${CC} ${CFLAGS} -o ${TARGET_DIR}.bin ${SRCS}
	${OBJCOPY} -j .text -j .data -O ihex ${TARGET_DIR}.bin ${TARGET_DIR}.hex

flash:
	avrdude -p ${MCU} -c arduino -U flash:w:${TARGET_DIR}.hex:i ${SERIAL} 

assb:
	${CC} -mmcu=${MCU} -Wall -Os -o ${TARGET_DIR}.elf ${SRCS}
	avr-objdump -d ${TARGET_DIR}.elf >> ${TARGET}.asm 

space: # for memory anaylics
	${CC} -mmcu=${MCU} -Wall -Os -o ${TARGET_DIR}.elf ${SRCS}
	avr-size --format=avr --mcu=${MCU} ${TARGET_DIR}.elf

eeprom: # read eeprom data
	avrdude -P ${PORT} -c arduino -p m328p -U eeprom:r:${TARGET_DIR}.hex:i

clean:
	rm -f ${TARGET}/*.bin ${TARGET}/*.hex ${TARGET}/*.elf
