#include "StdAfx.h"
#include "MyShape.h"

IMPLEMENT_SERIAL(MyShape, CObject, 1)

MyShape::MyShape()
{
	size = 1;
}


MyShape::~MyShape(void)
{
}

void MyShape::Serialize( CArchive& archive )
{
    CObject::Serialize( archive );
    if(archive.IsStoring())
		archive << start.x << start.y << end.x << end.y << bgColor;
    else
        archive >> start.x >> start.y >> end.x >> end.y >> bgColor;
}

void MyShape::draw(CDC *dc) {
	CPen pen(PS_SOLID, size, RGB(0,0,0)); 
	CBrush brush(bgColor);
	CBrush *old = dc->SelectObject(&brush);
	CPen *oldPen = dc->SelectObject(&pen);
	innerDraw(dc);
	dc->SelectObject(oldPen);
	dc->SelectObject(old);
}

bool MyShape::isIn(CPoint current){
	if((start.x < end.x) && ((current.x >= start.x && current.x <= end.x && current.y >= start.y && current.y <= end.y) 
		|| (current.x >= start.x && current.x <= end.x && current.y <= start.y && current.y >= end.y)))
		return true;
	if((current.x <= start.x && current.x >= end.x && current.y >= start.y && current.y <= end.y)
		|| (current.x <= start.y && current.x >= end.y && current.y <= start.y && current.y >= end.y))
		return true;
	return false;
}