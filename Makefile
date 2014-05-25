# device minor and major numbers:
# - major number indicating which device driver should be
# used to access a particular device
# - minor number serving as a flag to a device driver
# The minor number of the device node that represents the whole disk is 0.
# 12 bits are used to encode a major number (0..4095, it seems), 20 bits - for the minors

obj-m += dev_driver.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	sudo insmod dev_driver.ko
	sudo mknod /dev/test c 250 0
#	sudo chmod 666 /dev/test - by default
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	sudo rmmod dev_driver
	sudo rm -rf /dev/test
