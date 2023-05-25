# STSchedulingSim

STSchedulingSim is a Short-Term Scheduling Algorithms Simulator written in C++. It provides simulations for the following scheduling algorithms: First-Come, First-Served (FCFS), Shortest Job First (SJF), and Round Robin (RR).

## Requirements

- C++ compiler with C++20 support
- CMake (version 3.12 or higher)

## Build Instructions

1. Clone the repository:

```shell
git clone https://github.com/sirius-0/STSchedulingSim.git
```

2. Navigate to the project directory:

```shell
cd STSchedulingSim
```

3. Create a build directory:

```shell
mkdir build
cd build
```

4. Generate build files with CMake:

```shell
cmake ..
```

5. Build the project:

```shell
make
```

This will generate the executable for the simulator.

## Usage

Once the project is built, you can run the simulator with different scheduling algorithms and parameters. The simulator accepts the following command line arguments:

```shell
./STSchedulingSim <input_file>
```

- `<input_file>`: Path to the input file containing the process information. Each line in the file represents a process and should follow the format: `<arrival_time> <process_name> <burst_time> <priority>`. 

The priority is for a future implementation of the priority algorithm

Please note that the Round Robin (RR) algorithm currently does not support specifying the time quantum through command line arguments.
