#pragma once
#include "BodyPart.h"
class Torso :
    public BodyPart
{
public:
    Torso() : BodyPart("torso") {};
    Torso(const Torso&) = default;

    virtual unsigned  int getPartID() const override { return 2; }
    const static unsigned int Type = 2;
};

