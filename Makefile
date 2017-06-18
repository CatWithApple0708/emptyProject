
CROSS_COMPILE =
AS		= $(CROSS_COMPILE)as
LD		= $(CROSS_COMPILE)ld
CC		= $(CROSS_COMPILE)gcc
CPP		= $(CC) -E
AR		= $(CROSS_COMPILE)ar
NM		= $(CROSS_COMPILE)nm

STRIP		= $(CROSS_COMPILE)strip
OBJCOPY		= $(CROSS_COMPILE)objcopy
OBJDUMP		= $(CROSS_COMPILE)objdump

export AS LD CC CPP AR NM
export STRIP OBJCOPY OBJDUMP

export CFLAGS LDFLAGS

TOPDIR := $(shell pwd)
export TOPDIR

CFLAGS := -Wall -O2 -g -I $(TOPDIR)/include

CFLAGS += -I $(TOPDIR)/include
CFLAGS += -I $(TOPDIR)/src/EasyLogger/include
CFLAGS += -I $(TOPDIR)/src/inirw/include

LDFLAGS := -lpthread



TARGET := main.out


 obj-y += main.o
 obj-y += src/

all :
	make -C ./ -f $(TOPDIR)/Makefile.build
	$(CC) -o $(TARGET)  built-in.o   $(LDFLAGS)


clean:
	rm -f $(shell find  -name "*.o")
	rm -f $(shell find  -name "*.d")
	rm -f $(TARGET)
.PHONY:all clean



