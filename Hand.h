#pragma once
#include "BodyPart.h"
class Hand :
    public BodyPart
{
public:
    Hand() : BodyPart("hand") {};
    Hand(const Hand& hand) : BodyPart(hand) {}

    virtual unsigned  int getPartID() const override { return 3; }
    const static unsigned int Type = 3;
};

