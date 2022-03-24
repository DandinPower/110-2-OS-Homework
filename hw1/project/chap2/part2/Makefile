KERNEL_DIR = /lib/modules/${shell uname -r}

obj-m := birthday.o

all:
	make -C $(KERNEL_DIR)/build M=$(shell pwd) modules
clean:
	rm *.o *.ko *.mod.c	
	make -C $(KERNEL_DIR)/build M=$(shell pwd) clean
.PHONY:
	clean
