#include "pch.h"
#include "CimeraCreature.h"



std::wstring CimeraCreature::showStats() const
{
	std::wstringstream ss;
	ss << "Type: Cimera Creature\n" << BasicCreature::showStats();
	return ss.str();
}