#include "pch.h"
#include "SlitheringCreature.h"



std::wstring SlitheringCreature::showStats() const
{
	std::wstringstream ss;
	ss << "Type: Slithering Creature\n" << BasicCreature::showStats();
	return ss.str();
}