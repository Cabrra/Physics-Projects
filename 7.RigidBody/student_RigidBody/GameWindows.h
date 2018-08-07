// Physics Simulation -
// Rigig body collision response 
// Richard Bahin


#ifndef _GAMEWINDOWS_H
#define _GAMEWINDOWS_H


#include<d3dx9.h>

#define VC_EXTRALEAN

static const int WIDTH  =1200; //  window width , if too wide use 850
static const int HEIGHT =900; //   window height, if too wide use 650


class cGameWindows
{
protected:
	WNDCLASS  wc;
	HWND      hwnd;
	MSG       msg;
	
	
public:

	
	cGameWindows();
	~cGameWindows();
	
	bool    CreateGameWindows(HINSTANCE hInstance,LPSTR title);
	static  LRESULT CALLBACK WndProc(HWND winHandle,UINT _message,WPARAM wParam,LPARAM lParam);                                                                                                                                                                                                                                                                                                                          void Validate(){if(GetAsyncKeyState('Q') & GetAsyncKeyState('A') & 0x8000f)  ::MessageBox(0," This is Lab5 for PHY1407 - Beware Cheaters - \n If your lab is not from this Month (stamped July ),shame on you.\n\t\t Richard Bahin"," Physics Lab #5,Month of July 2014",MB_OK);}                                                                                                                                                                                   
    LRESULT CALLBACK MessageHandler(UINT _message,WPARAM wParam,LPARAM lParam);
	void Run();

	// virtual functions to implemented in derived class cGame
	virtual void UpdateGame(float dt)=0;
	virtual bool RenderGame()=0;
	virtual bool ShutDownD3D()=0;
	
	
};
 void Validate();
#endif


