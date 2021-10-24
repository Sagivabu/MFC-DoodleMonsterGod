#pragma once
#include "pch.h"


class BodyPart: public CObject//Abstarct
{
protected:
	CImage* image = nullptr;	//hold the image
	CPoint imagePoint{};		// hold the topleft point of the picture control
	int width = 64;				// width of the picture control
	int height = 64;			//height of the picture control
	int x2MidWidth = 0;				//the First x differences between the picture and to the middle of the client (to rePosition when change window size)
	const char* partName;		// "head" / "torso" / "hand".. to verification for later use
	CStatic control;			// the picture control itself
	bool isBorderSet = true;	// flag to turn off and on the picture frame borders
	int imageIndex = -1;		//the index of the image from 'file' (the list of the 68 images) - for Serialize
private:	int edgeHitBox = 4;	// whne turning on the frame border to play with size - we want bigger hitbox


public: 
	BodyPart();
	BodyPart(const BodyPart& bp);
	virtual ~BodyPart();
	BOOL create(CWnd* pParentWnd, std::vector<std::array<LPCTSTR, 2>> files, int m_nDragIndex, int ClientMid);	//create the picture control
	void setPosition(int x, int y); //Set new position for picture control
	void ShowHideBorders(); //Show / Hide picture control frame borders
	void reSize(int w, int h); //reSize the picture control
	bool isInside(CPoint& point); // if point is inside the control rect return TRUE
	int catchEdge(CPoint& point); //return which edge is catched

protected:
	BodyPart(const char* name) :partName(name) {};

public:
	const char* getPartName() { return partName; }
	virtual unsigned int getPartID() const = 0;
	const static unsigned int Type = 0;
	void Serialize(CArchive& ar);
	void SerializeName(CArchive& ar); //need to know bodyPart name to create the right derived son

	friend class CMFCprojectDlg; // this class makes changes in bodyPart
};

