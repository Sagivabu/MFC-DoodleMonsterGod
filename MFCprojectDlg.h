#include "pch.h"
// MFCprojectDlg.h : header file
//

#pragma once

// CMFCprojectDlg dialog
class CMFCprojectDlg : public CDialogEx
{
// Construction
public:
	CMFCprojectDlg(CWnd* pParent = nullptr);	// standard constructor
	~CMFCprojectDlg()
	{
		for (auto pBP : pImageRightCreature) {
			delete pBP;
		}
		for (auto pBP : pImageLeftCreature) {
			delete pBP;
		}
		if (leftCreature != nullptr) delete leftCreature;
		leftCreature = nullptr;
		if (rightCreature != nullptr) delete rightCreature;
		rightCreature = nullptr;
	}

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCPROJECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMCustomdrawProgress1(NMHDR* pNMHDR, LRESULT* pResult);

	CListCtrl m_listControl; //list control of the images
	CImageList m_imageList; //list of images to build list contrl

	CPaintDC* pCanvas; //overall canvas
	bool isDrawXl=false, isDrawXr=false; //flag for draw X

	bool isPressed = false;	//TRUE while dragging bodyPart (after created)
	bool isSizing = false;	//TRUE while change size of bodyPart
	BodyPart* manipulateBP; //point to the dragged bodyPart
	int bpIndex; //index for the position of the dragged bodyPart in the vector
	int whichEdge = 0;	//return the number of which edge was pressed (reSize)
	bool isLeftVector = true; //TRUE if the dragged bodyPart is from the left vector (FALSE = right vector)

	CTypedPtrArray< CObArray, BodyPart*> bparts; // save / load 

	//messages:
	void fightCanceledM(); // show fight canceled message
	void failed2CreateM();	//failed to create creature message
	void dragonCreatedM();	//dragon message
	void angelCreatedM(); //agnel message
	void cimeraCreatedM(); //cimera message
	void humanoidCreatedM(); //humanoid message
	void reptilianCreatedM(); //reptilian message
	void wingedCreatedM(); //winged creature message
	void leggedCreatedM(); //legged creature message
	void tailedCreatedM(); //tailed creature message
	void slitheringCreatedM(); //slithering creature message


	std::vector<BodyPart*> pImageLeftCreature; //left Creature images
	std::vector<BodyPart*> pImageRightCreature; //right Creature images
	BasicCreature* leftCreature = nullptr;
	BasicCreature* rightCreature = nullptr;

	CListCtrl* m_pDragList;		//Which ListCtrl we are dragging FROM
	CImageList* m_pDragImage;	//For creating and managing the drag-image
	BOOL		m_bDragging;	//True during a drag operation
	int			m_nDragIndex;	//Index of selected item in the List we are dragging FROM
	int			m_nDropIndex;	//Index at which to drop item in the List we are dropping ON
	CWnd* m_pDropWnd;		//Pointer to window we are dropping on (will be cast to CListCtrl* type)

