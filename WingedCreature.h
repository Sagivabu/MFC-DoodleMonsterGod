#pragma once
#include "pch.h"
#include "BasicCreature.h"
#include "Wing.h"


class WingedCreature :
    virtual public BasicCreature
{
protected:
    std::vector<Wing> wings;

public:
    WingedCreature() {}
    WingedCreature(const Head& head, const Torso& torso, const std::vector<Wing>& wings)
        : BasicCreature(head, torso, 700, 400, 500, { 1 + 0.1 * wings.size() ,1,1}), wings(wings) {}
    ~WingedCreature() {}

    virtual std::wstring showStats() const override;
};
