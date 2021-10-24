#pragma once
#include "LeggedCreature.h"
#include "Hand.h";

class HumanoidCreature :
    virtual public LeggedCreature
{
protected:
    std::vector<Leg> legs;
    std::vector<Hand> hands;

public:
    HumanoidCreature() {}
    HumanoidCreature(const Head& head, const Torso& torso, const std::vector<Leg>& legs, const std::vector<Hand>& hands)
        :
        LeggedCreature(head, torso, legs),
        BasicCreature(head, torso, 1200, 600, 500, { 1 + 0.1 * hands.size(),1,1 + 0.1 * legs.size() }),
        legs(legs), hands(hands) {}
    ~HumanoidCreature() {}

    virtual std::wstring showStats() const override;
};

