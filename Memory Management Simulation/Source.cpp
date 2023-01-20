#include <iostream>
#include <vector>
#include <iterator>
#include "Process.h"
#include "Partition.h"
using namespace std;

void firstFit(vector<Partition> memoryPartitions, vector<Process> userProcesses);
void nextFit(vector<Partition> memoryPartitions, vector<Process> userProcesses);
void bestFit(vector<Partition> memoryPartitions, vector<Process> userProcesses);
void worstFit(vector<Partition> memoryPartitions, vector<Process> userProcesses);
void worstFitDynamic(vector<Partition> memoryPartitions, vector<Process> userProcesses);
int main() {
	//Variables for initializing partitions and processes
	int numProcesses = 0, numPartitions = 0, processSize = 0, partitionSize = 0;
	vector<Process> userProcesses;
	vector<Partition> memoryPartitions;

	//Resize the memory partitions vector based on user input
	cout << "Enter the number of memory partitions: ";
	cin >> numPartitions;
	memoryPartitions.resize(numPartitions);

	//Get the size of each partition from the user
	for (int x = 0; x < memoryPartitions.size(); x++) {
		memoryPartitions[x].setPartitionID(x + 1);
		cout << "Memory for Partition " << memoryPartitions[x].getPartitionId() << ": ";
		cin >> partitionSize;
		memoryPartitions[x].setMemorySize(partitionSize);
	}

	//Resize the user processes vector based on user input
	cout << "\nEnter the number of processes: ";
	cin >> numProcesses;
	userProcesses.resize(numProcesses);

	//Get the required size of each process from the user
	for (int x = 0; x < userProcesses.size(); x++) {
		userProcesses[x].setProcessId(x + 1);
		cout << "Memory needed for Process " << userProcesses[x].getProcessId() << ": ";
		cin >> processSize;
		userProcesses[x].setSize(processSize);
	}

	//Call memory management algorithms
	firstFit(memoryPartitions, userProcesses);

	nextFit(memoryPartitions, userProcesses);

	bestFit(memoryPartitions, userProcesses);

	worstFit(memoryPartitions, userProcesses);

	worstFitDynamic(memoryPartitions, userProcesses);

	return 0;
}

void firstFit(vector<Partition> memoryPartitions, vector<Process> userProcesses) {
	int numProcesses = userProcesses.size(), numPartitions = memoryPartitions.size(), currentWaste = 0, totalWaste = 0;

	cout << "\n==================== First-Fit ====================" << endl;
	cout << "\nProcess No.\tPartition No.\tWaste\tStatus\n";

	//Search for the first free partition that has enough memory for each process
	for (int x = 0; x < numProcesses; x++) {
		for (int y = 0; y < numPartitions; y++) {
			//Check if the partition has enough memory and isn't already running a process
			if (userProcesses[x].getSize() <= memoryPartitions[y].getMemorySize() && memoryPartitions[y].getIsFree()) {
				//Change the data of the newly assigned process
				userProcesses[x].setStatus("Run");
				userProcesses[x].setCurrentPartition(memoryPartitions[y].getPartitionId());

				//Process is now assigned to the partition so it isn't free
				memoryPartitions[y].setIsFree(false);

				//Calculate memory left over after the process and partition are assigned
				currentWaste = memoryPartitions[y].getMemorySize() - userProcesses[x].getSize();
				totalWaste += currentWaste;

				//Print out the data from the process
				cout << userProcesses[x].getProcessId() << "\t\t" << userProcesses[x].getCurrentPartition() << "\t\t" << currentWaste << "\t" <<
					userProcesses[x].getStatus() << "\n";
				break;
			}
		}
	}

	//Print out processes that weren't assigned to a partition
	for (int x = 0; x < numProcesses; x++) {
		if (userProcesses[x].getStatus() == "Wait") {
			cout << userProcesses[x].getProcessId() << "\t\t" << "-" << "\t\t" << "-" << "\t" <<
				userProcesses[x].getStatus() << "\n";
		}
	}

	cout << "\nTotal waste: " << totalWaste << endl;
}

