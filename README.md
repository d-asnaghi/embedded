
# Algorithms for embedded systems

Most embedded systems run under specific sets of constraints, specifically lower computing capacity and stack memory available. 

While the C standard library contains greatly optimized implementations of most of the common algorithms, many embedded applications benefit from application specific implementations that minimize code size.

The following is a personal collection of algorithms implementation in C specifically aimed for embedded applications. Each file can be compiled standalone, but the functions implemented are intended to be modular and usable in any project.

## Sections

* [Sorting](sorting) 

## Directory tree

The project is organized in this directory tree, every topic contains an explanation of the algorithms implemented.
 
```bash
├── README.md
├── docs
│   └── [supporting files]
├── sorting
│   ├── README.md
│   └──  embedded_sorting.c
└── template.c
```