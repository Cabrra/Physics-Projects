
#include"CommonFile.h"



static cGame* game;

 // number of bodies
#define    NBODIES      3 
RIGIDBODY  ball[NBODIES] ;
RIGIDBODY  box;
TCOLLISION collision;

cGame::cGame():cGameWindows()
{
   
 
}




cGame::~cGame()
{
  

}



bool SetupMatrices()
{
   
	D3DXVECTOR3 position(1.0f,4.0f,-9.0f); // 
	D3DXVECTOR3 target(0.0f,0.0f,0.0f);
	D3DXVECTOR3 up(0.0f,1.0f,0.0f);
	D3DXMatrixLookAtLH(&game->viewMatrix,&position,&target,&up);
	D3DXMatrixPerspectiveFovLH(&game->projectionMatrix,D3DX_PI/2.0f ,(float)WIDTH /(float)HEIGHT,1.0f,1000.0f);
	
	return true;
}



bool cGame::InitializeGame()
{
	// Iniatialize lights
	InitializeLight();
	// Initialize world matrices
	SetupMatrices();
	Matrix3D identityMatrix = Matrix3D(1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f);
	float Ixx, Iyy, Izz;
	// load the first ball  
	ball[0].Load("bowlball.x", Device);
	// set its mass m=50 kg
	ball[0].mass = 50.0f;
	// compute ball 1 inverse mass : massInv=1/mass
	ball[0].massInv = 1/ball[0].mass;
	// set its initial position at (-5,0,0)
	ball[0].position = Vector3D(-5, 0, 0);
	//set its coefficient of restitution to 0.03
	ball[0].coefficientOfRestitution = 0.03f;
	// set its radius=0.7m
	ball[0].radius = 0.7f;
	// set its initial velocity to (5,0,0)
	ball[0].velocity = Vector3D(5.0f, 0, 0);
	// set the applied outer force to (10,10,0)Newtons
	ball[0].force = Vector3D(10.0f, 10.0f, 0);
	// set its initial orientation to 90 degree rotation about its local X-axis
	ball[0].orientation = Matrix3D{ 1, 0, 0,
									0, 0, -1,
									0, 1, 0 };
	// set its initial angular velocity to (0,0,0) rad/s
	ball[0].angularVelocity = Vector3D(0, 0, 0);
	// calculate the inertia tensor of the ball(sphere) that is Ixx=Iyy=Izz=(2/5)(mass*radius*radius) ]
	float inertia = (2.0f / 5.0f)*(ball[0].mass*ball[0].radius*ball[0].radius);
	Ixx = Iyy = Izz =  inertia;
	ball[0].Ibody = Matrix3D{ inertia, 0, 0,
		0, inertia, 0,
		0, 0, inertia };
	// load the second ball
	ball[1].Load("bowlball.x", Device);
	// set its mass m=40 kg
	ball[1].mass = 40.0f;
	// compute ball 2 inverse mass
	ball[1].massInv = 1/ball[1].mass;
	// set its initial position at (0,-4,0)
	ball[1].position = Vector3D(0, -4, 0);
	//set its coefficient of restitution to 0.02
	ball[1].coefficientOfRestitution = 0.02f;
	// set its radius=0.7m
	ball[1].radius = 0.7f;
	// set its initial velocity to (0,4,0)
	ball[1].velocity = Vector3D(0, 4, 0);
	// set the applied outer force to (10,20,0)Newtons
	ball[1].force = Vector3D(10, 20, 0);
	// set its initial orientation to be a 90 degree rotation about its local Z-axis.
	ball[1].orientation = Matrix3D{ 0, -1, 0,
									1, 0, 0,
									0, 0, 1};
	// set its initial angular velocity to (0,0,0) rad/s
	ball[1].angularVelocity = Vector3D(0, 0, 0);
	// calculate the inertia tensor of the ball(sphere) that is Ixx=Iyy=Izz=(2/5)(mass*radius*radius) ]
	inertia = (2.0f / 5.0f)*(ball[1].mass*ball[1].radius*ball[1].radius);
	ball[1].Ibody = Matrix3D{ inertia, 0, 0,
		0, inertia, 0,
		0, 0, inertia };
	// load the third ball
	ball[2].Load("bowlball.x", Device);
	// set its mass m=70 kg
	ball[2].mass = 70.0f;
	// compute ball 2 inverse mass
	ball[2].massInv = 1/ball[2].mass;
	// set its initial position at (-4,2,1)
	ball[2].position = Vector3D(-4, 2, 1);
	//set its coefficient of restitution to 0.4
	ball[2].coefficientOfRestitution = 0.4f;
	// set its radius=0.7m
	ball[2].radius = 0.7f;
	// set its initial velocity to (2.5 , 0 , 0)
	ball[2].velocity = Vector3D(2.5f, 0, 0);
	// set the applied outer force to (10,10,0)Newtons
	ball[2].force = Vector3D(10, 10, 0);
	// set its initial orientation to 90 degree rotation about its local X-axis
	ball[2].orientation = Matrix3D{ 1.0f, 0, 0,
		0, 0, -1,
		0, 1, 0 };
	// set its initial angular velocity to (0,0,0) rad/s
	ball[2].angularVelocity = Vector3D(0, 0, 0);
	// calculate the inertia tensor of the ball(sphere) that is Ixx=Iyy=Izz=(2/5)(mass*radius*radius) ]
	inertia = (2.0f / 5.0f)*(ball[2].mass*ball[2].radius*ball[2].radius);
	Ixx = Iyy = Izz = inertia;
	ball[2].Ibody = Matrix3D{ inertia, 0, 0,
		0, inertia, 0,
		0, 0, inertia };
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
  
	//objects update goes here///
	 
	  ball[0].totalForces= ball[0].force ;
	  ball[1].totalForces= ball[1].force ; 
	  ball[2].totalForces= ball[2].force;
	  
	  
	   for( int i=0 ; i<NBODIES-1 ; i++)
		  { 
			for(int j=i+1 ; j<NBODIES ; j++)
			{
		       COLLISION_STATE check;
		       check=CheckCollision(ball[i],ball[j],collision);
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
					  ResolveOverlapping(ball[i],ball[j],collision,dt);
				      forceApplied=false;
			    break;
			}

		 }
	  }  
     

     if(forceApplied)
	  {

	  for( int i=0; i<=NBODIES-1 ; i++ ) 
		{
		  ball[i].force=0.90f*ball[i].force;
		if(ball[i].force.Norm()<0.1f)  ball[i].force=Vector3D(0.0f,0.0f,0.0f);
		  
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

     
  

}// end of UpdateGame()



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
	 
         Device->Clear(0,0,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0) ,1.0f,0);
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
 game->CreateGameWindows(hInstance,"y  FULL SAIL - Physics(Lab#5 ): Rigid Body CollisioN Response Simulations");
 
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
  d3dpp.BackBufferFormat             =D3DFMT_A8R8G8B8;// or use D3DFMT_A8R8G8B8;
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
