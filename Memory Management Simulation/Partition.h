#pragma once
using namespace std;
#ifndef PARTITION_H
#define PARTITION_H

class Partition {
private:
	int partitionId, memorySize, currentProcess;
	bool isFree;

public:
	Partition() {
		partitionId = 0;
		memorySize = 0;
		isFree = true;
		currentProcess = 0;
	}

	Partition(int newId, int newMemorySize, int newProcess, bool newStatus) {
		partitionId = newId;
		memorySize = newMemorySize;
		currentProcess = newProcess;
		isFree = newStatus;
	}

	int getPartitionId() {
		return partitionId;
	}

	int getMemorySize() {
		return memorySize;
	}

	int getCurrentProcess() {
		return currentProcess;
	}

	bool getIsFree() {
		return isFree;
	}

	void setPartitionID(int newId) {
		partitionId = newId;
	}

	void setMemorySize(int newMemorySize) {
		memorySize = newMemorySize;
	}

	void setCurrentProcess(int newProcess) {
		currentProcess = newProcess;
	}

	void setIsFree(bool newStatus) {
		isFree = newStatus;
	}
};

#endif