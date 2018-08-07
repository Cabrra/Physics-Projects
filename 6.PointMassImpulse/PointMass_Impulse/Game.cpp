
#include"CommonFile.h"

//number of bodies
#define    NBODIES     3  

static cGame* game;   
RIGIDBODY  ball[NBODIES] ;
TCOLLISION collision;

cGame::cGame():cGameWindows()
{
   

}




cGame::~cGame()
{
  

}



bool SetupMatrices()
{
   
	D3DXVECTOR3 position(0.0f,0.0f,-20.0f);
	D3DXVECTOR3 target(0.0f,0.0f,0.0f);
	D3DXVECTOR3 up(0.0f,1.0f,0.0f);
	D3DXMatrixLookAtLH(&game->viewMatrix,&position,&target,&up);
	D3DXMatrixPerspectiveFovLH(&game->projectionMatrix,D3DX_PI/2.0f ,(float)WIDTH /(float)HEIGHT ,1.0f,10000.0f);

	return true;
}



bool cGame::InitializeGame()
{
    // Iniatialize lights
	InitializeLight();
	// Initialize world matrices
	SetupMatrices();

	//  load ball1 that is ball[0] by calling Load()
	ball[0].Load("bowlball.x", Device);
	// set its mass=5 kg
	ball[0].mass = 5;
	// initialize its position at (-5,0,0)
	ball[0].position = Vector3D(-5.0f, 0.0f, 0.0f);
	// set its coefficient of restitution to 0.03
	ball[0].coefficientOfRestitution = 0.03f;
	// set its radius t0 0.75 m
	ball[0].radius = 0.75f;
	// set its initial velocity to (6,0,0)
	ball[0].velocity = Vector3D(6.0f, 0.0f, 0.0f);
	// set the force applied to the ball equal to (0.3 , 0 , 0) Newtons
	ball[0].force = Vector3D(0.3f, 0.0f, 0.0f);
   
   // load ball2(that is ball[1]) by calling Load("bowlball.x",Device)
	ball[1].Load("bowlball.x", Device);
	// set ba112 mass=8 kg
	ball[1].mass = 8;
	// initialize its position at (0,-5,0)
	ball[1].position = Vector3D(0.0f, -5.0f, 0.0f);
	//set its coefficient of restitution to 0.02
	ball[1].coefficientOfRestitution = 0.02f;
	//set its radius t0 0.75 m
	ball[1].radius = 0.75f;
    // set its initial velocity to (0,3,0)
	ball[1].velocity = Vector3D(0.0f, 3.0f, 0.0f);
	// set the force applied to the ball equal to (0, 2 , 0) Newtons 
	ball[1].force = Vector3D(0.0f, 2.0f, 0.0f);
	

	// load ball3 (that is ball[2]) by calling Load("bowlball.x",Device)
	ball[2].Load("bowlball.x", Device);
	// set ba113 mass=9kg
	ball[2].mass = 9;
	//  initialize its position at (0,1,0)
	ball[2].position = Vector3D(0.0f, 1.0f, 0.0f);
	// set its coefficient of restitution to 0.9
	ball[2].coefficientOfRestitution = 0.9f;
	// set its radius t0 0.75 m
	ball[2].radius = 0.75;
	// set its initial velocity to (1,-3,0)
	ball[2].velocity = Vector3D(1.0f, -3.0f, 0.0f);
	// set the force applied to the ball equal to (0, -4 , 0) Newtons 
	ball[2].force = Vector3D(0.0f, -4.0f, 0.0f);

	return true;
}




bool cGame::ShutDownD3D()
{
		
	if(Device!=NULL)
	{
		Device->Release();
		Device=NULL;
	    
	}
	if(D3D!=NULL)
	{
		D3D->Release();
        D3D=NULL;
	}

	
		return true;
}

//end of shutdownD3D()



void cGame::UpdateGame(float dt)
{
  

      // set the 3 balls' sum force to existing force 
	  ball[0].totalForces= ball[0].force ;
	  ball[1].totalForces= ball[1].force ; 
	  ball[2].totalForces= ball[2].force;
	  
	 
	   for( int i=0 ; i<NBODIES-1 ; i++)
		  { 
			for(int j=i+1 ; j<NBODIES ; j++)
			{
		       COLLISION_STATE check;
		       check=CheckCollision(ball[i],ball[j]);
			   switch(check)
		    	{

				  case COLLISION:
					  HandleCollision(ball[i],ball[j],collision,dt);
				      forceApplied=false;
				      break;

				  case NO_COLLISION:
					  // do nothing
				  break;

				 case TOUCHING:
				      forceApplied=false;
				 break;

				case  PENETRATING:
					HandleCollision(ball[i],ball[j],collision,dt);
				      forceApplied=false;
			    break;
			}

		 }
	  }  
     

     if(forceApplied)
	  {
        // reset all applird forces  to zero
	  for( int i=0; i<=NBODIES-1 ; i++ ) 
		{
		  ball[i].force=Vector3D(0.0f,0.0f,0.0f);
		}
      
	  }
	 else
	  {
      forceApplied=true;
	  }


     for( int i=0 ; i<= NBODIES-1 ; i++ ) 
		{ 
		  // update each ball by calling Update(dt);
		  ball[i].Update(dt);
	  
		}

     
  

}



