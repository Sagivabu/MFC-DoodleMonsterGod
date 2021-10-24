#pragma once
#include "BodyPart.h"
class Tail :
    public BodyPart
{
public:
    Tail() : BodyPart("tail") {};
    Tail(const Tail& tail) : BodyPart(tail) {}

    virtual unsigned  int getPartID() const override { return 5; }
    const static unsigned int Type = 5;
};

