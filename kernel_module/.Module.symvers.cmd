cmd_/home/lilpa/workspace/my_project/kernel_module/Module.symvers := sed 's/\.ko$$/\.o/' /home/lilpa/workspace/my_project/kernel_module/modules.order | scripts/mod/modpost -m -a -E -o /home/lilpa/workspace/my_project/kernel_module/Module.symvers -e -i Module.symvers   -T -