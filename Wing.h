#pragma once
#include "BodyPart.h"
class Wing :
    public BodyPart
{
public:
    Wing() : BodyPart("wing") {};
    Wing(const Wing& wing) : BodyPart(wing) {}

    virtual unsigned  int getPartID() const override { return 6; }
    const static unsigned int Type = 6;
};

