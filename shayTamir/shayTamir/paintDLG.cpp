#include "stdafx.h"
#include "shayTamir.h"
#include "paintDLG.h"
#include "afxdialogex.h"


IMPLEMENT_DYNAMIC(paintDLG, CDialogEx)

paintDLG::paintDLG(CWnd* pParent)
	: CDialogEx(paintDLG::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	isPressed = false; //bool variable that checks if we pressed left button of the mouse.
	isRefill = false; //bool variable that checks if we pressed the refill button.
	flagBoom = 0; ////checks if we pressed with the mouse inside a shape that we can't drag - like spray or line.
	index = -1; //index of the shape we want to drag.
	size = 1; // size of shapes.
	lastMode = regular;
	myMode = lastMode;
	rect.SetRect(90, 80, 880, 450);
	shapeFactory = RectangleFactory::getInstance();
}

paintDLG::~paintDLG()
{
}

void paintDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON3, undoB);
	DDX_Control(pDX, IDC_BUTTON2, RedoB);
	DDX_Control(pDX, IDC_BUTTON4, clearB);
	DDX_Control(pDX, IDC_BUTTON5, unClearB);
	DDX_Control(pDX, IDC_CHECK1, dragMe);
	DDX_Control(pDX, IDC_BUTTON1, colorChooseB);
	DDX_Control(pDX, IDC_BUTTONSave, saveB);
	DDX_Control(pDX, IDC_BUTTONLoad, loadB);
	DDX_Control(pDX, IDCANCEL, exitB);
	DDX_Control(pDX, IDC_BUTTON6, fillB);
}


BEGIN_MESSAGE_MAP(paintDLG, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_RADIO1, &paintDLG::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &paintDLG::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &paintDLG::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &paintDLG::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_BUTTON1, &paintDLG::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &paintDLG::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &paintDLG::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &paintDLG::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &paintDLG::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &paintDLG::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_CHECK1, &paintDLG::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTONLoad, &paintDLG::OnBnClickedButtonload)
	ON_BN_CLICKED(IDC_BUTTONSave, &paintDLG::OnBnClickedButtonsave)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_RADIO5, &paintDLG::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_BUTTON8, &paintDLG::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON7, &paintDLG::OnBnClickedButton7)
END_MESSAGE_MAP()
BOOL paintDLG::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);		
	colorChooseB.ModifyStyle(0, BS_ICON);
	HICON colors= (HICON)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON2),
        IMAGE_ICON, 50, 50, LR_DEFAULTCOLOR);
	colorChooseB.SetIcon(colors);
	saveB.ModifyStyle(0,BS_ICON);
	HICON save= (HICON)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON3),
        IMAGE_ICON, 50, 50, LR_DEFAULTCOLOR);
	saveB.SetIcon(save);
	loadB.ModifyStyle(0,BS_ICON);
	HICON load= (HICON)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON4),
        IMAGE_ICON, 50, 50, LR_DEFAULTCOLOR);
	loadB.SetIcon(load);
	fillB.ModifyStyle(0,BS_ICON);
	HICON fill= (HICON)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON5),
        IMAGE_ICON, 50, 50, LR_DEFAULTCOLOR);
	fillB.SetIcon(fill);
	unClearB.ModifyStyle(0,BS_ICON);
	HICON unclear= (HICON)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON6),
        IMAGE_ICON, 90, 70, LR_DEFAULTCOLOR);
	unClearB.SetIcon(unclear);
	clearB.ModifyStyle(0,BS_ICON);
	HICON clearall= (HICON)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON7),
        IMAGE_ICON, 90, 70, LR_DEFAULTCOLOR);
	clearB.SetIcon(clearall);
	RedoB.ModifyStyle(0,BS_ICON);
	HICON redo= (HICON)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON8),
        IMAGE_ICON, 50, 50, LR_DEFAULTCOLOR);
	RedoB.SetIcon(redo);
	undoB.ModifyStyle(0,BS_ICON);
	HICON undo= (HICON)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON9),
        IMAGE_ICON, 50, 50, LR_DEFAULTCOLOR);
	undoB.SetIcon(undo);
	exitB.ModifyStyle(0,BS_ICON);
	HICON exit= (HICON)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON10),
        IMAGE_ICON, 90, 50, LR_DEFAULTCOLOR);
	exitB.SetIcon(exit);
	CheckRadioButton(IDC_RADIO1, IDC_RADIO5, IDC_RADIO2);
	m_brush.CreateSolidBrush(RGB(255, 255, 255)); // set the dialog background to be white.
	return TRUE;
}

