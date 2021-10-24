#pragma once
#include "HumanoidCreature.h"
#include "WingedCreature.h"

class AngelCreature :
    public HumanoidCreature, public WingedCreature
{
protected:
    std::vector<Hand> hands;
    std::vector<Leg> legs;
    std::vector<Wing> wings;


public:
    AngelCreature() {}
    AngelCreature(const Head& head, const Torso& torso, const std::vector<Hand>& hands, const std::vector<Leg>& legs,const std::vector<Wing>& wings)
        :
        HumanoidCreature(head, torso, legs,hands),
        WingedCreature(head, torso, wings),
        BasicCreature(head, torso, 3000, 1200, 600, { 1 + 0.1 * (wings.size()+hands.size()),1 ,1 + 0.1 * legs.size() }),
        hands(hands), legs(legs), wings(wings) {} //implemetaion is order by declaration
    ~AngelCreature() {}

    virtual std::wstring showStats() const override;
};

