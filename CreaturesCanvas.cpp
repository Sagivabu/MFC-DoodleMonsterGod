#include "CreaturesCanvas.h"
#include "pch.h"


//	Button 'Fight' function
void Fight(CMFCprojectDlg* cmf, BasicCreature& lbc1, BasicCreature& rbc2)
{
	if (lbc1.getHp() > 0 && rbc2.getHp() > 0) //because the creature may be survived this round
	{
		lbc1.Attack(rbc2);
		if (lbc1.isDead())
		{
			lbc1.setHp(0);
			cmf->isDrawXl = true;
		}
		if (rbc2.isDead())
		{
			rbc2.setHp(0);
			cmf->isDrawXr = true;
		}
	}
	else
	{
		cmf->fightCanceledM();
	}
}


// Button 'Stats' function
void creatureStats(const BasicCreature* bc1)
{
	if (bc1 != nullptr)
	{
		auto message = bc1->showStats();
		MessageBox(0, message.c_str(), L"Creature Stats", 0);
	}
	else
	{
		std::wstringstream ss;
		ss << "Please Create a Creature first";
		auto message = ss.str();
		MessageBox(0, message.c_str(), L"Creature Stats Failed!", 0);
	}
}



// Button 'Create' function
BasicCreature* createCreature(CMFCprojectDlg* cmf, std::vector<BodyPart*> v)
{
	//!! 10 - the next steps is to build the matching creature depends on the bodyparts distribution

	struct {
		std::vector<Head> heads;
		std::vector<Torso> torsos;
		std::vector<Hand> hands;
		std::vector<Leg> legs;
		std::vector<Tail> tails;
		std::vector<Wing> wings;
	} bodyParts;


	for (auto bodyPart : v) {
		switch (bodyPart->getPartID()) {
			case Head::Type: {
				bodyParts.heads.push_back(*static_cast<Head*>(bodyPart));
				break;
			}
			case Torso::Type: {
				bodyParts.torsos.push_back(*static_cast<Torso*>(bodyPart));
				break;
			}
			case Hand::Type: {
				bodyParts.hands.push_back(*static_cast<Hand*>(bodyPart));
				break;
			}
			case Leg::Type: {
				bodyParts.legs.push_back(*static_cast<Leg*>(bodyPart));
				break;
			}
			case Tail::Type: {
				bodyParts.tails.push_back(*static_cast<Tail*>(bodyPart));
				break;
			}
			case Wing::Type: {
				bodyParts.wings.push_back(*static_cast<Wing*>(bodyPart));
				break;
			}
		}

	}
	//Dragon
	 if (bodyParts.heads.size() == 1 &&
		bodyParts.torsos.size() == 1 &&
		bodyParts.hands.size() == 0 &&
		bodyParts.legs.size() >= 2 && bodyParts.legs.size() <= 4 &&
		bodyParts.tails.size() >= 1 && bodyParts.tails.size() <= 9 &&
		bodyParts.wings.size() >= 2 && bodyParts.wings.size() <= 6)
	{
		 cmf->dragonCreatedM();
		return new DragonCreature(bodyParts.heads[0], bodyParts.torsos[0], bodyParts.legs, bodyParts.tails, bodyParts.wings);
	}
	 //Angel
	else if (bodyParts.heads.size() == 1 &&
		bodyParts.torsos.size() == 1 &&
		bodyParts.hands.size() >= 2 && bodyParts.hands.size() <= 6 &&
		bodyParts.legs.size() == 2 &&
		bodyParts.tails.size() == 0 &&
		bodyParts.wings.size() >= 2 && bodyParts.wings.size() <= 6)
	{
		 cmf->angelCreatedM();
		return new AngelCreature(bodyParts.heads[0], bodyParts.torsos[0], bodyParts.hands, bodyParts.legs, bodyParts.wings);
	}
	 //Cimera
	else if (bodyParts.heads.size() >= 1 && bodyParts.heads.size() <= 3 &&
		bodyParts.torsos.size() == 1 &&
		bodyParts.hands.size() == 0 &&
		bodyParts.legs.size() >= 2 && bodyParts.legs.size() <= 8 &&
		bodyParts.tails.size() == 0 &&
		bodyParts.wings.size() >= 2 && bodyParts.wings.size() <= 6)
	 {
		 cmf->cimeraCreatedM();
		 return new CimeraCreature(bodyParts.heads, bodyParts.torsos[0], bodyParts.legs, bodyParts.wings);
	 }
	 //Reptilian
	else if (bodyParts.heads.size() == 1 &&
		bodyParts.torsos.size() == 1 &&
		bodyParts.hands.size() == 0 &&
		bodyParts.legs.size() >= 2 && bodyParts.legs.size() <= 8 &&
		bodyParts.tails.size() >= 1 && bodyParts.tails.size() <= 9 &&
		bodyParts.wings.size() == 0)
	 {
		 cmf->reptilianCreatedM();
		 return new ReptilianCreature(bodyParts.heads[0], bodyParts.torsos[0], bodyParts.legs, bodyParts.tails);
	 }
	 //Humanoid
	else if (bodyParts.heads.size() == 1 &&
		bodyParts.torsos.size() == 1 &&
		bodyParts.hands.size() >= 2 && bodyParts.hands.size() <= 6 &&
		bodyParts.legs.size() >= 2 && bodyParts.legs.size() <= 4 &&
		bodyParts.tails.size() == 0 &&
		bodyParts.wings.size() == 0)
	 {
		 cmf->humanoidCreatedM();
		 return new HumanoidCreature(bodyParts.heads[0], bodyParts.torsos[0], bodyParts.legs, bodyParts.hands);
	 }
	 //Legged
	else if(bodyParts.heads.size() == 1 &&
		bodyParts.torsos.size() == 1 &&
		bodyParts.hands.size() == 0 &&
		bodyParts.legs.size() >= 2 && bodyParts.legs.size() <= 8 &&
		bodyParts.tails.size() == 0 &&
		bodyParts.wings.size() == 0)
	{
		 cmf->leggedCreatedM();
		return new LeggedCreature(bodyParts.heads[0], bodyParts.torsos[0], bodyParts.legs); 
	}
	 //Winged
	else if (bodyParts.heads.size() == 1 &&
		bodyParts.torsos.size() == 1 &&
		bodyParts.hands.size() == 0 &&
		bodyParts.legs.size() >= 0 &&
		bodyParts.tails.size() == 0 &&
		bodyParts.wings.size() >= 2 && bodyParts.wings.size() <= 6)
	{
		 cmf->wingedCreatedM();
		return new WingedCreature(bodyParts.heads[0], bodyParts.torsos[0], bodyParts.wings); 
	}
	 //Tailed
	else if (bodyParts.heads.size() == 1 &&
		bodyParts.torsos.size() == 1 &&
		bodyParts.hands.size() == 0 &&
		bodyParts.legs.size() >= 0 &&
		bodyParts.tails.size() >= 1 && bodyParts.tails.size() <= 9 &&
		bodyParts.wings.size() == 0)
	 {
		 cmf->tailedCreatedM();
		 return new TailedCreature(bodyParts.heads[0], bodyParts.torsos[0], bodyParts.tails);
	 }
	//Slithering
	else if (bodyParts.heads.size() == 1 &&
		bodyParts.torsos.size() == 1 &&
		bodyParts.hands.size() == 0 &&
		bodyParts.legs.size() >= 0 &&
		bodyParts.tails.size() == 0 &&
		bodyParts.wings.size() >= 0)
	{
		 cmf->slitheringCreatedM();
		return new SlitheringCreature(bodyParts.heads[0], bodyParts.torsos[0]);
	}
	else
	{
		 cmf->failed2CreateM();
		 return nullptr;
	}

	//!! 10 - end
}