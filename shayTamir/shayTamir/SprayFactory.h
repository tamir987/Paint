#pragma once
#include "ShapeFactory.h"
#include "MySpray.h"

class SprayFactory :
	public ShapeFactory
{
public:	
	~SprayFactory(void);
	MyShape* createShape() { return new MySpray(); }
	static SprayFactory* getInstance() {
		static SprayFactory instance;
		return &instance;
	}
private:
	SprayFactory(void);
};

