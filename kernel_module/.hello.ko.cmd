cmd_/home/lilpa/workspace/my_project/kernel_module/hello.ko := ld -r  -m elf_x86_64 -z noexecstack   --build-id=sha1  -T scripts/module.lds -o /home/lilpa/workspace/my_project/kernel_module/hello.ko /home/lilpa/workspace/my_project/kernel_module/hello.o /home/lilpa/workspace/my_project/kernel_module/hello.mod.o;  true