void nextFit(vector<Partition> memoryPartitions, vector<Process> userProcesses) {
	int numProcesses = userProcesses.size(), numPartitions = memoryPartitions.size(), currentWaste = 0, totalWaste = 0, y = 0;

	cout << "\n==================== Next-Fit ====================" << endl;
	cout << "\nProcess No.\tPartition No.\tWaste\tStatus\n";

	for (int x = 0; x < numProcesses; x++) {
		//Don't do multiple loops, continue with the next partition 
		while (y < numPartitions) {
			//Check if the partition has enough memory and isn't already running a process
			if (userProcesses[x].getSize() <= memoryPartitions[y].getMemorySize() && memoryPartitions[y].getIsFree()) {
				//Change the data of the newly assigned process
				userProcesses[x].setStatus("Run");
				userProcesses[x].setCurrentPartition(memoryPartitions[y].getPartitionId());

				//Process is now assigned to the partition so it isn't free
				memoryPartitions[y].setIsFree(false);

				//Calculate memory left over after the process and partition are assigned
				currentWaste = memoryPartitions[y].getMemorySize() - userProcesses[x].getSize();
				totalWaste += currentWaste;

				//Print out the data from the process
				cout << userProcesses[x].getProcessId() << "\t\t" << userProcesses[x].getCurrentPartition() << "\t\t" << currentWaste << "\t" <<
					userProcesses[x].getStatus() << "\n";
				break;
			}
			y++;
		}
	}

	//Print out processes that weren't assigned to a partition
	for (int x = 0; x < numProcesses; x++) {
		if (userProcesses[x].getStatus() == "Wait") {
			cout << userProcesses[x].getProcessId() << "\t\t" << "-" << "\t\t" << "-" << "\t" <<
				userProcesses[x].getStatus() << "\n";
		}
	}

	cout << "\nTotal waste: " << totalWaste << endl;
}

void bestFit(vector<Partition> memoryPartitions, vector<Process> userProcesses) {
	int numProcesses = userProcesses.size(), numPartitions = memoryPartitions.size(), currentWaste = 0, totalWaste = 0;

	cout << "\n==================== Best-Fit ====================" << endl;
	cout << "\nProcess No.\tPartition No.\tWaste\tStatus\n";

	for (int x = 0; x < numProcesses; x++) {
		//Initialize best fit index 
		int bestFit = -1;
		for (int y = 0; y < memoryPartitions.size(); y++) {
			//Check if the partition has enough memory and isn't already running a process
			if (userProcesses[x].getSize() <= memoryPartitions[y].getMemorySize() && memoryPartitions[y].getIsFree()) {
				//Check if this is the first assignment of the best fit index
				//Otherwise check if there is another best fit
				if (bestFit == -1) {
					bestFit = y;
				}
				else if (memoryPartitions[bestFit].getMemorySize() > memoryPartitions[y].getMemorySize()) {
					bestFit = y;
				}
			}
		}

		//Check if a best fit index was found
		if (bestFit != -1) {
			//Change the data of the newly assigned process
			userProcesses[x].setStatus("Run");
			userProcesses[x].setCurrentPartition(memoryPartitions[bestFit].getPartitionId());

			//Process is now assigned to the partition so it isn't free
			memoryPartitions[bestFit].setIsFree(false);

			//Calculate memory left over after the process and partition are assigned
			currentWaste = memoryPartitions[bestFit].getMemorySize() - userProcesses[x].getSize();
			totalWaste += currentWaste;

			//Print out the data from the process
			cout << userProcesses[x].getProcessId() << "\t\t" << userProcesses[x].getCurrentPartition() << "\t\t" << currentWaste << "\t" <<
				userProcesses[x].getStatus() << "\n";
		}
	}

	//Print out processes that weren't assigned to a partition
	for (int x = 0; x < numProcesses; x++) {
		if (userProcesses[x].getStatus() == "Wait") {
			cout << userProcesses[x].getProcessId() << "\t\t" << "-" << "\t\t" << "-" << "\t" <<
				userProcesses[x].getStatus() << "\n";
		}
	}

	cout << "\nTotal waste: " << totalWaste << endl;
}

void worstFit(vector<Partition> memoryPartitions, vector<Process> userProcesses) {
	int numProcesses = userProcesses.size(), numPartitions = memoryPartitions.size(), currentWaste = 0, totalWaste = 0;

	cout << "\n==================== Worst-Fit ====================" << endl;
	cout << "\nProcess No.\tPartition No.\tWaste\tStatus\n";

	for (int x = 0; x < numProcesses; x++) {
		int worstFit = -1;
		for (int y = 0; y < numPartitions; y++) {
			//Check if the partition has enough memory and isn't already running a process
			if (userProcesses[x].getSize() <= memoryPartitions[y].getMemorySize() && memoryPartitions[y].getIsFree()) {
				//Check if this is the first assignment of the worst fit index
				//Otherwise check if there is another worst fit
				if (worstFit == -1) {
					worstFit = y;
				}
				else if (memoryPartitions[y].getMemorySize() > memoryPartitions[worstFit].getMemorySize()) {
					worstFit = y;
				}
			}
		}

		//Check if a worst fix index was found
		if (worstFit != -1) {
			//Change the data of the newly assigned process
			userProcesses[x].setStatus("Run");
			userProcesses[x].setCurrentPartition(memoryPartitions[worstFit].getPartitionId());

			//Process is now assigned to the partition so it isn't free
			memoryPartitions[worstFit].setIsFree(false);

			//Calculate memory left over after the process and partition are assigned
			currentWaste = memoryPartitions[worstFit].getMemorySize() - userProcesses[x].getSize();
			totalWaste += currentWaste;

			//Print out the data from the process
			cout << userProcesses[x].getProcessId() << "\t\t" << userProcesses[x].getCurrentPartition() << "\t\t" << currentWaste << "\t" <<
				userProcesses[x].getStatus() << "\n";
		}
	}

	//Print out processes that weren't assigned to a partition
	for (int x = 0; x < numProcesses; x++) {
		if (userProcesses[x].getStatus() == "Wait") {
			cout << userProcesses[x].getProcessId() << "\t\t" << "-" << "\t\t" << "-" << "\t" <<
				userProcesses[x].getStatus() << "\n";
		}
	}

	cout << "\nTotal waste: " << totalWaste << endl;
}

