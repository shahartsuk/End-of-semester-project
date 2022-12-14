#include"DLLDictionary.h"
#pragma warning (disable:4996)

t_DLLDictionary* DDictionaryHead = NULL;
t_DLLDictionary* DDictionaryTail = NULL;

t_PDictionary* PDictionaryHead = NULL;
t_PDictionary* PDictionaryTail = NULL;

int DLLCounter = 0;
int ProcessCounter = 0;

// search all the process that use the same dll in the snapshot list.
void searchForAllTheDLLS()
{
	t_PDictionary* currProcessList = NULL;

	t_DLLDictionary* currDLLList = NULL;

	t_SnapShot* currentSList = Shead;

	t_Process* currentProcess = currentSList->process;

	t_DLL* currentProcessDll = currentProcess->ProcessDLLList;

	buildProcessDictionaryList(currentProcess);

	while (currentSList)
	{ 
		currentProcess = currentSList->process;
		while (currentProcess)
		{
			currProcessList = PDictionaryHead;
			while (currProcessList)
			{
				if (currProcessList->ProcessID == currentProcess->ProcessID)
				{
					break;
				}
				else if (currProcessList == PDictionaryTail)
				{
					// to know how many processes i have in the program
					buildProcessDictionaryList(currentProcess);
				}
				currProcessList = currProcessList->next;
			}
			currentProcessDll = currentProcess->ProcessDLLList;
			if (!DDictionaryHead && currentProcessDll != NULL)
			{
				buildDLLDictionaryList(currentProcessDll);
			}
			else
			{
			while (currentProcessDll)
			{
				currDLLList = DDictionaryHead;
				while (currDLLList)
				{
					if (strstr(currentProcessDll->DLLName, ".dll") || strstr(currentProcessDll->DLLName, ".DLL"))
					{
					if (strcmp(currentProcessDll->DLLName, currDLLList->DLLName) == 0)
					{
						break;
					}
					else if (currDLLList== DDictionaryTail)
					{
						buildDLLDictionaryList(currentProcessDll);
					}
					}
					currDLLList = currDLLList->next;
				}
				currentProcessDll = currentProcessDll->next;
			}
			}
			currentProcess = currentProcess->next;
		}
		currentSList = currentSList->next;
	}
	currentSList = Shead;
	addNewValue();
}

//create the list of all the dll i have in the project
void buildDLLDictionaryList(t_DLL* newDLL)
{
	// to know how many DLL'S i have in the program
	DLLCounter++;
	t_DLLDictionary* addDLL = (t_DLLDictionary*)malloc(sizeof(t_DLLDictionary));
	if (!addDLL)
	{
		LogError(strerror(GetLastError()));
		exit(1);
	}
	t_DLL* currDLL = newDLL;
	addDLL->ProcessList = NULL;
	strcpy(addDLL->DLLName, currDLL->DLLName);
	addDLL->next = addDLL->prev = NULL;

	if (!DDictionaryHead)
	{
		DDictionaryHead = addDLL;
		DDictionaryTail = addDLL;
		return;
	}
	else
	{
		addDLL->prev = DDictionaryTail;
		DDictionaryTail->next = addDLL;
		DDictionaryTail = addDLL;
		return;
	}
	
}
// Creates the list of processes that used the same dll
void addNewValue()
{
	t_DLLDictionary* currDLLList = DDictionaryHead;

	t_SnapShot* currentSList = Shead;

	t_Process* currentProcess = currentSList->process;

	t_DLL* currentProcessDll = currentProcess->ProcessDLLList;

	while (currentSList)
	{
		while (currDLLList)
		{
		currentProcess = currentSList->process;
			while (currentProcess)
			{
				currentProcessDll = currentProcess->ProcessDLLList;
				while (currentProcessDll)
				{
					if (strcmp(currDLLList->DLLName, currentProcessDll->DLLName) == 0)
					{
						addToDictionary(currDLLList, currentProcess);
					}
					currentProcessDll = currentProcessDll->next;
				}
				currentProcess = currentProcess->next;
			}
			currDLLList = currDLLList->next;
		}
		currentSList = currentSList->next;
	}
	currentSList = Shead;
}
// Appends the list of processors that used the same dll to the list of the dll's
void addToDictionary(t_DLLDictionary* curr, t_Process* newItem)
{
	t_DLLDictionary* currItem = curr;
	t_Process* addProcess = (t_Process*)malloc(sizeof(t_Process));
	if (!addProcess)
	{
		LogError(strerror(GetLastError()));
		exit(1);
	}
	*addProcess = *newItem;
	while (currItem->ProcessList)
	{
		if (addProcess->ProcessID == currItem->ProcessList->ProcessID)
		{
			free(addProcess);
			return;
		}
		if (!currItem->ProcessList->next)
		{
			currItem->ProcessList->next = addProcess;
			addProcess->prev = currItem->ProcessList;
			addProcess->next = NULL;
			return;
		}
		currItem->ProcessList = currItem->ProcessList->next;
	}
	currItem->ProcessList = addProcess;
	return;
}

