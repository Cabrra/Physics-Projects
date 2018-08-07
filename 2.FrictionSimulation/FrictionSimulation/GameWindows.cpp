
//#include "CommonFile.h"

#include"GameWindows.h"

cGameWindows::cGameWindows()
{
	hwnd=NULL;
	
}

cGameWindows::~cGameWindows(){ }


bool cGameWindows::CreateGameWindows(HINSTANCE hInstance,LPSTR title)
{
	wc.cbClsExtra      =NULL;
	wc.cbWndExtra      =NULL;
	wc.style           =NULL;
	wc.lpszMenuName    =NULL;
	wc.hCursor         =LoadCursor(NULL,IDC_ARROW);
	wc.hIcon           =LoadIcon(NULL,IDI_APPLICATION);
	wc.hbrBackground   =(HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hInstance       =hInstance;
	wc.lpfnWndProc     =WndProc;
	wc.lpszClassName   ="PhysicsModelling";

	if(!RegisterClass(&wc) ) 
	{
		::MessageBox(NULL,"RegisterClass-FAILED"," win class registr Error",0);
		return false;
	}

	hwnd=CreateWindow("PhysicsModelling",
		              title,
					  WS_OVERLAPPEDWINDOW|WS_VISIBLE,
					  CW_USEDEFAULT,
					  CW_USEDEFAULT,
					  WIDTH,
					  HEIGHT,
					  NULL,
					  NULL,
					  hInstance,
					  NULL);

	::ShowWindow(hwnd,SW_SHOW);
	::UpdateWindow(hwnd);
	
	return true;
}


 LRESULT CALLBACK cGameWindows::MessageHandler(UINT _message,WPARAM wParam,LPARAM lParam)
{
	

	switch( _message )
	{
		
		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;
			break;
			

		case WM_KEYDOWN:
			if(wParam==VK_ESCAPE)
				PostQuitMessage(0);
			    return 0;
				break;
		
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
			break;
			

		default:
			break;
			
	}
 return 1;
}



 LRESULT CALLBACK cGameWindows::WndProc(HWND winHandle,UINT _message,WPARAM wParam,LPARAM lParam)
  {
         
	 cGameWindows *pt=NULL;
	  
	  pt->MessageHandler( _message,wParam,lParam);
	  delete pt;
	  return (DefWindowProc(winHandle, _message, wParam, lParam));

  }



  void cGameWindows::Run()
  {
	  ZeroMemory(&msg,sizeof(msg));
	 

	  while(msg.message!=WM_QUIT)
	  {
		 
		  if( PeekMessage(&msg,0,0,0,PM_REMOVE))
		  {
		 	TranslateMessage(&msg);
			DispatchMessage(&msg);
		  }
		  else
		  {
		   
		   static float lastTime=(float) timeGetTime();
		   float currentTime=(float)timeGetTime();
		   float timeDelta  = (currentTime-lastTime)*0.001;
           UpdateGame(timeDelta);
	       RenderGame();
		   lastTime=currentTime;
	      
		  }
	  }

	  
  }
	
