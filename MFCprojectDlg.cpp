
// MFCprojectDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCproject.h"
#include "MFCprojectDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCprojectDlg dialog



CMFCprojectDlg::CMFCprojectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCPROJECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCprojectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listControl);
}

BEGIN_MESSAGE_MAP(CMFCprojectDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CMFCprojectDlg::OnHdnItemclickList1)
	ON_NOTIFY(LVN_BEGINDRAG, IDC_LIST1, &CMFCprojectDlg::OnLvnBegindragList1)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(clearRButton, &CMFCprojectDlg::OnBnClickedclearrbutton)
	ON_BN_CLICKED(createRButtton, &CMFCprojectDlg::OnBnClickedcreaterbuttton)
	ON_BN_CLICKED(showStatsLButton, &CMFCprojectDlg::OnBnClickedshowstatslbutton)
	ON_WM_SIZING()
	ON_BN_CLICKED(clearLButton, &CMFCprojectDlg::OnBnClickedclearlbutton)
	ON_BN_CLICKED(createLButton, &CMFCprojectDlg::OnBnClickedcreatelbutton)
	ON_WM_RBUTTONDBLCLK()
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(showStatsRButton, &CMFCprojectDlg::OnBnClickedshowstatsrbutton)
	ON_BN_CLICKED(fightButton, &CMFCprojectDlg::OnBnClickedfightbutton)
	ON_WM_RBUTTONUP()
	ON_BN_CLICKED(saveButton, &CMFCprojectDlg::OnBnClickedsavebutton)
	ON_BN_CLICKED(loadButton, &CMFCprojectDlg::OnBnClickedloadbutton)
	ON_BN_CLICKED(InstructionButton, &CMFCprojectDlg::OnBnClickedInstructionbutton)
END_MESSAGE_MAP()


// CMFCprojectDlg message handlers

BOOL CMFCprojectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	// TODO: Add extra initialization here

	//!! 0 - Creating CImageList of images
	m_imageList.Create(64, 64, ILC_COLOR32 | ILC_MASK,8,8);

	
	m_listControl.SetImageList(&m_imageList, TVSIL_NORMAL);

	CImage image;
	CBitmap bmp;
	int i = 0;
	for (auto path : files) {
		image.Load(path[1]);
		bmp.Attach(image.Detach());
		m_imageList.Add(&bmp, RGB(0, 0, 0));
		bmp.Detach();
		m_listControl.InsertItem(i, path[0], i);
		i++;
	}


	//!! 0 - End of Creating Image List 

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.


void CMFCprojectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//!! 0 b - Create the Stadium (board)
		CPaintDC dc(this);
		pCanvas = &dc;
		CRect rect;
		this->GetClientRect(rect); //rect has the window 'size'
		int w = rect.Width(); //w/2 can be the separate to include where the image is.
		int h = rect.Height();
		CPoint P1(w/2, 130); //Top Left of Canvas
		CPoint P2(w/2, h-30); //Bot Right of Canvas
		pCanvas->MoveTo(P1); //move the graphic pointer to P1
		pCanvas->LineTo(P2); //Draw Line from the current graphic pointer(P1) to P2
		DrawX(); //Draw X on the creatures whose dead; 
		pCanvas = nullptr;
		//!! 0 
		
		CDialogEx::OnPaint();

	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCprojectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCprojectDlg::OnNMCustomdrawProgress1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

