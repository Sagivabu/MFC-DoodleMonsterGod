#pragma once
#include "BasicCreature.h"
class SlitheringCreature :
    virtual public BasicCreature
{

public:
    SlitheringCreature() {}
    SlitheringCreature(const Head& head, const Torso& torso)
        : BasicCreature(head, torso, 200, 200, 200, { 1,1,1 }) {}
    ~SlitheringCreature() {}

    virtual std::wstring showStats() const override;
};

