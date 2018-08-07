#ifndef _GameWindows_H
#define  _GameWindows_H


#include<d3dx9.h>

#define VC_EXTRALEAN

static const int WIDTH  = 1200; // window width
static const int HEIGHT = 850; // window height


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
	static  LRESULT CALLBACK WndProc(HWND winHandle,UINT _message,WPARAM wParam,LPARAM lParam);          
    LRESULT CALLBACK MessageHandler(UINT _message,WPARAM wParam,LPARAM lParam);
	void Run();

	// virtual functions to implemented in derived class cGame
	virtual void UpdateGame(float dt)=0;
	virtual bool RenderGame()=0;
	virtual bool ShutDownD3D()=0;
	
	
};

#endif


