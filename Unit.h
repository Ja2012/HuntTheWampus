#pragma once

#include "Cave.h"

class Cave;

class Unit
{
public:
    Cave* CavePtr;
    virtual ~Unit() {};
};