void paintDLG::OnSysCommand(UINT nID, LPARAM lParam)
{
		CDialogEx::OnSysCommand(nID, lParam);
}

void paintDLG::OnPaint() //"Invalidate"
{
	CPaintDC dc(this);
	dc.Rectangle(90, 80, 880, 450);
	for (int i = 0; i < myShapes.GetSize(); ++i)
			myShapes[i]->draw(&dc); // draw the shapes
	if(myShapes.IsEmpty())
	{
		clearB.EnableWindow(FALSE);
		dragMe.EnableWindow(FALSE);
		dragMe.SetCheck(FALSE);
		GetDlgItem(IDC_RADIO1)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO2)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO3)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO4)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO5)->EnableWindow(TRUE);
		myMode = lastMode;
		fillB.EnableWindow(false);
		HCURSOR hcur;
		hcur = AfxGetApp()->LoadCursorW(MAKEINTRESOURCE(IDC_AFXBARRES_DEFAULT_IMAGE));
		SetClassLong(m_hWnd,GCL_HCURSOR,(LONG)hcur);
	}
	else
	{
		clearB.EnableWindow(TRUE);
		for (int i = 0; i < myShapes.GetSize(); ++i)
		{
			if(!((myShapes[i]->getId() == 4) || (myShapes[i]->getId() == 3) || (myShapes[i]->getId() == 6)))
			{
				dragMe.EnableWindow(true);	
				fillB.EnableWindow(true);
			}
		}
	}	
	CDialogEx::OnPaint();
}

