SMP Model Development Kit
=========================

This project is forked from [Burak Deniz's implementation of SMP (Simulation Model Portability) Model Development Kit](https://github.com/GITburakdeniz/smp-mdk) for open-source development of SMP models, mainly geared for academic research projects including HIL (Hardware in the Loop) and OBC (On board computer) device and peripheral models, among others.

Differences from original author's code:

- Migrating to CMake build system (WIP).
- Adding examples from the official handbook (WIP).
- Adding minimal implementation of a simulation infrastructure (WIP).

Instructions
------------

Requirements:

- C++ compiler
- CMake

Build library:

~~~bash
mkdir build
cd build
cmake ..
make && make install
~~~

Tested on Ubuntu 18.04.


Related resources and references
--------------------------------

- [SMP 2.0 Handbook - EGOS-SIM-GEN-TN-0099 - Issue 1 Revision 2 - 28 October 2005](https://taste.tuxfamily.org/wiki/images/9/9a/SMP_2.0_Handbook_-_1.2.pdf). Accessed 2021-09-30.