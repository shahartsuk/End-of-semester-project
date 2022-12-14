#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>
#include <Windows.h>
#include <psapi.h>
#include"Build SnapShot.h"
#include"Build ProcessList.h"
#include"LogFile.h"
#include"LongSnapShot.h"
#include"DLLDictionary.h"
#include"SnapShotFile.h"
#include"MemoryFree.h"
#include"GenerateHTML.h"
#pragma warning (disable:4996)

int main()
{
    // gets the snapshot after created
    t_SnapShot* snapShot=NULL;
    char userResponses = NULL;
    char strFileName[1000];
    char strEvents[1000];
    time_t t;
    time(&t);

    struct tm* timeInfo;

    timeInfo = localtime(&t);
    sprintf(strFileName, "C:\\Users\\97254\\source\\repos\\TheBigProject\\LogFiles\\FileLog %d %d %d - %02d:%02d", timeInfo->tm_year + 1900, timeInfo->tm_mon + 1, timeInfo->tm_mday, timeInfo->tm_hour, timeInfo->tm_min);
    Log_Init(strFileName);
    strcpy(strEvents, "System Is Starting");
    LogEvent(strEvents);

    while (userResponses != 'Q')
    {
        printf("Dear user,there is options for you to build your dictionary:\n1. A-Take one snapshot\n2. T-Take 20 snapshots\n3. L-Start long snapshot\n4. G-Generate HTML report\n5. R-Reset collection\n6. S-Save in file\n7. U-Upload from File\n8. Q-Quit\n");
        // space in order to disable the enter input
        scanf(" %c", &userResponses);
        switch (userResponses)
        {
        case 'A':
            sprintf(strFileName, "C:\\Users\\97254\\source\\repos\\TheBigProject\\LogFiles\\FileLog %d %d %d - %02d:%02d", timeInfo->tm_year + 1900, timeInfo->tm_mon + 1, timeInfo->tm_mday, timeInfo->tm_hour, timeInfo->tm_min);
           strcpy(strEvents, "Taking one snapshot");
           LogEvent(strEvents);
           snapShot = OneSnapShot();
            buildSnapShotList(snapShot);
            strcpy(strEvents, "One snapshot had finished");
            break;
             case 'T':
                 sprintf(strFileName, "C:\\Users\\97254\\source\\repos\\TheBigProject\\LogFiles\\FileLog %d %d %d - %02d:%02d", timeInfo->tm_year + 1900, timeInfo->tm_mon + 1, timeInfo->tm_mday, timeInfo->tm_hour, timeInfo->tm_min);
                 printf("Please wait for twenty seconds\n");
                 strcpy(strEvents, "Taking twenty snapshots");
                 LogEvent(strEvents);
                 TwentySnapShots();
                 strcpy(strEvents, "Twenty snapshots had finished");
            break;
            case 'L':
                sprintf(strFileName, "C:\\Users\\97254\\source\\repos\\TheBigProject\\LogFiles\\FileLog %d %d %d - %02d:%02d", timeInfo->tm_year + 1900, timeInfo->tm_mon + 1, timeInfo->tm_mday, timeInfo->tm_hour, timeInfo->tm_min);
                strcpy(strEvents, "Taking long snapshot");
                LogEvent(strEvents);
                LongSnapShot();
                strcpy(strEvents, "Long snapshot had finished");
            break;
        case 'G':        
                sprintf(strFileName, "C:\\Users\\97254\\source\\repos\\TheBigProject\\LogFiles\\FileLog %d %d %d - %02d:%02d", timeInfo->tm_year + 1900, timeInfo->tm_mon + 1, timeInfo->tm_mday, timeInfo->tm_hour, timeInfo->tm_min);
                strcpy(strEvents, "Starting to build DLL Dictionary");
                LogEvent(strEvents);
                // I have to reset this variable every time because I sum up all the memory of the Snapshots in it every time and then divide
                if (Shead)
                {
                searchForAllTheDLLS();
                }
                GenerateHTML();
                strcpy(strEvents, "Done building DLL Dictionary");
            break;
         case 'R':
             releaseTheCollection();
             // have to give the lists NULL so i can keep with the program
             Shead = Stail = NULL;
             head = tail = NULL;
             Dhead = Dtail = NULL;
             break;
         case 'S':
            if (!Shead)
            {
                printf("There is no SnapShots in the list pleas try other options");
            }
            else
            {
                sprintf(strFileName, "C:\\Users\\97254\\source\\repos\\TheBigProject\\LogFiles\\FileLog %d %d %d - %02d:%02d", timeInfo->tm_year + 1900, timeInfo->tm_mon + 1, timeInfo->tm_mday, timeInfo->tm_hour, timeInfo->tm_min);
                strcpy(strEvents, "Starting to enter snapshot list to file");
                LogEvent(strEvents);
                EnterSnapShotListToFile();
                strcpy(strEvents, "Done entering snapshot list to file");
            }
            break;
         case 'U':
            
                 sprintf(strFileName, "C:\\Users\\97254\\source\\repos\\TheBigProject\\LogFiles\\FileLog %d %d %d - %02d:%02d", timeInfo->tm_year + 1900, timeInfo->tm_mon + 1, timeInfo->tm_mday, timeInfo->tm_hour, timeInfo->tm_min);
                 strcpy(strEvents, "Starting to upload snapshot list from file");
                 LogEvent(strEvents);
                 UploadSnapShotListFromFile();
                 strcpy(strEvents, "Done uploading snapshot list from file");

             break;
            case 'Q':
                sprintf(strFileName, "C:\\Users\\97254\\source\\repos\\TheBigProject\\LogFiles\\FileLog %d %d %d - %02d:%02d", timeInfo->tm_year + 1900, timeInfo->tm_mon + 1, timeInfo->tm_mday, timeInfo->tm_hour, timeInfo->tm_min);
                strcpy(strEvents, "Starting to delet snapshot list");
                LogEvent(strEvents);
                releaseTheCollection();
                strcpy(strEvents, "Done deleting snapshot list");
                break; 
        default:
            printf("wrong selection, pls be more sharp");
            break;
        }
    }

   GetProcessInfo();
   LogEvent("System Is Ending");
}
