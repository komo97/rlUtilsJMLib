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
	rlUtilJM::KeepScreenSize();
	Draw();
}

void rlUtilJMApp::OnClose()
{
	rlUtilJM::RestoreFont();
	rlUtilJM::Cleanup();
}

void rlUtilJMApp::EndOfFrame()
{
	rlUtilJM::AddToDrawThread(rlUtilJM::PrintBuffer);
	std::this_thread::sleep_for(std::chrono::milliseconds(11));
}

void rlUtilJMApp::App(const int& windowWidthInPixels, const int& windowHeightInPixels, const char* name)
{
	rlUtilJM::WindowSize(windowWidthInPixels, windowHeightInPixels);
	rlUtilJM::ChangeWindowTitle(name);
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
