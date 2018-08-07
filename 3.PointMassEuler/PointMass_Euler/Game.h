
#ifndef  _GAME_H
#define  _GAME_H

#include<d3dx9.h>
#include<D3dx9math.h>
#include<assert.h>
#include<string>
#include<mmsystem.h>
#include"GameWindows.h"



// GLOBAL VARIABLES
static LPDIRECT3DDEVICE9  Device;// = NULL; // directx device
static LPDIRECT3D9        D3D;//    = NULL; // directx object


/********************************************************************************************************************
Author     : Richard Bahin
class      : cGame                                                                                  
base class : cGameWindows																																																			
comment    : Game class  for the Physics simulation frame                                                                                                     
TODO       : None 																											
*********************************************************************************************************************/
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



