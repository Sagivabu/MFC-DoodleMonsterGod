#include "pch.h"
#include "WingedCreature.h"



std::wstring WingedCreature::showStats() const
{
	std::wstringstream ss;
	ss << "Type: Winged Creature\n" << BasicCreature::showStats();
	return ss.str();
}