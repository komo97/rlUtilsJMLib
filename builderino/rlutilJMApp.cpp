#include "rlutilJMApp.h"
#include <cstdlib>

void rlUtilJMApp::Draw()
{
	
}

void rlUtilJMApp::Start()
{
	Draw();
	DrawStep();
}

void rlUtilJMApp::Update()
{
	Draw();
}

void _cdecl* rlUtilJMApp::OnClose()
{

}

void rlUtilJMApp::App()
{
	this->Start();
	
	while (1)
	{
		this->Update();
		std::atexit(this->rlUtilJMApp::OnClose);
	}


}

void rlUtilJMApp::DrawStep()
{
	rlUtilJM::startDrawThread(rlUtilJM::executeDraw);
}
