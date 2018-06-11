#include "lock.h"
#include <Windows.h>
#include <stdio.h>

//shared = 1;

int AcquireLock()
{
	printf("\nThread %lu is Trying to Acquire the lock\n",GetCurrentThreadId());
	__asm
	{
	mov eax, 1;
	jmp enter_critical_section
	repeat_section:
		mov eax, 1;
	}
	printf("\nThread %lu failed to Acquire the lock. Retrying!!",GetCurrentThreadId());
	__asm
	{
	enter_critical_section:
		lock xchg eax, shared; test set lock : store the 'shared' in eax register
			; and then atomically set the 'shared' to 1
			cmp eax, 0; compare the eax register with zero.
			jnz repeat_section; if eax is 1, lock already acquired, repeat the above process until free
	}
	printf("\n Thread %lu Successfully acquired the lock. Please release the lock using ReleaseLock().", GetCurrentThreadId());
	return 0;
}

int ReleaseLock()
{
	printf("\n Thread %lu is trying to release the lock.", GetCurrentThreadId());
	__asm
	{
	leave_critical_section:
		mov shared, 0; free the lock
	}
	printf("\n Thread %lu successfully released the lock using the ReleaseLock(). Lock is now available, please acquire the lock using the AcquireLock()", GetCurrentThreadId());
	return 0;
}