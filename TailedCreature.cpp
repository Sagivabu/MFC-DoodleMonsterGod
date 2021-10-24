#include "pch.h"
#include "TailedCreature.h"



std::wstring TailedCreature::showStats() const
{
	std::wstringstream ss;
	ss << "Type: Tailed Creature\n" << BasicCreature::showStats();
	return ss.str();
}