#pragma once
#include "LeggedCreature.h"
#include "TailedCreature.h"

class ReptilianCreature :
    public LeggedCreature, public TailedCreature
{
protected:
    std::vector<Leg> legs;
    std::vector<Tail> tails;

public:
    ReptilianCreature() {}
    ReptilianCreature(const Head& head, const Torso& torso, const std::vector<Leg>& legs, const std::vector<Tail>& tails)
        :
        LeggedCreature(head,torso,legs),
        TailedCreature(head,torso,tails),
        BasicCreature(head, torso, 1500, 300, 400, { 1,1 + 0.1 * tails.size(),1 + 0.1 * legs.size() }),
        legs(legs), tails(tails) {}
    ~ReptilianCreature() {}

    virtual std::wstring showStats() const override;
};

