
#include"averageProcessMemory.h"
#pragma warning (disable:4996)

// Calculates the average memory of the entire list of snapshots
unsigned long long averageSnapShotMemory()
{
	unsigned long long avgAllSnapShots = 0;
	int oneSnapProcessCounter = 0;

	t_SnapShot* snapShotList = Shead;
	if (!Shead)
	{
		return;
	}
	t_Process* currProcess = NULL;

	while (snapShotList)
	{
		currProcess = snapShotList->process;
		while (currProcess)
		{
			avgAllSnapShots += currProcess->pmc.WorkingSetSize;
			currProcess = currProcess->next;
		}
		oneSnapProcessCounter += snapShotList->processCounter;
		snapShotList = snapShotList->next;
	}

	avgAllSnapShots = avgAllSnapShots / oneSnapProcessCounter;
	return 	avgAllSnapShots;
}
// Calculates each snapshot separately
 unsigned long long averageProcessMemory(t_SnapShot* SnapShot)
{
	t_SnapShot* currSnapShot= SnapShot;
	t_Process* currProcess = NULL;
	if (currSnapShot)
	{
	 currProcess = currSnapShot->process;
	}
	else
	{
		return;
	}
	unsigned long long sum1SnapShot=0;
	unsigned long long avg = 0;
	int numOfProcess=0;

	while (currProcess)
	{
	sum1SnapShot += currProcess->pmc.WorkingSetSize;

	currProcess = currProcess->next;
	}

	avg = sum1SnapShot / currSnapShot->processCounter;

	return avg;
}

 // counting the processesID in the snapshot list
 void buildProcessDictionaryList(t_Process* newProcess)
 {
	 ProcessCounter++;
	 t_PDictionary* addProcessID = (t_PDictionary*)malloc(sizeof(t_PDictionary));
	 if (!addProcessID)
	 {
		 LogError(strerror(GetLastError()));
		 exit(1);
	 }
	 t_Process* newItem = newProcess;
	 addProcessID->ProcessID = newItem->ProcessID;
	 addProcessID->next = addProcessID->prev = NULL;

	 if (!PDictionaryHead)
	 {
		 PDictionaryHead = addProcessID;
		 PDictionaryTail = addProcessID;
		 return;
	 }
	 else
	 {
		 addProcessID->prev = PDictionaryTail;
		 PDictionaryTail->next = addProcessID;
		 PDictionaryTail = addProcessID;
		 return;
	 }

 }
