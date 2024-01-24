#pragma once

#include "Cave.h"

struct Cave;

struct Unit
{
    Cave* CavePtr;
    virtual ~Unit() {};
};