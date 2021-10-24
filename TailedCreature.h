#pragma once
#include "BasicCreature.h"
#include "Tail.h"

class TailedCreature :
    virtual public BasicCreature
{
protected:
    std::vector<Tail> tails;

public:
    TailedCreature() {}
    TailedCreature(const Head& head, const Torso& torso, const std::vector<Tail>& tails)
        : BasicCreature(head, torso, 800, 200, 300, { 1,1 + 0.1 * tails.size(),1 }), tails(tails) {}
    ~TailedCreature() {}

    virtual std::wstring showStats() const override;
};