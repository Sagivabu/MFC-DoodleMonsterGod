#include "pch.h"
#include "BodyPart.h"

BodyPart::BodyPart()
{
	partName = NULL;
	image = new CImage();
}
BodyPart::BodyPart(const BodyPart& bp)
{
	image = bp.image;
	partName = bp.partName;
}
BodyPart::~BodyPart()
{
	delete image;
}

BOOL BodyPart::create(CWnd* pParentWnd, std::vector<std::array<LPCTSTR, 2>> files, int m_nDragIndex, int ClientMid)
{
	//creatre the Picture control
	control.Create(_T("A bitmap static control (A)"),
		WS_CHILD | WS_BORDER | WS_VISIBLE | SS_BITMAP, CRect(imagePoint.x, imagePoint.y, height, width),
		pParentWnd);
	//insert image to the picture control
	CBitmap Cbmp;
	CImage Cimg;
	Cimg.Load(files[m_nDragIndex][1]);
	control.SetBitmap(HBITMAP(Cimg));
	control.ShowWindow(SW_SHOW);
	x2MidWidth = ClientMid - imagePoint.x; //for later use;
	//Draw the Image
	setPosition(imagePoint.x, imagePoint.y);
	return true;
}

void BodyPart::setPosition(int x, int y)
{
	this->imagePoint.SetPoint(x, y);
	this->control.MoveWindow(x, y, width, height);
}

void BodyPart::ShowHideBorders()
{
	if (isBorderSet) //turn OFF the borders
	{
		control.ModifyStyle(WS_BORDER, WS_OVERLAPPED);
		isBorderSet = false;
	}
	else if (!isBorderSet) //turn ON the borders
	{
		control.ModifyStyle(0, WS_BORDER | WS_OVERLAPPED);
		isBorderSet = true;
	}
}

void BodyPart::reSize(int w, int h)
{
	width = w;
	height = h;
	control.MoveWindow(imagePoint.x, imagePoint.y, w, h);
}

bool BodyPart::isInside(CPoint& point)
{
	int x = imagePoint.x;
	int y = imagePoint.y;
	return (point.x > x + edgeHitBox && point.x < x + width - edgeHitBox && point.y > y + edgeHitBox && point.y < y + height - edgeHitBox); //only the inside without the edges (because they ment to change the size)
}

int BodyPart::catchEdge(CPoint& point)
{
	//	1		|	2	|	3		|	4	|	5		|	6	|	7		|	8	|
// TopLeft	| Top	| topRight 	| Right	| BotRight	| Bot	| botLeft	| Left	|
	int x = imagePoint.x;
	int y = imagePoint.y;
	if (isBorderSet) {
		if (point.x >= x - edgeHitBox && point.x <= x + edgeHitBox && point.y >= y - edgeHitBox && point.y <= y + edgeHitBox)											return 1;
		else if (point.x > x + edgeHitBox && point.x < x + width - edgeHitBox && point.y > y - edgeHitBox && point.y < y + edgeHitBox)									return 2;
		else if (point.x >= x + width - edgeHitBox && point.x <= x + width + edgeHitBox && point.y >= y - edgeHitBox && point.y <= y + edgeHitBox)						return 3;
		else if (point.x > x + width - edgeHitBox && point.x < x + width + edgeHitBox && point.y > y + edgeHitBox && point.y < y + height - edgeHitBox)					return 4;
		else if (point.x >= x + width - edgeHitBox && point.x <= x + width + edgeHitBox && point.y >= y + height - edgeHitBox && point.y <= y + height + edgeHitBox)	return 5;
		else if (point.x > x + edgeHitBox && point.x < x + width - edgeHitBox && point.y > y + height - edgeHitBox && point.y < y + height + edgeHitBox)				return 6;
		else if (point.x >= x - edgeHitBox && point.x <= x + edgeHitBox && point.y >= y + height - edgeHitBox && point.y <= y + height + edgeHitBox)					return 7;
		else if (point.x > x - edgeHitBox && point.x < x + edgeHitBox && point.y > y + edgeHitBox && point.y < y + height - edgeHitBox)									return 8;
	}
	return 0;
}

void BodyPart::Serialize(CArchive& ar)
{
	if (ar.IsStoring()) //Saving mode
	{
		ar << imageIndex;
		ar << imagePoint;
		ar << width;
		ar << height;
	}
	else // Loading mode
	{
		ar >> imageIndex;
		ar >> imagePoint;
		ar >> width;
		ar >> height;
	}
}

void BodyPart::SerializeName(CArchive& ar)
{
	if (ar.IsStoring()) //Saving mode
	{
		ar << (CString)partName;
	}
}


