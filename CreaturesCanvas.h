#pragma once
#include "BasicCreature.h"
#include "BodyPart.h"
#include "MFCprojectDlg.h"
#include "LeggedCreature.h"
#include "WingedCreature.h"
#include "TailedCreature.h"
#include "SlitheringCreature.h"
#include "ReptilianCreature.h"
#include "HumanoidCreature.h"
#include "CimeraCreature.h"
#include "DragonCreature.h"
#include "AngelCreature.h"

#include "Head.h"
#include "Torso.h"
#include "Hand.h"
#include "Leg.h"
#include "Tail.h"
#include "Wing.h"

void Fight(CMFCprojectDlg* cmf, BasicCreature& bc1, BasicCreature& bc2); //Button 'Fight'
void creatureStats(const BasicCreature* bc1); //Button 'Stats'
BasicCreature* createCreature(CMFCprojectDlg* cmf, std::vector<BodyPart*> bPartsVector); //Button 'Create' 