//Drag an image (after created)
void CMFCprojectDlg::OnLButtonDown(UINT nFlags, CPoint point)
{

	CDialogEx::OnLButtonDown(nFlags, point);
	for (int i = 0; i != pImageLeftCreature.size(); i++){
		if (pImageLeftCreature[i]->isInside(point))
		{
			isPressed = true; //flag for dragging
			bpIndex = i;	//saving the index for later use
			isLeftVector = true; //remind: true = LEFT;
			manipulateBP = pImageLeftCreature[i]; //saving the BP for later use
			return;
		}
		else {
			whichEdge = pImageLeftCreature[i]->catchEdge(point);
			if (whichEdge != 0)
			{

				isSizing = true;
				bpIndex = i;
				isLeftVector = true; //remind: true = LEFT;
				manipulateBP = pImageLeftCreature[i];
				return;

			}
		}
	}
	for (std::vector<BodyPart*>::size_type i = 0; i != pImageRightCreature.size(); i++) {
		if (pImageRightCreature[i]->isInside(point))
		{
			isPressed = true; //flag for dragging
			bpIndex = i;	//saving the index for later use
			isLeftVector = false; //remind: flase = RIGHT;
			manipulateBP = pImageRightCreature[i];	//saving the BP for later use
			return;
		}
		else
		{
			whichEdge = pImageRightCreature[i]->catchEdge(point);
			if (whichEdge != 0)
			{
				isSizing = true;
				bpIndex = i;
				isLeftVector = false; //remind: true = LEFT;
				manipulateBP = pImageRightCreature[i];
				return;

			}
		}

	}
}


void CMFCprojectDlg::OnHdnItemclickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

//!! 1 - Begin of Drag img Process from listControl
void CMFCprojectDlg::OnLvnBegindragList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	m_nDragIndex = pNMLV->iItem; //Saveing the Img index for later use

	//// Create a drag image
	POINT pt;
	int nOffset = 50; //offset in pixels for drag image (up and to the left)
	pt.x = nOffset;
	pt.y = nOffset;

	m_pDragImage = this->m_listControl.CreateDragImage(m_nDragIndex, &pt);
	ASSERT(m_pDragImage); //make sure it was created
	//We will call delete later (in LButtonUp) to clean this up

	//// Change the cursor to the drag image
	////    (still must perform DragMove() in OnMouseMove() to show it moving)
	m_pDragImage->BeginDrag(0, CPoint(nOffset, nOffset/2));
	m_pDragImage->DragEnter(GetDesktopWindow(), pNMLV->ptAction);

	//// Set dragging flag and others
	m_bDragging = TRUE;    //we are in a drag and drop operation
	m_nDropIndex = -1;    //we don't have a drop index yet
	m_pDragList = &m_listControl; //make note of which list we are dragging from
	m_pDropWnd = &m_listControl;    //at present the drag list is the drop list

	SetCapture(); //Capture all mouse messages

	//!! 1 - Now i have finished to Drag the IMG (but now moving or implement it yet
	*pResult = 0;
}

//!! 2 - Tracking the drag:
void CMFCprojectDlg::OnMouseMove(UINT nFlags, CPoint point)
{

	if (m_bDragging) //TRUE if we are in dragging mode
	{
		//// Move the drag image
		CPoint pt(point);    //get our current mouse coordinates
		ClientToScreen(&pt); //convert to screen coordinates
		m_pDragImage->DragMove(pt); //move the drag image to those coordinates
		// Unlock window updates (this allows the dragging image to be shown
				// smoothly)
		m_pDragImage->DragShowNolock(false);

		// Get the CWnd pointer of the window that is under the mouse cursor (return a pointer to where the cursor is hovering over)
		CWnd* pDropWnd = WindowFromPoint(pt);
		ASSERT(pDropWnd); //make sure we have a window

		/* @@@@@@@@ Highlight the item we are dragging @@@@@@@ */
		//// If we drag outside current window we need
		//   to adjust the highlights displayed
		if (pDropWnd != m_pDropWnd)
		{
			//If we drag over the CListCtrl header, turn off the
			// hover highlight
			if (m_nDropIndex != -1)
			{
				TRACE("m_nDropIndex is -1\n");
				CListCtrl* pList = (CListCtrl*)m_pDropWnd;
				VERIFY(pList->SetItemState(m_nDropIndex, 0,
					LVIS_DROPHILITED));
				// redraw item
				VERIFY(pList->RedrawItems(m_nDropIndex,
					m_nDropIndex));
				pList->UpdateWindow();
				m_nDropIndex = -1;
			}
			else //If we drag out of the CListCtrl altogether
			{
				TRACE("m_nDropIndex is not -1\n");
				CListCtrl* pList = (CListCtrl*)m_pDropWnd;
				int i = 0;
				int nCount = pList->GetItemCount();
				for (i = 0; i < nCount; i++)
				{
					pList->SetItemState(i, 0, LVIS_DROPHILITED);
				}
				pList->RedrawItems(0, nCount);
				pList->UpdateWindow();
			}
		}
		/* @@@@@@@ End of Highlighting @@@@@@@@ */

		// @@@ Start of Highlight which window we are hovering over @@@ //

		// Save current window pointer as the CListCtrl we are dropping onto
		m_pDropWnd = pDropWnd;

		// Convert from screen coordinates to drop target client coordinates
		pDropWnd->ScreenToClient(&pt);

		//If we are hovering over a CListCtrl we need to adjust the highlights
		if (pDropWnd->IsKindOf(RUNTIME_CLASS(CListCtrl)))
		{
			UINT uFlags;
			CListCtrl* pList = (CListCtrl*)pDropWnd;

			// Turn off hilight for previous drop target
			pList->SetItemState(m_nDropIndex, 0, LVIS_DROPHILITED);
			// Redraw previous item
			pList->RedrawItems(m_nDropIndex, m_nDropIndex);

			// Get the item that is below cursor
			m_nDropIndex = ((CListCtrl*)pDropWnd)->HitTest(pt, &uFlags);
			// Highlight it
			pList->SetItemState(m_nDropIndex, LVIS_DROPHILITED,
				LVIS_DROPHILITED);
			// Redraw item
			pList->RedrawItems(m_nDropIndex, m_nDropIndex);
			pList->UpdateWindow();
		}
		// Lock window updates
		m_pDragImage->DragShowNolock(true);
		// @@@ End of Highlight which window we are hovering over @@@ //

		//!! 2 - End of Tracking the drag section
	}
	CDialogEx::OnMouseMove(nFlags, point);
}

void CMFCprojectDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	//!! 3 - Ending the drag for listControl
	if (m_bDragging) //TRUE if we are in dragging mode
	{
		ReleaseCapture(); // Release mouse capture, so that other controls can get control/messages
		// Note that we are NOT in a drag operation
		m_bDragging = FALSE;

		// End dragging image
		m_pDragImage->DragLeave(GetDesktopWindow());
		m_pDragImage->EndDrag();
		delete m_pDragImage;
		//must delete it because it was created at the beginning of the drag
		
		//@@@@@@ To identify which window we are hovering over (Saftey for dropdown the image in the right place) @@@@@@//

		CPoint pt(point); //Get current mouse coordinates
		ClientToScreen(&pt); //Convert to screen coordinates
		CWnd* pDropWnd = WindowFromPoint(pt); // Get the CWnd pointer of the window that is under the mouse cursor
		ASSERT(pDropWnd); //make sure we have a window pointer
		if (pDropWnd->IsKindOf(RUNTIME_CLASS(CWnd)) && point.y > 140)
		{
			//Creatre the BodyPart and insert it to left / right creature's vector<bodyParts>, also draw the image in the window
			LVITEMW x{}; 
			x.iItem = m_nDragIndex;
			CString partName = m_listControl.GetItemText(x.iItem, 0);

			BodyPart* pBP = nullptr; //create the bodypart by depands on its name
			if(partName ==_T("head")) {
				pBP = new Head;
			}
			else if(partName ==_T("torso")) {
				pBP = new Torso;
			}
			else if(partName ==_T("hand")) {
				pBP = new Hand;
			}
			else if(partName ==_T("leg")) {
				pBP = new Leg;
			}
			else if(partName ==_T("tail")) {
				pBP = new Tail;
			}
			else if(partName ==_T("wing")) {
				pBP = new Wing;
			}
			else
			{
				throw std::runtime_error("Nothing was dragged");
			}

			CRect rect;
			this->GetClientRect(rect);
			pBP->imagePoint.SetPoint(point.x - 30, point.y - 25);
			pBP->imageIndex = m_nDragIndex; //for later use (serialize)
			pBP->create(this, files, m_nDragIndex,rect.Width()/2); //create the Body Part

			if (point.x < (rect.Width() / 2))
			{
				pImageLeftCreature.push_back(pBP);
			}
			else
			{
				pImageRightCreature.push_back(pBP);
			}

			if (m_hWnd) //refresh the client function
			{
				Invalidate();
				RedrawWindow();
			}
		}

		// @@@@@ End of identification @@@@@ //
		//!! 3 - End of Ending the drag
	}
	//Draggin the image after it was created
	if (isPressed)
	{
		POINT pt;
		pt.x = point.x - manipulateBP->width / 2;
		pt.y = point.y - manipulateBP->height / 2;

		CRect rect;
		this->GetClientRect(rect);
		isPressed = false;
		manipulateBP->setPosition(pt.x, pt.y);
		if (point.x > rect.Width() / 2 && isLeftVector) //TRUE = in left vector
		{
			pImageLeftCreature.erase(pImageLeftCreature.begin() + bpIndex);
			pImageRightCreature.push_back(manipulateBP);
		}
		else if (point.x < rect.Width() / 2 && !isLeftVector) //FALSE = in right vector
		{
			pImageRightCreature.erase(pImageRightCreature.begin() + bpIndex);
			pImageLeftCreature.push_back(manipulateBP);
		}
		if (m_hWnd) //refresh the client function
		{
			Invalidate();
			RedrawWindow();
		}
	}
	//Sizing the picture control
	if (isSizing)
	{
		isSizing = false;
		//	1		|	2	|	3		|	4	|	5		|	6	|	7		|	8	|
		// TopLeft	| Top	| topRight 	| Right	| BotRight	| Bot	| botLeft	| Left	|
		int yDiff, xDiff;
		switch (whichEdge)
		{
		case 1:
			xDiff = point.x - manipulateBP->imagePoint.x;
			yDiff = point.y - manipulateBP->imagePoint.y;
			manipulateBP->reSize(manipulateBP->width - xDiff, manipulateBP->height - yDiff);
			manipulateBP->setPosition(point.x, point.y);
			break;
		case 2:
			yDiff = point.y - manipulateBP->imagePoint.y;
			manipulateBP->reSize(manipulateBP->width, manipulateBP->height - yDiff);
			manipulateBP->setPosition(manipulateBP->imagePoint.x, point.y);
			break;
		case 3:
			xDiff = point.x - manipulateBP->imagePoint.x - manipulateBP->width;
			yDiff = point.y - manipulateBP->imagePoint.y;
			manipulateBP->reSize(manipulateBP->width + xDiff, manipulateBP->height - yDiff);
			manipulateBP->setPosition(manipulateBP->imagePoint.x, point.y);
			break;
		case 4:
			xDiff = point.x - manipulateBP->imagePoint.x - manipulateBP->width;
			manipulateBP->reSize(manipulateBP->width + xDiff, manipulateBP->height);
			break;
		case 5:
			xDiff = point.x - manipulateBP->imagePoint.x - manipulateBP->width ;
			yDiff = point.y - manipulateBP->imagePoint.y - manipulateBP->height;
			manipulateBP->reSize(manipulateBP->width + xDiff, manipulateBP->height + yDiff);
			break;
		case 6:
			yDiff = point.y - manipulateBP->imagePoint.y - manipulateBP->height;
			manipulateBP->reSize(manipulateBP->width, manipulateBP->height + yDiff);
			break;
		case 7:
			xDiff = point.x - manipulateBP->imagePoint.x;
			yDiff = point.y - manipulateBP->imagePoint.y - manipulateBP->height;
			manipulateBP->reSize(manipulateBP->width - xDiff, manipulateBP->height + yDiff);
			manipulateBP->setPosition(point.x, manipulateBP->imagePoint.y);
			break;
		case 8:
			xDiff = point.x - manipulateBP->imagePoint.x;
			manipulateBP->reSize(manipulateBP->width - xDiff, manipulateBP->height);
			manipulateBP->setPosition(point.x, manipulateBP->imagePoint.y);
			break;
		}
		if (m_hWnd) //refresh the client function
		{
			Invalidate();
			RedrawWindow();
		}
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}