void worstFitDynamic(vector<Partition> memoryPartitions, vector<Process> userProcesses) {
	int numProcesses = userProcesses.size(), numPartitions = memoryPartitions.size(), currentWaste = 0, totalWaste = 0;

	cout << "\n==================== Worst-Fit Dynamic ====================" << endl;
	cout << "\nProcess No.\tPartition No.\tWaste\tStatus\n";

	for (int x = 0; x < numProcesses; x++) {
		int worstFit = -1;
		for (int y = 0; y < numPartitions; y++) {
			//Check if the partition has enough memory and isn't already running a process
			if (userProcesses[x].getSize() <= memoryPartitions[y].getMemorySize() && memoryPartitions[y].getIsFree()) {
				//Check if this is the first assignment of the worst fit index
				//Otherwise check if there is another worst fit
				if (worstFit == -1) {
					worstFit = y;
				}
				else if (memoryPartitions[y].getMemorySize() > memoryPartitions[worstFit].getMemorySize()) {
					worstFit = y;
				}
			}
		}

		//Check if a worst fix index was found
		if (worstFit != -1) {
			//Process has now been assigned to a partition
			userProcesses[x].setStatus("Run");
			userProcesses[x].setCurrentPartition(memoryPartitions[worstFit].getPartitionId());

			//Partition is no longer free
			memoryPartitions[worstFit].setIsFree(false);

			//Calculate memory left over after the process and partition are assigned
			currentWaste = memoryPartitions[worstFit].getMemorySize() - userProcesses[x].getSize();

			//If there is waste resulting from the assignment
			if (currentWaste > 0) {
				//Create an index and a new unassigned partition with the leftover memory to be inserted in the vector
				//The new partition will be inserted right after the worst fit partition
				vector<Partition>::iterator index = memoryPartitions.begin() + worstFit + 1;
				Partition newPartition(worstFit + 11, currentWaste, -1, true);

				//Insert the new partition
				memoryPartitions.insert(index, newPartition);

				//Change the memory of the assigned partition after its waste was used for a new partition
				memoryPartitions[worstFit].setMemorySize(userProcesses[x].getSize());

				numPartitions = memoryPartitions.size();

				//Calculate memory left over after the process and partition are assigned
				currentWaste = memoryPartitions[worstFit].getMemorySize() - userProcesses[x].getSize();

				/*Partition newPartition(numPartitions + 1, currentWaste, -1, true);
				memoryPartitions.push_back(newPartition);
				numPartitions = memoryPartitions.size();
				currentWaste = memoryPartitions[worstFit].getMemorySize() - userProcesses[x].getSize();*/
			}
			totalWaste += currentWaste;

			//Print out the data from the process
			cout << userProcesses[x].getProcessId() << "\t\t" << userProcesses[x].getCurrentPartition() << "\t\t" << currentWaste << "\t" <<
				userProcesses[x].getStatus() << "\n";
		}
	}

	//Print out processes that weren't assigned to a partition
	for (int x = 0; x < numProcesses; x++) {
		if (userProcesses[x].getStatus() == "Wait") {
			cout << userProcesses[x].getProcessId() << "\t\t" << "-" << "\t\t" << "-" << "\t" <<
				userProcesses[x].getStatus() << "\n";
		}
	}

	cout << "\nTotal waste: " << totalWaste << endl;

	//Print out the memory partitions after the algorithm is executed
	//Checks to see if the new partitions were inserted correctly
	for (auto x : memoryPartitions) {
		cout << "\nPartiton: " << x.getPartitionId() << " " << x.getMemorySize();
	}
}