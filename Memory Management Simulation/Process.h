#pragma once
#include <string>
using namespace std;
#ifndef PROCESS_H
#define PROCESS_H

class Process {
private:
	int processId, size, currentPartition;
	string status;

public:
	Process() {
		processId = 0;
		size = 0;
		currentPartition = 0;
		status = "Wait";
	}

	Process(int newId, int newSize, int newPartition, string newStatus) {
		processId = newId;
		size = newSize;
		currentPartition = newPartition;
		status = newStatus;
	}

	int getProcessId() {
		return processId;
	}

	int getSize() {
		return size;
	}

	int getCurrentPartition() {
		return currentPartition;
	}

	string getStatus() {
		return status;
	}

	void setProcessId(int newID) {
		processId = newID;
	}

	void setSize(int newSize) {
		size = newSize;
	}

	void setCurrentPartition(int newPartition) {
		currentPartition = newPartition;
	}

	void setStatus(string newStatus) {
		status = newStatus;
	}
};

#endif