	afx_msg void OnHdnItemclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLvnBegindragList1(NMHDR* pNMHDR, LRESULT* pResult);
	//struct that used for OnMouseMove while dragging the image from control list
	typedef struct {	
		LVITEM* plvi;
		CString sCol2;
	} lvItem, * plvItem;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedclearrbutton();
	afx_msg void OnBnClickedcreaterbuttton();
	afx_msg void OnBnClickedshowstatslbutton();
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnBnClickedclearlbutton();
	afx_msg void OnBnClickedcreatelbutton();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedshowstatsrbutton();
	afx_msg void OnBnClickedfightbutton();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedsavebutton();
	afx_msg void OnBnClickedloadbutton();
	afx_msg void OnBnClickedInstructionbutton();

private:
	void DrawX(); //Draw X if the creature is dead
	void imagesRedraw(); //RePosition left and right creatures depends on Client screen changes

public:
	const std::vector<std::array<LPCTSTR,2>> files = {
		//Heads (11)
		{L"head", L".\\64x64Head1.png"},
		{L"head", L".\\64x64Head2.png"},
		{L"head", L".\\64x64Head3.png"},
		{L"head", L".\\64x64Head4.png"},
		{L"head", L".\\64x64Head5.png"},
		{L"head", L".\\64x64Head6.png"},
		{L"head", L".\\64x64Head7.png"},
		{L"head", L".\\64x64Head8.png"},
		{L"head", L".\\64x64Head9.png"},
		{L"head", L".\\64x64Head10.png"},
		{L"head", L".\\64x64Head11.png"},
		//Torsos (9)
		{L"torso", L".\\64x64Torso1.png"},
		{L"torso", L".\\64x64Torso2.png"},
		{L"torso", L".\\64x64Torso3.png"},
		{L"torso", L".\\64x64Torso4.png"},
		{L"torso", L".\\64x64Torso5.png"},
		{L"torso", L".\\64x64Torso6.png"},
		{L"torso", L".\\64x64Torso7.png"},
		{L"torso", L".\\64x64Torso8.png"},
		{L"torso", L".\\64x64Torso9.png"},
		//Hands (16)
		{L"hand", L".\\64x64Hand1.png"},
		{L"hand", L".\\64x64Hand2.png"},
		{L"hand", L".\\64x64Hand3.png"},
		{L"hand", L".\\64x64Hand4.png"},
		{L"hand", L".\\64x64Hand5.png"},
		{L"hand", L".\\64x64Hand6.png"},
		{L"hand", L".\\64x64Hand7.png"},
		{L"hand", L".\\64x64Hand8.png"},
		{L"hand", L".\\64x64Hand9.png"},
		{L"hand", L".\\64x64Hand10.png"},
		{L"hand", L".\\64x64Hand11.png"},
		{L"hand", L".\\64x64Hand12.png"},
		{L"hand", L".\\64x64Hand13.png"},
		{L"hand", L".\\64x64Hand14.png"},
		{L"hand", L".\\64x64Hand15.png"},
		{L"hand", L".\\64x64Hand16.png"},
		//Legs (8)
		{L"leg", L".\\64x64Leg1.png"},
		{L"leg", L".\\64x64Leg2.png"},
		{L"leg", L".\\64x64Leg3.png"},
		{L"leg", L".\\64x64Leg4.png"},
		{L"leg", L".\\64x64Leg5.png"},
		{L"leg", L".\\64x64Leg6.png"},
		{L"leg", L".\\64x64Leg7.png"},
		{L"leg", L".\\64x64Leg8.png"},
		//Tails (6)
		{L"tail", L".\\64x64Tail1.png"},
		{L"tail", L".\\64x64Tail2.png"},
		{L"tail", L".\\64x64Tail3.png"},
		{L"tail", L".\\64x64Tail4.png"},
		{L"tail", L".\\64x64Tail5.png"},
		{L"tail", L".\\64x64Tail6.png"},
		//Wings(18)	.
		{L"wing", L".\\64x64Wing1.png"},
		{L"wing", L".\\64x64Wing2.png"},
		{L"wing", L".\\64x64Wing3.png"},
		{L"wing", L".\\64x64Wing4.png"},
		{L"wing", L".\\64x64Wing5.png"},
		{L"wing", L".\\64x64Wing6.png"},
		{L"wing", L".\\64x64Wing7.png"},
		{L"wing", L".\\64x64Wing8.png"},
		{L"wing", L".\\64x64Wing9.png"},
		{L"wing", L".\\64x64Wing10.png"},
		{L"wing", L".\\64x64Wing11.png"},
		{L"wing", L".\\64x64Wing12.png"},
		{L"wing", L".\\64x64Wing13.png"},
		{L"wing", L".\\64x64Wing14.png"},
		{L"wing", L".\\64x64Wing15.png"},
		{L"wing", L".\\64x64Wing16.png"},
		{L"wing", L".\\64x64Wing17.png"},
		{L"wing", L".\\64x64Wing18.png"}
	};
};