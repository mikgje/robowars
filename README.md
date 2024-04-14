# Chop Shop for Omega Verksted's RoboWars April 2024. 
The code is made to be used with a Raspberry Pi 3 B connected to a Bluetooth wireless controller.

The repsoitory contains both a Python and a C version. The Python code is straightforward to use. The C code requires the Linuxs kernel. To use the C code, first compile the WiringPi library using `./build` with its Bazel BUILD file. If the folder containing the library is empty, first initialize it using `git submodule update --init`. After building the library, compile `main.c` in the `source` folder using `gcc -o main main.c -l wiringPi`. The program can then be run with `./main`.

Note that the C version has a significantly lower input delay than the Python version, but hasn't been fully tested.