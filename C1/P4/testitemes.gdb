catch syscall exit_group
cond 1 $rdi!=0
break main
run coquimbo.arr algarrobo.arr santiago.arr
