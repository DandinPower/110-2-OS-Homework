KERNEL_DIR = /usr/src/linux-headers-5.13.0-37-generic/

obj-m := simple.o

all:
	make -C $(KERNEL_DIR) SUBDIRS=$(shell pwd)
clean:
	rm *.o *.ko *.mod.c	
.PHONY:
	clean
