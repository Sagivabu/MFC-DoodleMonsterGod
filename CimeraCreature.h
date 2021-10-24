#pragma once
#include "LeggedCreature.h"
#include "WingedCreature.h"

class CimeraCreature :
    public LeggedCreature, public WingedCreature
{
protected:
    std::vector<Head> heads;
    std::vector<Leg> legs;
    std::vector<Wing> wings;


public:
    CimeraCreature() {}
    CimeraCreature(const std::vector<Head>& heads, const Torso& torso, const std::vector<Leg>& legs, const std::vector<Wing>& wings)
        :
        LeggedCreature(heads[0],torso,legs),
        WingedCreature(heads[0],torso,wings),
        BasicCreature(heads[0], torso, 2700, 1000, 500, { 1 + 0.1*wings.size() + 0.2 * heads.size(), 1 ,1 + 0.1 * legs.size() + 0.2* heads.size() }),
        heads(heads), legs(legs), wings(wings) {}
    ~CimeraCreature() {}

    virtual std::wstring showStats() const override;
};

