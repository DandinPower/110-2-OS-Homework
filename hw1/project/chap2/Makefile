KVERSION := $(shell uname -r)
KERNEL_DIR = /usr/src/linux-headers-$(KVERSION)/

MODULE_NAME = simple
obj-m := $(MODULE_NAME).o

all:
	make -C $(KERNEL_DIR) M=$(shell pwd)
clean:
	rm *.o *.ko *.mod.c	
.PHONY:
	clean
