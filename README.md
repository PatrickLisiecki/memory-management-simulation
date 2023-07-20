# Memory Management Simulation

Assignment for CSC 305 - Operating Systems Lab with Professor Jonathan Parziale

## Objective

The objective of this program is to implement the following memory management algorithms:

- First-Fit
- Next-Fit
- Best-Fit
- Worst-Fit Fixed
- Worst-Fit Dynamic

The program allows the user to input main memory information, including the number of memory partitions and the size of each memory partition. Additionally, the program takes process information, assigning a unique identifier to each job, including the number of processes and the memory requirements for each process/job.

## Program Structure

The program is structured as follows:

1. `Source.cpp`: The main source code file that contains the implementation of the memory management algorithms.
2. `Process.h`: Header file for the `Process` class that represents a job/process. It contains variables like process Id, status (run/wait), memory requirement, and the partition name/Id it was assigned to.
3. `Partition.h`: Header file for the `Partition` class that represents a memory partition. It contains variables like partition name/Id, a bool to indicate if the partition is in use, the amount of memory available, and the process Id assigned to it.

## Program Input

The program prompts the user to input the following:

1. Main Memory Information:
   - The number of memory partitions.
   - The size of each memory partition.

2. Process Information:
   - Number of processes.
   - Memory requirements for each process/job.

## Program Output

The program provides the following output for each algorithm:

- Initial Memory Allocation:
   - It displays a list of initial memory allocation, i.e., which process was assigned to which partition after the first round of allocation.

- Memory Waste:
   - The program calculates and displays the memory waste for each partition.
   - It also provides the total waste for each algorithm.

- List of Processes in Waiting State:
   - It lists the processes that were not assigned to any partition and are in the waiting state.

## How to Run the Program

1. Clone the repository or download the source code files to your local machine.
2. Ensure you have a C++ compiler installed (e.g., GCC, MinGW for Windows, etc.).
3. Open a terminal or command prompt and navigate to the directory containing the source code files.
4. Compile the program using the C++ compiler. For example:
   
   ```
   g++ Source.cpp -o memory_management
   ```
   
5. Run the executable generated:
   
   ```
   ./memory_management
   ```
   
6. Follow the on-screen instructions to provide the required input.

## Screenshots

Screenshots of the output/results from each memory management algorithm.

<img align="center" width="400" src="https://github.com/PatrickLisiecki/memory-management-simulation/assets/96704934/61da468b-089d-4aa1-8b6f-1dcbc57f99b5" />

<img align="center" width="600" height="300" src="https://github.com/PatrickLisiecki/memory-management-simulation/assets/96704934/2ee6bc71-be96-46e5-803b-b3fbb045b1e6" />