bool RenderFrame()
{
    
    Device->SetTransform(D3DTS_VIEW,&game->viewMatrix);
    Device->SetTransform(D3DTS_PROJECTION,&game->projectionMatrix);


	for(int i=0 ;i<=NBODIES-1; i++)  
	{
	   // render each ball by calling Render(Device)
	   ball[i].Render(Device);
	}

	return true;
}




bool cGame::RenderGame()
{
     bool IsRendered=true;
     

	// Clear the backbuffer to a black color
	 
         Device->Clear(0,0,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(0,0,0),1.0f,0);
        // Begin the scene
	   if(SUCCEEDED(Device->BeginScene()))
        { 
           	      
			//rendering goes here
			RenderFrame();

		    // End the scene
            Device->EndScene();

		}

    	else 
	  {
	    	MessageBox(0," BeginScene()-Failed"," Rendering Error" ,MB_OK) ;
			IsRendered=false;
	  }
	
    // Present the backbuffer contents to the display
	  
       Device->Present(0,0,0,0);
	return IsRendered;
}



void cGame::Cleanup()
{
   
	
}



bool InitializeLight()
{
	D3DLIGHT9 light;
	ZeroMemory(&light,sizeof(D3DLIGHT9));
	light.Type=D3DLIGHT_DIRECTIONAL;
	D3DXVECTOR3 lightDirection;
	lightDirection=D3DXVECTOR3(0.0f,-2.0f,1.0f);
	D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction,&lightDirection);

	//set the diffuse color
	light.Diffuse.r=1.0f;
	light.Diffuse.g=1.0f;
	light.Diffuse.b=1.0f;
	light.Diffuse.a=1.0f;
	Device->SetLight(0,&light);
	Device->LightEnable(0,true);
	Device->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE,D3DMCS_MATERIAL);
	// Turn on  D3D lighting.
    Device->SetRenderState(D3DRS_LIGHTING,true);
	return true;
}





INT WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInst,LPSTR lpCmdLine, int nShowCmd)
{
  
 game=new cGame();
  /* Create window */
 game->CreateGameWindows(hInstance,"y	   FULL SAIL - Physics Lab#4:Impulse-Based Particle Collision Response");
 
 /* Setup Direct3D */
 game->InitializeD3D();

 // initialize game
 game->InitializeGame();

 /* Enter message loop */
 game->Run();
 
 /* Shutdown Direct3D */

 game->ShutDownD3D();
 
  delete game ;
 return 0;
}






HRESULT cGame::InitializeD3D()
{
     HRESULT hr=0; // handle to result
	
	// create the IDirect3D object
	if(NULL==(D3D=Direct3DCreate9(D3D_SDK_VERSION)))
	{
  
      MessageBox(NULL,"DIRECT3DCREATE9-FAILED","ERROR",0);	
	  return E_FAIL;
	}
  

  // check the hardware vertex processing capabillty

  D3DCAPS9 caps;
  D3DDEVTYPE deviceType=D3DDEVTYPE_HAL;
  D3D->GetDeviceCaps(D3DADAPTER_DEFAULT,deviceType,&caps);
  
  int vp=0; //vertexProcessing
  
  if(caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)  
  {
	  vp=D3DCREATE_HARDWARE_VERTEXPROCESSING;
  }
  else
  {
	  vp=D3DCREATE_SOFTWARE_VERTEXPROCESSING;
  }

  // create Present Parameter and fill it out.
  D3DPRESENT_PARAMETERS d3dpp;
  ZeroMemory(&d3dpp,sizeof(d3dpp));
  
  d3dpp.BackBufferWidth              =WIDTH;
  d3dpp.BackBufferHeight             =HEIGHT;
  d3dpp.BackBufferFormat             =D3DFMT_A8R8G8B8;
  d3dpp.BackBufferCount              =1;
  d3dpp.AutoDepthStencilFormat       =D3DFMT_D16; // or use D3DFMT_D24S8;
  d3dpp.EnableAutoDepthStencil       =true;
  d3dpp.Flags                        =0;
  d3dpp.FullScreen_RefreshRateInHz   =D3DPRESENT_RATE_DEFAULT;
  d3dpp.hDeviceWindow                =hwnd;
  d3dpp.MultiSampleQuality           =0;
  d3dpp.MultiSampleType              =D3DMULTISAMPLE_NONE;
  d3dpp.PresentationInterval         =D3DPRESENT_INTERVAL_IMMEDIATE;
  d3dpp.SwapEffect                   =D3DSWAPEFFECT_DISCARD;
  d3dpp.Windowed                     =true;
  

  // now create the device
  hr=D3D->CreateDevice(D3DADAPTER_DEFAULT,deviceType,hwnd,vp,&d3dpp,&Device);
  if( FAILED (hr))
  {
	  	 D3D->Release();
		 MessageBox(NULL,"CreateDevice()-Failed","ERROR",NULL);
		 return E_FAIL;
	
  }
  
   if(hr==S_OK)
	   {
	      // Turn off culling, so we see the front and back of the 
       /* object.*/
        Device->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);
		Device->SetRenderState(D3DRS_AMBIENT,0xffffffff);

    }

  return hr;
}

//////////////////////////////////////////////////end of initializeD3D()////////////////////////////////////////
