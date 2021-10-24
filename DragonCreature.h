#pragma once
#include "LeggedCreature.h"
#include "TailedCreature.h"
#include "WingedCreature.h"

class DragonCreature :
    public LeggedCreature, public TailedCreature, public WingedCreature
{
protected:
    std::vector<Leg> legs;
    std::vector<Tail> tails;
    std::vector<Wing> wings;


public:
    DragonCreature() {}
    DragonCreature(const Head& head, const Torso& torso, const std::vector<Leg>& legs, const std::vector<Tail>& tails, const std::vector<Wing>& wings)
        :
        LeggedCreature(head, torso, legs),
        TailedCreature(head, torso, tails),
        WingedCreature(head, torso, wings),
        BasicCreature(head, torso, 2500, 1500, 1000, { 1 + 0.1 * wings.size(),1 + 0.1*tails.size(),1 + 0.1 * legs.size() }),
        legs(legs), tails(tails), wings(wings) {}
    ~DragonCreature() {}

    virtual std::wstring showStats() const override;
};

