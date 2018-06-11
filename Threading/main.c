#include<stdio.h>
#include<Windows.h>
#include "lock.h"

int changevar;

void performAction() {
	AcquireLock();
			printf("Printing and modifying shared:%d", ++changevar);
	ReleaseLock();
}

void main()
{
	HANDLE thread1 = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)performAction, NULL, (DWORD)0,NULL);
	HANDLE thread2 = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)performAction, NULL, (DWORD)0, NULL);

	CloseHandle(thread1);
	CloseHandle(thread2);
}