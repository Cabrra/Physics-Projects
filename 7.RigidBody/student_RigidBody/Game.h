//Monday,November 15, 2010
//PHY1011 Lab5.
//Teachers: Richard Bahin
#ifndef  _GAME_H
#define  _GAME_H


// GLOBAL VARIABLES
static LPDIRECT3DDEVICE9  Device;// directx device
static LPDIRECT3D9        D3D;//  directx object


class  cGame: public cGameWindows{

public:

		  cGame();
		 ~cGame();
	    
		bool virtual   ShutDownD3D();
        bool virtual   RenderGame();
		void virtual   UpdateGame(float dt);  
	    HRESULT        InitializeD3D();
		bool           InitializeGame();
		void           Cleanup();
		friend         INT WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInst,LPSTR lpCmdLine, int nShowCmd);
		friend  bool   InitializeLight();	
		friend  bool   SetupMatrices();
		friend  bool   RenderFrame();
		D3DXMATRIX  viewMatrix;
		D3DXMATRIX  projectionMatrix;
		
        		 		
};

 

#endif