//For Sizing the window
void CMFCprojectDlg::imagesRedraw()
{
	CRect cRect;
	this->GetClientRect(cRect);
	for (auto pBP : pImageLeftCreature) {
		pBP->setPosition(cRect.Width()/2 - pBP->x2MidWidth, pBP->imagePoint.y);
	}
	for (auto pBP : pImageRightCreature) {
		pBP->setPosition(cRect.Width()/2 - pBP->x2MidWidth, pBP->imagePoint.y);
	}
}

//When Sizing the window
void CMFCprojectDlg::OnSizing(UINT fwSide, LPRECT pRect)
{

	CDialogEx::OnSizing(fwSide, pRect);
	imagesRedraw();
}

//Draw X if the creature is dead
void CMFCprojectDlg::DrawX()
{
	//!! 20 b
	CRect rect;
	this->GetClientRect(rect); //rect has the window 'size' now
	//CPaintDC canvas(this);


	int x, y; //X,Y of the top left corner of the creatures canvas

	if (isDrawXl)
	{
		x = 0;
		y = 130;
		CPoint Ptl1(x, y);											//next 4 points to draw left X
		CPoint Pbr1(x + rect.Width() / 2, rect.Height() - 30); //-70 cause the canvas is little lift above some buttons
		CPoint Ptr1(x + rect.Width() / 2, y);
		CPoint Pbl1(x, rect.Height() - 30);
		pCanvas->MoveTo(Ptl1); //move the graphic pointer to Ptl
		pCanvas->LineTo(Pbr1); //Draw Line from the current graphic pointer(Ptl) to Pbr
		pCanvas->MoveTo(Ptr1); //move the graphic pointer to Ptr
		pCanvas->LineTo(Pbl1); //Draw Line from the current graphic pointer(Ptr) to Pbl
	}
	if (isDrawXr)
	{
		x = rect.Width() / 2;
		y = 130;
		CPoint Ptl2(x, y);											//next 4 points to draw right X
		CPoint Pbr2(rect.Width(), rect.Height() - 30); //-70 cause the canvas is little lift above some buttons
		CPoint Ptr2(rect.Width(), y);
		CPoint Pbl2(x, rect.Height() - 30);
		pCanvas->MoveTo(Ptl2); //move the graphic pointer to Ptl
		pCanvas->LineTo(Pbr2); //Draw Line from the current graphic pointer(Ptl) to Pbr
		pCanvas->MoveTo(Ptr2); //move the graphic pointer to Ptr
		pCanvas->LineTo(Pbl2); //Draw Line from the current graphic pointer(Ptr) to Pbl
	}
	//!! 20 e
}

