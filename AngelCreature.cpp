#include "pch.h"
#include "AngelCreature.h"

std::wstring AngelCreature::showStats() const
{
	std::wstringstream ss;
	ss << "Type: Angel Creature\n" << BasicCreature::showStats();
	return ss.str();
}