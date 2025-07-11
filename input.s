addi x3, x0, 16
slli x3, x3, 12
addi x1, x0, 1
sb x1, 0(x3)
addi x1, x1, 240
sh x1, 1(x3)
slli x1, x1, 8
sw x1, 3(x3)
addi x1, x1, 1024
sd x1, 8(x3)
lb x5, 0(x3)
lbu x6, 0(x3)
lh x7, 0(x3)
lhu x8, 0(x3)
lw x9, 1(x3)
ld x10, 4(x3)