//Left 'Clear' Button
void CMFCprojectDlg::OnBnClickedclearlbutton()
{
	for (auto pBP : pImageLeftCreature) {	//delete the vector's bodyParts and remove them from screen
		pBP->control.ShowWindow(SW_HIDE);
		delete pBP;
	}
	UpdateWindow(); //refresh the window from the bodyparts
	pImageLeftCreature.clear(); //remove the vector elements
	isDrawXl = false;
	if (leftCreature != nullptr) delete leftCreature;
	leftCreature = nullptr;
	if (m_hWnd) //refresh the client function
	{
		Invalidate();
		RedrawWindow();
	}

}

//Right 'Clear' Button
void CMFCprojectDlg::OnBnClickedclearrbutton()
{
	for (auto pBP : pImageRightCreature) {
		pBP->control.ShowWindow(SW_HIDE);
		delete pBP;
	}
	UpdateWindow();
	pImageRightCreature.clear(); // need to upgrade! - most move all the images far away and delete all of them.
	isDrawXr = false;
	if (rightCreature != nullptr) delete rightCreature;
	rightCreature = nullptr;
	if (m_hWnd) //refresh the client function
	{
		Invalidate();
		RedrawWindow();
	}

}

//Left 'Create' button
void CMFCprojectDlg::OnBnClickedcreatelbutton()
{
	if (leftCreature != nullptr)	//first delete the previous picture and then create the new one
	{
		delete leftCreature;
	}
	leftCreature = createCreature(this,pImageLeftCreature);
}

//Right 'Create' button
void CMFCprojectDlg::OnBnClickedcreaterbuttton()
{
	if (rightCreature != nullptr)	//first delete the previous picture and then create the new one
	{
		delete rightCreature;
	}
	rightCreature = createCreature(this,pImageRightCreature);
}

//Left 'show stats' button
void CMFCprojectDlg::OnBnClickedshowstatslbutton()
{
	creatureStats(leftCreature);
}

