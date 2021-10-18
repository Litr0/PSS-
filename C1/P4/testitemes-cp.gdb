catch syscall exit_group
cond 1 $rdi!=0
break main
run coquimbo-cp.arr algarrobo-cp.arr santiago-cp.arr
