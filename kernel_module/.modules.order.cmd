cmd_/home/lilpa/workspace/my_project/kernel_module/modules.order := {   echo /home/lilpa/workspace/my_project/kernel_module/hello.ko; :; } | awk '!x[$$0]++' - > /home/lilpa/workspace/my_project/kernel_module/modules.order
