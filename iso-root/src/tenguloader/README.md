#TenguOS Loader
## Temporary stashed to focus on the Tengu6 kernel and OS first.

This is the loader for TenguOS. The bootloader (Limine) loads this file first,
then it finds a C compiler and compiles the kernel, finally loading the kernel and
exits.

Memory map and all kernel command parameters are passed to the kernel.

Loader parameters:
  - prebuilt_kernel=yes/no: Use a precompiled kernel instead of recompiling?
  - kernel_path=string: Precompiled kernel path. `prebuilt_kernel` is assumed `yes` if not given.
