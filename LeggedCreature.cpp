#include "pch.h"
#include "LeggedCreature.h"



std::wstring LeggedCreature::showStats() const
{
	std::wstringstream ss;
	ss << "Type: Legged Creature\n" << BasicCreature::showStats();
	return ss.str();
}

