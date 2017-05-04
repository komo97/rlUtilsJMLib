#include "rlutilJMApp.h"
#include <cstdlib>

void rlUtilJMApp::Draw()
{
	
}

void rlUtilJMApp::Start()
{

	DrawStep();
	Draw();
}

void rlUtilJMApp::Update()
{
	//rlUtilJM::AddToDrawThread(rlUtilJM::ClearBuffer);
	rlUtilJM::KeepScreenSize();
	Draw();
}

void rlUtilJMApp::OnClose()
{
	rlUtilJM::RestoreFont();
}

void rlUtilJMApp::EndOfFrame()
{
	rlUtilJM::AddToDrawThread(rlUtilJM::PrintBuffer);
	msleep(11);
}

void rlUtilJMApp::App(const int& windowWidthInPixels, const int& windowHeightInPixels)
{
	rlUtilJM::WindowSize(windowHeightInPixels, windowHeightInPixels);

	this->Start();
	
	while (1)
	{
		this->Update();
		EndOfFrame();
	}


}

void rlUtilJMApp::DrawStep()
{
	rlUtilJM::startDrawThread(rlUtilJM::executeDraw);
}
