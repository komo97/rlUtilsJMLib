#pragma once
#ifndef _RLUTILJMAPP_H_
#define _RLUTILJMAPP_H_

#include "rlutilJM.h"

using namespace rlutilJM;
class rlUtilJMApp : rlUtilJM
{
public:
	virtual void Draw();
	virtual void Start();
	virtual void Update();
	virtual void OnClose();

	void App();
private:
	void DrawStep();
};

#endif