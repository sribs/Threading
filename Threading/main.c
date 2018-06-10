#include<stdio.h>
#include<Windows.h>

int value = 0;
int shared = 0;

int AcquireLock();
void ReleaseLock();

int AcquireLock() {
	__asm
	{
	enter_critical_section:
		mov eax, 1;
		lock xchg eax, value	; test set lock : store the 'value' in eax register
						; and then atomically set the 'value' to 1
		cmp eax, 0		; compare the eax register with zero.
		jnz enter_critical_section ; if eax is 1, lock already acquired, repeat the above process until free
	}
	return 0;
}

void performAction() {
	AcquireLock();
			printf("Printing and modifying shared:%d", ++shared);
	ReleaseLock();
}

void ReleaseLock()
{
	__asm
	{
	leave_critical_section:
		mov value, 0; free the lock
	}
}

void main()
{
	HANDLE thread1 = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)performAction, NULL, (DWORD)0,NULL);
	HANDLE thread2 = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)performAction, NULL, (DWORD)0, NULL);

	CloseHandle(thread1);
	CloseHandle(thread2);
}