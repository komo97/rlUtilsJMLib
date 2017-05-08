#pragma once
#ifndef _RLUTILJMAPP_H_
#define _RLUTILJMAPP_H_

#include "rlutilJM.h"


class rlUtilJMApp : protected rlUtilJM
{
public:
	///<summary>
	///Overload to add any draw operations. Only call Entity->Draw from here.
	///</summary>
	virtual void Draw();

	///<summary>
	///The first function to be called on the hierarchy. Overload to add setup
	///components.
	///</summary>
	virtual void Start();

	///<summary>
	///This function runs on a game loop, once start finishes No other operations 
	///outside update will be run.
	///</summary>
	virtual void Update();

	///<summary>
	///Run this function from main. After it runs no code outside from it will ever run.
	///</summary>
	void App(const int& windowWidthInPixels, const int& windowHeightInPixels, const char* name);

	///<summary>
	///This function is called once the window receives a signal to close
	///</summary>
	static void OnClose();
private:

	///<summary>
	///Starts the draw thread and all draw operations
	///</summary>
	void DrawStep();


	///<summary>
	///This function is called at the end of the frame
	///</summary>
	void EndOfFrame();
};

#endif