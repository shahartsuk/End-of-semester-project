
#include"LongSnapShot.h"
#pragma warning (disable:4996)


// Builds a snapshot every second and summarizes the memory of all processes until the user decides to stop
void LongSnapShot()
{
	int sec = 1;
	int stop = 0;
	t_SnapShot* origSnapShot = OneSnapShot();

	//in order not to run over the original list i use another pointers
	t_SnapShot* newTempSnapshot = NULL;

	t_Process* currentOrigProcess = NULL;
	t_Process* newProcess = NULL;
	t_Process* newProcessP = NULL;

	t_DLL* newDLLP = NULL;
	t_DLL* newProcessDll = NULL;
	t_DLL* currentOrigProcessDll = NULL;
	// To Start
	// Until Stop

	printf("Dear user enter any note to end the long snap shot\n");
	// kbhit() return 1 if keyboard key was clicked else returns 0
	while (stop != 1)
	{
		if (kbhit())
		{
			stop = 1;
		}
		newTempSnapshot = OneSnapShot();
		// check if there is the same process, if so I summarize their memory
		newProcess = newTempSnapshot->process;
		while (newProcess)
		{
			currentOrigProcess = origSnapShot->process;
			while (currentOrigProcess)
			{
				// Iterate over processes that are in main snapshot
				if (newProcess->ProcessID == currentOrigProcess->ProcessID)
				{
					// Sum current process's stuff
					currentOrigProcess->pmc.PageFaultCount += newProcess->pmc.PageFaultCount;
					currentOrigProcess->pmc.WorkingSetSize += newProcess->pmc.WorkingSetSize;
					currentOrigProcess->pmc.QuotaPagedPoolUsage += newProcess->pmc.QuotaPagedPoolUsage;
					currentOrigProcess->pmc.QuotaPeakPagedPoolUsage += newProcess->pmc.QuotaPeakPagedPoolUsage;
					currentOrigProcess->pmc.PagefileUsage += newProcess->pmc.PagefileUsage;

					// Iterate new dll list
					newProcessDll = newProcess->ProcessDLLList;
					while (newProcessDll)
					{
						currentOrigProcessDll = currentOrigProcess->ProcessDLLList;
						while (currentOrigProcessDll)
						{
							if (strcmp(currentOrigProcessDll->DLLName, newProcessDll->DLLName) == 0)
							{
								break;
							}
							// ! didnt work had to write ==NULL
							else if (currentOrigProcessDll->next==NULL)
							{

								newDLLP = (t_DLL*)malloc(sizeof(t_DLL));
								if (!newDLLP)
								{
									LogError(strerror(GetLastError()));
									exit(1);
								}
								*newDLLP = *newProcessDll;

								currentOrigProcessDll->next = newDLLP;
								newDLLP->prev = currentOrigProcessDll;
								newDLLP->next = NULL;
								currentOrigProcess->DLLNumber++;

							}

							currentOrigProcessDll = currentOrigProcessDll->next;
						}

						newProcessDll = newProcessDll->next;
					}
					// found the process, stop and go to the next one
					break;
				}
				else if (!currentOrigProcess->next)
				{
					newProcessP = (t_Process*)malloc(sizeof(t_Process));
					if (!newProcessP)
					{
						LogError(strerror(GetLastError()));
						exit(1);
					}
					*newProcessP = *newProcess;

					currentOrigProcess->next = newProcessP;
					newProcessP->prev = currentOrigProcess;
					newProcessP->next = NULL;

				}
				currentOrigProcess = currentOrigProcess->next;
			}

			newProcess = newProcess->next;
		}

		resetSnapShot(newTempSnapshot);
		Sleep(1000);
		if (sec == 1)
		{
			printf("%d Eteration\n", sec);
		}
		else {
			printf("%d Eterations\n", sec);
		}
		sec++;
	}
	buildSnapShotList(origSnapShot);
}


