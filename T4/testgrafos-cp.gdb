catch syscall exit_group
cond 1 $rdi!=0
break main
run coquimbo-cp.gf algarrobo-cp.gf antofagasta-cp.gf las-cruces-cp.gf
