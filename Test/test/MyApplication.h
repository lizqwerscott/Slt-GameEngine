#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H

#include "../../src/Application.h"

using namespace slt;

class MyApplication : public Application
{
public:
	MyApplication();
	~MyApplication();
public:
	virtual void init() override;
	virtual void end() override;
};

#endif
