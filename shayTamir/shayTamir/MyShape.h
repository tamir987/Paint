#pragma once
class MyShape : public CObject
{
public:
	DECLARE_SERIAL(MyShape)
	MyShape();
	virtual ~MyShape(void);
	void setStart(CPoint p) { start = p; }
	void setEnd(CPoint p) { end = p; }
	void setSize(int sizep) { size = sizep; }
	CPoint getStart() const { return start; }
	CPoint getEnd() const { return end; }
	COLORREF getBg() const { return bgColor; }
	void setBg(COLORREF c) { bgColor = c; }
	virtual void draw(CDC *dc);// calls innerDraw function after we create CPen and CBrush
	virtual void innerDraw(CDC *dc) {}
	void Serialize(CArchive& archive);
	bool isIn(CPoint); // check if the point is in any shape
	virtual int getId() {return 0;}
	CPoint start, end;
	int size;
protected:
	COLORREF bgColor;
};
