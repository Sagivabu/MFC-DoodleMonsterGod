#pragma once
#include "pch.h"
#include "BasicCreature.h"
#include "Leg.h";


class LeggedCreature :
    virtual public BasicCreature
{
protected:
    std::vector<Leg> legs;

public:
    LeggedCreature() {}
    LeggedCreature(const Head& head, const Torso& torso, const std::vector<Leg>& legs) 
        : BasicCreature(head, torso, 400, 600, 300, { 1,1,1 + 0.1*legs.size() }), legs(legs){}
    ~LeggedCreature() {}

   virtual std::wstring showStats() const override;

};
