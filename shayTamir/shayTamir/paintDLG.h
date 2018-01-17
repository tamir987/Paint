#pragma once
#include "MyShape.h"
#include "MyEllipse.h"
#include "MyRectangle.h"
#include "MyLine.h"
#include "MySpray.h"
#include "MyBrush.h"
#include "EllipseFactory.h"
#include "LineFactory.h"
#include "RectangleFactory.h"
#include "SprayFactory.h"
#include "BrushFactory.h"
#include <vector>
#include "addShape.h"
#include "dragShape.h"
#include <stack>
#include "afxwin.h"
#include "afxcmn.h"

using namespace std;

// paintDLG dialog

class paintDLG : public CDialogEx
{
	DECLARE_DYNAMIC(paintDLG)

public:
	CRect rect;
	COLORREF RefillColor, color; //RefillColor = color for fill shape, color = color we choose to paint.
	paintDLG(CWnd* pParent = NULL);   // standard constructor
	virtual ~paintDLG();
	// msg
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedButtonload();
	afx_msg void OnBnClickedButtonsave();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton7();
	afx_msg bool OnEraseBkGnd();
	CButton undoB, unClearB, RedoB, clearB, dragMe, colorChooseB, saveB, loadB, exitB, fillB; //CButton for each button
	bool isEnabled1, isEnabled2, spray, isRefill;
	int delX, delY, deldelY, deldelX, flagBoom, index, size;
	enum { IDD = IDD_PAINTDLG };
	enum modeOf{regular, drag, graffity,refill, brush}; // our mode 
	modeOf myMode, lastMode;

	bool isIn(CPoint current, CPoint start, CPoint end){
	if((start.x < end.x) && ((current.x >= start.x && current.x <= end.x && current.y >= start.y && current.y <= end.y) 
		|| (current.x >= start.x && current.x <= end.x && current.y <= start.y && current.y >= end.y)))
		return true;
	if((current.x <= start.x && current.x >= end.x && current.y >= start.y && current.y <= end.y)
		|| (current.x <= start.y && current.x >= end.y && current.y <= start.y && current.y >= end.y))
		return true;
	return false;
}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	HICON m_hIcon;
	CBrush m_brush;
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	bool isPressed;
	CPoint start, end;
	CTypedPtrArray<CObArray, MyShape*> myShapes;
	stack<Command*> commands, undoes, temp; // commands = stack of undo. undoes = stack of redo. temp = stack of clearAll.
	ShapeFactory* shapeFactory;
};
