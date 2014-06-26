# Performance versus Design in C++ (a 1 day tutorial)

## Code Example: massif demonstration 

This directory contains an application with a memory leak on purpose. You invoke it by calling the binary and giving the number of kB that are to be allocated.  
```bash
$ gcc -O2 -g ellbow-out.c -o ellbow-out
$ valgrind --tool=massif ellbow-out 5000
$ massif-visualizer massif.out.* #if available
```

## Contact

Either contact the original author (Peter Steinbach) through the github issue tracker or directly: steinbac@mpi-cbg.de

## License

All the material contained is licensed under the Create Commons Attribution License (version 4.0, CC-BY 4.0). See LICENSE for more details.


