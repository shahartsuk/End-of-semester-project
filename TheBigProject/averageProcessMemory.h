#pragma once
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include <Windows.h>
#include <psapi.h>
#include <conio.h>
#include <time.h>
#include"Structs.h"
#include"LogFile.h"
#include"Build ProcessList.h"
#include"Build SnapShot.h"
#include"DLLDictionary.h"

unsigned long long averageProcessMemory(t_SnapShot*);
unsigned long long averageSnapShotMemory();
void buildProcessDictionaryList(t_Process*);