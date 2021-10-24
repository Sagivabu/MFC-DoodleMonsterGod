#include "pch.h"
#include "ReptilianCreature.h"



std::wstring ReptilianCreature::showStats() const
{
	std::wstringstream ss;
	ss << "Type: Reptilian Creature\n" << BasicCreature::showStats();
	return ss.str();
}
