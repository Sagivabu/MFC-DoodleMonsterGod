#pragma once
#include "pch.h"
#include "BodyPart.h";
#include "Head.h";
#include "Torso.h";

#include "string.h"
using std::ostream;
using std::endl;
using std::cout;

class BasicCreature //Abstarct
{
protected:
	//Stats:
	int atk = 0;
	int def = 0;
	int hp = 0;
	std::array<double, 3> statsMultiplier = {1,1,1};

	//BodyParts:
	Head head;
	Torso torso;
	

public:
	BasicCreature() {}
	BasicCreature(const Head& head, const Torso& Torso, int atk, int def, int hp, std::array<double, 3> statsMultiplier = { 1,1,1 }) : atk(atk), def(def), hp(hp), head(head), torso(torso) {
			this->statsMultiplier[0] = statsMultiplier[0];
			this->statsMultiplier[1] = statsMultiplier[1];
			this->statsMultiplier[2] = statsMultiplier[2];
	}
	virtual ~BasicCreature() = 0;

	//get Stats:
	int getAtk() const { return (int)(atk * statsMultiplier[0]); }
	int getDef() const { return (int)(def * statsMultiplier[1]); }
	int getHp() const { return (int)(hp * statsMultiplier[2]); }

	//set Stats:
	void setAtk(int num) { atk = num; };
	void setDef(int num) { def = num; };
	void setHp(int num) { hp = num; };

	virtual void Attack(BasicCreature& bc); //attack another creature
	bool isDead() const { return hp<=0; } //True if is dead (HP less than 0)
	virtual std::wstring showStats() const;	//return string of creature details

};