HCURSOR paintDLG::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void paintDLG::OnMouseMove(UINT nFlags, CPoint point) //when we move the mouse : check which mode we are and do his thing.
{
	if(isIn(point, rect.TopLeft(), rect.BottomRight()))
	{
		if(isPressed)
		{
			switch (myMode)
			{
			case refill: break;
				case regular:
				{
					myShapes[myShapes.GetSize() - 1]->setEnd(point);
					InvalidateRect(rect);
					break;
				}
			case brush:
				{
					myShapes[myShapes.GetSize() - 1]->setEnd(point);
					undoB.EnableWindow(TRUE);
					clearB.EnableWindow(TRUE);
					RedoB.EnableWindow(FALSE);
					MyShape *s = shapeFactory->createShape();
					Command *c = new addShape(myShapes, s);
					c->perform();
					commands.push(c);
					s->setBg(color);
					s->setStart(point);
					s->setEnd(point);
					s->size = size;
					Invalidate(false);
					break;
				}
				case graffity:
				{
					myShapes[myShapes.GetSize() - 1]->setEnd(point);
					undoB.EnableWindow(TRUE);
					clearB.EnableWindow(TRUE);
					RedoB.EnableWindow(FALSE);
					MyShape *s = shapeFactory->createShape();
					Command *c = new addShape(myShapes, s);
					c->perform();
					commands.push(c);
					s->setBg(color);
					s->setStart(point);
					s->setEnd(point);
					s->size = size;
					Invalidate(false);
					break;
				}
			case drag:
				{	
					if((flagBoom == 1) || (index < 0 ))
					{
						flagBoom = 0;
						break;
					}
					int deltaSize = myShapes[index]->size;
					myShapes[index]->start.x = point.x - delX + deltaSize;
					myShapes[index]->start.y = point.y - delY + deltaSize;
					myShapes[index]->end.x = point.x + deldelX + deltaSize;
					myShapes[index]->end.y = point.y + deldelY + deltaSize;
				
					InvalidateRect(rect);
					break;
				}
			}
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}

void paintDLG::OnLButtonDown(UINT nFlags, CPoint point) // on left click the button : check which mode we are and do his thing.
{
	if(isIn(point, rect.TopLeft(), rect.BottomRight()))
	{
		undoB.EnableWindow(TRUE);
		clearB.EnableWindow(TRUE);
		RedoB.EnableWindow(FALSE);
		isPressed = true;
		switch(myMode)
		{
		case regular:
			{
				MyShape *s = shapeFactory->createShape();
				Command *c = new addShape(myShapes, s);
				c->perform();
				commands.push(c);
				s->setBg(color);
				s->setStart(point);
				s->setEnd(point);
				s->setSize(size);
				InvalidateRect(rect);
				break;
			}
		case drag:
			{
				for(int i = myShapes.GetSize() - 1; i >= 0; i--)
				{
					if(myShapes[i]->isIn(point))
					{
						if((myShapes[i]->getId() == 4) || (myShapes[i]->getId() == 3) || (myShapes[i]->getId() == 6))
						{
							flagBoom = 1;
							break;
						}
						delX = point.x - myShapes[i]->start.x;
						delY = point.y - myShapes[i]->start.y;
						deldelX = myShapes[i]->end.x - point.x;
						deldelY = myShapes[i]->end.y - point.y;
					
						MyShape *s = shapeFactory->createShape();
						Command *c = new dragShape(myShapes, s, myShapes[i]);
						c->perform();
						commands.push(c);
						s->setBg(color);
						s->setStart(myShapes[i]->getStart());
						s->setEnd(myShapes[i]->getEnd());
						s->size = size;
						index = myShapes.GetSize() - 1;
						InvalidateRect(rect);
						break;
					}
				}
				flagBoom = 1;
				break;
			}
		case graffity:
			{
				MyShape *s = shapeFactory->createShape();
				Command *c = new addShape(myShapes, s);
				c->perform();
				commands.push(c);
				s->setBg(color);
				s->setStart(point);
				s->setEnd(point);
				s->size = size;
				Invalidate(false);
				break;
			}
		case brush:
			{
				MyShape *s = shapeFactory->createShape();
				Command *c = new addShape(myShapes, s);
				c->perform();
				commands.push(c);
				s->setBg(color);
				s->setStart(point);
				s->setEnd(point);
				s->size = size;
				Invalidate(false);
				break;
			}
		case refill:
			{
				isPressed = false;
				isRefill = true;
				for (int i=myShapes.GetSize()-1;i>=0;i--)
				{
					if(myShapes[i]->isIn(point))
					{
						if((myShapes[i]->getId() == 4) || (myShapes[i]->getId() == 3) || (myShapes[i]->getId() == 6))
							break;
						MyShape *s = shapeFactory->createShape();
						Command *c = new dragShape(myShapes, s, myShapes[i]);
						s->setBg(RefillColor);
						s->setStart(myShapes[i]->getStart());
						s->setEnd(myShapes[i]->getEnd());
						s->size = size;
						c->perform();
						commands.push(c);
						InvalidateRect(rect);
						break;
					}
				}
				break;
			}
		}
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}

void paintDLG::OnLButtonUp(UINT nFlags, CPoint point) //when left click, move the mouse and left click again
{
	if(isIn(point, rect.TopLeft(), rect.BottomRight()))
	{
		if((myMode == regular) && (isRefill == false))
			myShapes[myShapes.GetSize() - 1]->setEnd(point);
		isRefill = false;
		index = -1;
		flagBoom = 1;
		isPressed = false;
		InvalidateRect(rect);
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}

HBRUSH paintDLG::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = m_brush;
	return hbr;
}


void paintDLG::OnBnClickedRadio2() //line option
{
	HCURSOR hcur;
	hcur = AfxGetApp()->LoadCursorW(MAKEINTRESOURCE(IDC_AFXBARRES_LINE));
	SetClassLong(m_hWnd,GCL_HCURSOR,(LONG)hcur);
	lastMode = myMode;
	myMode = regular;
	shapeFactory = LineFactory::getInstance();
}


void paintDLG::OnBnClickedRadio3() //rectangle option
{
	HCURSOR hcur;
	hcur = AfxGetApp()->LoadCursorW(MAKEINTRESOURCE(IDC_AFXBARRES_RECT));
	SetClassLong(m_hWnd,GCL_HCURSOR,(LONG)hcur);
	if(dragMe.GetCheck())
		myMode = drag;
	else
	{
		lastMode = myMode;
		myMode = regular;
		shapeFactory = RectangleFactory::getInstance();
	}
}


void paintDLG::OnBnClickedRadio4() ////ellipse option
{
	HCURSOR hcur;
	hcur = AfxGetApp()->LoadCursorW(MAKEINTRESOURCE(IDC_AFXBARRES_ELLIPSE));
	SetClassLong(m_hWnd,GCL_HCURSOR,(LONG)hcur);
	if(dragMe.GetCheck())
		myMode = drag;
	else
	{
		lastMode = myMode;
		myMode = regular;
		shapeFactory = EllipseFactory::getInstance();
	}
}


void paintDLG::OnBnClickedButton1()//choose color to paint with from color plate
{
	CColorDialog dlg;
	if(dlg.DoModal()==IDOK)
	{
		color=dlg.GetColor();
	}
}


void paintDLG::OnBnClickedButton2() //redo button
{
	undoB.EnableWindow(TRUE);
		if(!(undoes.empty()))
		{
			int i = 0;
			do
			{
				Command *c = undoes.top();
				c = undoes.top();
				c->perform();
				commands.push(c);
				undoes.pop();
				i = c->getMyId();

			}
			while(((i == 4) || (i == 6)) && (!(undoes.empty())));
			Invalidate();
			if(undoes.empty())
				RedoB.EnableWindow(FALSE);
		}
		else
			RedoB.EnableWindow(FALSE);
}


void paintDLG::OnBnClickedButton3() //undo button
{
	RedoB.EnableWindow(TRUE);
	if(!(commands.empty()))
	{
		int i = myShapes.GetSize() - 1;
		do
		{
			Command *c = commands.top();
			c = commands.top();
			c->rollback();
			undoes.push(c);
			commands.pop();
			i--;
		}
		while((i >= 0) && ((myShapes[i]->getId() == 4) || (myShapes[i]->getId() == 6)) && (!(commands.empty())));
		Invalidate();
		if(commands.empty())
			undoB.EnableWindow(FALSE);
	}
	else
		undoB.EnableWindow(FALSE);
}


void paintDLG::OnBnClickedButton4() // clear button
{
	isEnabled1 = RedoB.IsWindowEnabled();
	isEnabled2 = undoB.IsWindowEnabled();
	RedoB.EnableWindow(FALSE);
	undoB.EnableWindow(FALSE);
	unClearB.EnableWindow(TRUE);
	for (int i = 0; i < myShapes.GetSize(); i++)
	{
		Command *c = new addShape(myShapes, myShapes[i]);
		temp.push(c);
	}
	if(myShapes.IsEmpty() == false)
		myShapes.RemoveAll();
	Invalidate();
}

void paintDLG::OnBnClickedButton5() //Unclear button
{
	RedoB.EnableWindow(isEnabled1);
	undoB.EnableWindow(isEnabled2);
	clearB.EnableWindow(TRUE);
	unClearB.EnableWindow(FALSE);
	while(temp.empty() == false)
	{
		Command *c = temp.top();
		c->perform();
		temp.pop();
	}
	Invalidate();
}

void paintDLG::OnBnClickedButton6()//choose color to fill the shape with
{
	HCURSOR hcur;
	hcur = AfxGetApp()->LoadCursorW(MAKEINTRESOURCE(IDC_AFXBARRES_FILL));
	SetClassLong(m_hWnd,GCL_HCURSOR,(LONG)hcur);
	myMode=refill;
	CColorDialog dlg;
	if(dlg.DoModal()==IDOK)
	{
		RefillColor=dlg.GetColor();
	}
}

void paintDLG::OnBnClickedRadio1() //spray option
{
	HCURSOR hcur;
	hcur = AfxGetApp()->LoadCursorW(MAKEINTRESOURCE(IDC_AFXBARRES_PEN));
	SetClassLong(m_hWnd,GCL_HCURSOR,(LONG)hcur);
	if(dragMe.GetCheck())
		myMode = drag;
	else
	{
	lastMode = myMode;
	myMode = graffity;
	shapeFactory = SprayFactory::getInstance();
	}
}

bool paintDLG::OnEraseBkGnd()
{
	return true;
}


void paintDLG::OnBnClickedCheck1() //drag check
{
	if(dragMe.GetCheck())
	{
		SetClassLong( m_hWnd,GCL_HCURSOR,(LONG)LoadCursor(NULL, IDC_SIZEALL) );
		lastMode = myMode;
		myMode = drag;
		GetDlgItem(IDC_RADIO1)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO3)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO4)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO5)->EnableWindow(FALSE);
	}
	else
	{
		SetClassLong( m_hWnd,GCL_HCURSOR,(LONG)LoadCursor(NULL, IDC_ARROW) );
		GetDlgItem(IDC_RADIO1)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO2)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO3)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO4)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO5)->EnableWindow(TRUE);
		myMode = lastMode;
	}
}

