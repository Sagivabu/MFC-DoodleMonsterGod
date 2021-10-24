#include "pch.h"
#include "DragonCreature.h"



std::wstring DragonCreature::showStats() const
{
	std::wstringstream ss;
	ss << "Type: Dragon Creature\n" << BasicCreature::showStats();
	return ss.str();
}