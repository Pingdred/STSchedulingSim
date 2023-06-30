# STSchedulingSim

STSchedulingSim is a Short-Term Scheduling Algorithms Simulator written in C++. It provides simulations for the following scheduling algorithms: First-Come, First-Served (FCFS), Shortest Job First (SJF), and Round Robin (RR).

## Requirements

- C++ compiler
- CMake

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

Once the project is built, you can run the simulator by providing the path to the input configuration file. The simulator does not accept any additional command line parameters beyond the configuration file name.

```shell
./STSchedulingSim <input_file>
```

- `<input_file>`: Path to the input configuration file. The file should follow the following format for each process: `<arrival_time> <process_name> <burst_time> <priority>`. The `priority` attribute is reserved for a future implementation of priority-based scheduling algorithms.

Please note that the Round Robin (RR) algorithm currently does not support specifying the time quantum through command line arguments.

## Example Output

Using the example configuration file with the specified format, the simulator produces the following output:

```
FCFS: P1->P2->P3->P4->P5, TMA 22.6
SJF: P1->P3->P4->P5->P2, TMA 9.6
RR: P1->P2->P3->P4->P5->P2->P5->P2, TMA 17.6
```


