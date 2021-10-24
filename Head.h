#pragma once
#include "BodyPart.h"
class Head :
    public BodyPart
{
public:
    Head() : BodyPart("head") {}
    Head(const Head& head) : BodyPart(head) {}

    virtual unsigned int getPartID() const override { return 1; }
    const static unsigned int Type = 1;
};