//Right 'show stats' button
void CMFCprojectDlg::OnBnClickedshowstatsrbutton()
{
	creatureStats(rightCreature);
}

//Double-Click - show/hide borders (allow to reSize)
void CMFCprojectDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	/// Was meant to Display / Hide the borders of the picture
	for (auto pBP : pImageLeftCreature)
		if (pBP->isInside(point))
		{
			pBP->ShowHideBorders();
		}
	for (auto pBP : pImageRightCreature)
		if (pBP->isInside(point))
			pBP->ShowHideBorders();
	if (m_hWnd) //refresh the client function
	{
		Invalidate();
		RedrawWindow();
	}
	CDialogEx::OnLButtonDblClk(nFlags, point);
}

//'Fight' button
void CMFCprojectDlg::OnBnClickedfightbutton()
{
	if (leftCreature && rightCreature) Fight(this, *leftCreature, *rightCreature);
	else fightCanceledM();
	if (m_hWnd) //refresh the client function
	{
		Invalidate();
		RedrawWindow();
	}
}

//set the select picture control in front
void CMFCprojectDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	for (auto pBP : pImageLeftCreature)
		if (pBP->isInside(point))
			pBP->control.SetWindowPos(&wndBottom, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); 
	for (auto pBP : pImageRightCreature)
		if (pBP->isInside(point))
			pBP->control.SetWindowPos(&wndBottom, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	if (m_hWnd) //refresh the client function
	{
		Invalidate();
		RedrawWindow();
	}
	CDialogEx::OnRButtonUp(nFlags, point);
}

//'Save' button - SOS
void CMFCprojectDlg::OnBnClickedsavebutton()
{
	//step 0 - one array for left + right creatures together
	for (auto pBP : pImageLeftCreature)
		bparts.Add(pBP);
	for (auto pBP : pImageRightCreature)
		bparts.Add(pBP);
	//now there is 1 array that has both creatures

	// FALSE to SAVE
	CFileDialog dlg(FALSE, _T(".creature"), NULL, 0, _T("Creature (*.creature)|*.creature|All Files (*.*)|*.*||"));
	CString filename;
	if (dlg.DoModal() == IDOK)
	{
		filename = dlg.GetPathName(); // return full path and filename
		CFile file(filename, CFile::modeCreate | CFile::modeWrite);
		CArchive ar(&file, CArchive::store);
		ar << (DWORD)bparts.GetCount();  // write the number of BodyParts as DWORD
		ar << (DWORD)pImageLeftCreature.size(); // write the number of pImageLeftCreature	(pImageLeftCreature = count - leftVcount
		for (int i = 0; i < bparts.GetCount(); i++)	//Serialize all the bParts names first;
		{
			bparts[i]->SerializeName(ar);    // write shape
		}
		for (int i = 0; i < bparts.GetCount(); i++)	//Serialize all the bParts objects;
		{
			bparts[i]->Serialize(ar);    // write shape
		}
		ar.Close();
		file.Close();
	}
}

