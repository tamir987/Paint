#pragma once
class Command // abstract class of command class : includes a derived class of AddShape, and functions like perform and roll back
{
public:
	Command(void);
	~Command(void);
	virtual void perform() = 0;
	virtual void rollback() = 0;
	virtual int getMyId() = 0;
};

