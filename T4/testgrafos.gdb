catch syscall exit_group
cond 1 $rdi!=0
break main
run coquimbo.gf algarrobo.gf antofagasta.gf las-cruces.gf
