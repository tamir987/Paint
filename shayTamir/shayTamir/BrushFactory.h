#pragma once
#include "ShapeFactory.h"
#include "MyBrush.h"

class BrushFactory :
	public ShapeFactory
{
public:	
	~BrushFactory(void);
	MyShape* createShape() { return new MyBrush(); }
	static BrushFactory* getInstance() {
		static BrushFactory instance;
		return &instance;
	}
private:
	BrushFactory(void);
};