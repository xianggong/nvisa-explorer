# NVIDIA ISA Explorer

`nvisa-explorer` is a toy to explore the native ISA (or SASS) bit fields for NVIDIA GPUs. The ISA information is a prerequsite for a disassembler or ISA-level simulator. NVIDIA does not publish the ISA of their GPUs, which is why this project is started. The ISA is provided as C++ classes. Each instruction type corresponding to one class. They can be directly used in the C++ projects that need ISA information.

## Project Status
* Pascal ISA: In progress
* Volta ISA: Planned

## Setup Requirement
* CUDA toolkit 8.0
* G++ 4.8 or above
