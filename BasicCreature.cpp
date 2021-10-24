#include "pch.h"
#include "BasicCreature.h"
#define _CRT_SECURE_NO_WARNINGS


BasicCreature::~BasicCreature() {}

void BasicCreature::Attack(BasicCreature& bc)
{
	if (atk > bc.getDef())
		bc.setHp(bc.getHp() - (atk - bc.getDef()));
	if (bc.getAtk() > def)
		hp -= bc.getAtk() - def;
}

std::wstring BasicCreature::showStats() const
{
    std::wstringstream ss;
    ss << "HP: " << getHp() << "\nAtk: " << getAtk() << "\nDef: " << getDef();
    return ss.str();
}
