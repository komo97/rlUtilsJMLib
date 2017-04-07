#include "rlutilJMApp.h"

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

void rlUtilJMApp::OnClose()
{

}

void rlUtilJMApp::App()
{
	this->Start();
	while (1)
		this->Update();
}

void rlUtilJMApp::DrawStep()
{
	rlUtilJM::startDrawThread(rlUtilJM::executeDraw);
}
