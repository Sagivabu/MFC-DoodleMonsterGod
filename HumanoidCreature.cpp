#include "pch.h"
#include "HumanoidCreature.h"



std::wstring HumanoidCreature::showStats() const
{
	std::wstringstream ss;
	ss << "Type: Humanoid Creature\n" << BasicCreature::showStats();
	return ss.str();
}