//'Load' button
void CMFCprojectDlg::OnBnClickedloadbutton()
{
	// TRUE to LOAD
	CFileDialog dlg(TRUE, _T(".creature"), NULL, 0, _T("Creature (*.creature)|*.creature|All Files (*.*)|*.*||"));
	CString filename;
	if (dlg.DoModal() == IDOK)
	{
		OnBnClickedclearlbutton(); //first lets clear left side
		OnBnClickedclearrbutton(); //then clear right side
		filename = dlg.GetPathName(); // return full path and filename
		CFile file(filename, CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		DWORD count, leftVcount, rightVcount;
		ar >> count;		//get BodyParts count
		ar >> leftVcount;	//get pImageLeftCreature (pImageLeftCreature = count - leftVcount
		std::vector<BodyPart*> vtemp;
		for (int i = 0; i < count; i++) //create all the bodyParts objects and temporary save them in v
		{
			BodyPart* pBP = nullptr; //create the bodypart by depands on its name
			CString partName;
			ar >> partName;
			if (partName == _T("head")) {
				pBP = new Head;
			}
			else if (partName == _T("torso")) {
				pBP = new Torso;
			}
			else if (partName == _T("hand")) {
				pBP = new Hand;
			}
			else if (partName == _T("leg")) {
				pBP = new Leg;
			}
			else if (partName == _T("tail")) {
				pBP = new Tail;
			}
			else if (partName == _T("wing")) {
				pBP = new Wing;
			}
			vtemp.push_back(pBP);
		}//now v.temp contain all the new 

		CRect rect;
		this->GetClientRect(rect);
		for (int i = 0; i < count; i++)
		{
			vtemp[i]->Serialize(ar);
			if (i < leftVcount)
				pImageLeftCreature.push_back(vtemp[i]);
			else
				pImageRightCreature.push_back(vtemp[i]);
			vtemp[i]->create(this, files,vtemp[i]->imageIndex, rect.Width() / 2); //create the Body Part
		}
		ar.Close();
		file.Close();
		Invalidate();
	}
}

//'Instructions' button
void CMFCprojectDlg::OnBnClickedInstructionbutton()
{
	MessageBox(TEXT("How to Play?\n1. Build Left / Right Creature using images.\n2. 'Create' to create a creature from the images.\n3. Fight till Death!\n\nNote: Create more than 10 types of creatures! each has different stats!\n\n\nFunctions:\n1. Images are draggable to left / right box.\n2. Double-Click - Show/Hide image's borders (allow to reSize).\n3. Left-Click - Brings an image to the front.\n4. 'Clear' - Delete the creature.\n5. 'Show Stats' - Examine the creature you created."), TEXT("Instructions"), MB_ICONINFORMATION);
}

//Fight is Canceled Message
void CMFCprojectDlg::fightCanceledM()
{
	MessageBox(TEXT("One of your creatures is Dead / Unexist !\nPlease 'Create' a new creature."), TEXT("Fight is Canceled!"), MB_ICONWARNING);
}

//Failed to Create Message 
void CMFCprojectDlg::failed2CreateM()
{
	MessageBox(TEXT("This is not a creature in my Data base!\nTry diffrenet combination of body parts!"), TEXT("Failed to Create!"), MB_ICONWARNING);
}

//Dragon created Message
void CMFCprojectDlg::dragonCreatedM()
{
	MessageBox(TEXT("Dragon - has been created successfully!"), TEXT("Congratulations!"), MB_ICONINFORMATION);
}

//Angel created Message
void CMFCprojectDlg::angelCreatedM()
{
	MessageBox(TEXT("Angel - has been created successfully!"), TEXT("Congratulations!"), MB_ICONINFORMATION);
}

//Cimera created Message
void CMFCprojectDlg::cimeraCreatedM()
{
	MessageBox(TEXT("Cimera - has been created successfully!"), TEXT("Congratulations!"), MB_ICONINFORMATION);
}

//Humanoid created Message
void CMFCprojectDlg::humanoidCreatedM()
{
	MessageBox(TEXT("Humanoid - has been created successfully!"), TEXT("Congratulations!"), MB_ICONINFORMATION);
}

//Reptilian created Message
void CMFCprojectDlg::reptilianCreatedM()
{
	MessageBox(TEXT("Reptilian - has been created successfully!"), TEXT("Congratulations!"), MB_ICONINFORMATION);
}

//Winged Creature created Message
void CMFCprojectDlg::wingedCreatedM()
{
	MessageBox(TEXT("Winged Creature - has been created successfully!"), TEXT("Congratulations!"), MB_ICONINFORMATION);
}

//Legged Creature created Message
void CMFCprojectDlg::leggedCreatedM()
{
	MessageBox(TEXT("Legged Creature - has been created successfully!"), TEXT("Congratulations!"), MB_ICONINFORMATION);
}

//Tailed Creature created Message
void CMFCprojectDlg::tailedCreatedM()
{
	MessageBox(TEXT("Tailed Creature - has been created successfully!"), TEXT("Congratulations!"), MB_ICONINFORMATION);
}

//Slithering Creature created Message
void CMFCprojectDlg::slitheringCreatedM()
{
	MessageBox(TEXT("Slithering Creature - has been created successfully!"), TEXT("Congratulations!"), MB_ICONINFORMATION);
}
