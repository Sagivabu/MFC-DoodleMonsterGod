#pragma once
#include "BodyPart.h"
class Leg :
    public BodyPart
{
public:
    Leg() : BodyPart("leg") {};
    Leg(const Leg& Leg) : BodyPart(Leg) {}

    virtual unsigned  int getPartID() const override { return 4; }
    const static unsigned int Type = 4;
};