void paintDLG::OnBnClickedButtonload() // load button
{
	CFile file;
	CFileDialog FileDlg(TRUE);
	FileDlg.m_ofn.lpstrFilter=_T("DATA Files (*.dat)\0*.dat\0");
	FileDlg.m_ofn.lpstrTitle=_T("Load DATA File");
	CString filename;
	if(FileDlg.DoModal()==IDOK)
	{
		filename=FileDlg.GetPathName();
	}
	if(file.Open(filename,CFile::modeRead))
	{
		CArchive ar(&file,CArchive::load);
		myShapes.Serialize(ar);
		ar.Close();
	}
	else
		return;
	file.Close();
	Invalidate();
}

void paintDLG::OnBnClickedButtonsave() //save button
{
	CFile file;
	CFileDialog FileDlg(TRUE);
	FileDlg.m_ofn.lpstrFilter=_T("DATA Files (*.dat)\0*.dat\0");
	FileDlg.m_ofn.lpstrTitle=_T("Save DATA File As");
	CString filename;
	if (FileDlg.DoModal()==IDOK)
	{
		filename=FileDlg.GetPathName();
		filename.Append(_T(".dat"));
	}
	if(file.Open(filename,CFile::modeCreate|CFile::modeWrite))
	{
		CArchive ar(&file, CArchive::store);
		myShapes.Serialize(ar);
		ar.Close();
	}
	else
		return;
	file.Close();
}

void paintDLG::OnBnClickedRadio5() //brush option
{
	HCURSOR hcur;
	hcur = AfxGetApp()->LoadCursorW(MAKEINTRESOURCE(IDC_AFXBARRES_PEN));
	SetClassLong(m_hWnd,GCL_HCURSOR,(LONG)hcur);
	if(dragMe.GetCheck())
		myMode = drag;
	else
	{
		lastMode = myMode;
		myMode = brush;
		shapeFactory = BrushFactory::getInstance();
	}
}


void paintDLG::OnBnClickedButton8()  //size of shape get bigger
{
	if(size < 50)
		size++;
}


void paintDLG::OnBnClickedButton7() //size of shape get lower
{
	if(size > 1)
		size--;
}
