# Strategy Simulator
A simple simulator program to track holding positions of any trading algorithm

## Running the program
### Dependencies
This projects is tested on M1 Pro MacOS, so it is preferable to use the same. But as long as the system has `gcc`, `g++`,`cmake >= 3.8` and `boost >= 1.75` the program should compile well. To use a different compiler we can update the path in `cmake/c++.cmake`
```
set(CMAKE_C_COMPILER <new_c_comiler_path>)
set(CMAKE_CPP_COMPILER <new_c++_compiler_path>)
```

### How to build
It is pretty easy to build once the dependencies are satisfied. We can just use
```
./build_script
```

### How to run
The executable is generated at `./build/bins/simulator/simulator`. It takes only one argument which is the config file. We can run it as follows
```
./build/bins/simulator/simulator <path_to_json_config_file>
```

There is a sample json config file in `./configs` for example. Please make sure that the path to the closing prices file is correct and the output folder exists.

## Threading
In the config there is an option for `num_extra_threads`, it allows us to run the simulations over multiple threads. The various strategies are divided over the extra threads and run in parallel.
