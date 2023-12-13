obj-m = driver.o

KDIR := /home/lilpa/workspace/my_project/WSL2-Linux-Kernel-linux-msft-wsl-5.15.133.1
PWD := $(shell pwd)

defualt:
	make -C $(KDIR) M=$(PWD) modules
