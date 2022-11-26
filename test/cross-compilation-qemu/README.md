# Playing with RISC-V Cross Compiler and Qemu

## Setup
### Archlinux
```
sudo pacman -Sy qemu-user-static qemu-system-riscv riscv64-linux-gnu-gcc
```

## Execution
We'll use qemu-user-static to avoid emulating a full systems and instead just running *statically* compiled *C* binaries. So, to cross-compile a C into RISC-V binary:
```
riscv64-linux-gnu-gcc --static source.c
```

This will generate `a.out`, which is RISC-V binary. To execute it:
```
qemu-riscv64-static ./a.out
```

To inspect the asm of the generated binary:
```
riscv64-linux-gnu-objdump ./a.out
```
