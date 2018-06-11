#pragma once
#include <Windows.h>
#ifndef LOCK_H
#define LOCK_H

int shared;

int AcquireLock();
int ReleaseLock();

#endif