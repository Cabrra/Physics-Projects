
#include"Game.h"



static cGame* game;
Camera camera;
RigidBody ball;
Ground ground;

cGame::cGame():cGameWindows()
{
   
 
}




cGame::~cGame()
{
  

}



bool SetupMatrices()
{
    // setup  the projection matrix
	D3DXMatrixPerspectiveFovLH(&game->projectionMatrix,D3DX_PI/2.0f ,(float)WIDTH /(float)HEIGHT ,1.0f,1000.0f);
	Device->SetTransform(D3DTS_PROJECTION,&game->projectionMatrix);
	return true;
}



bool cGame::InitializeGame()
{
	 const float PI=3.14f;

    // Iniatialize lights
	InitializeLight();
	// Initialize world and view  matrices
	SetupMatrices();
	ground.position=D3DXVECTOR3(0,0,0);
	ground.CreatePlane(Device,"desert.bmp");

	
    // load the boal by calling Load() with model filename being "bowlball.x" and theDevice=Device 
	ball.Load("bowlball.x",Device);
	//set the ball mass=10kg
	ball.mass = 10;
	// set ball radius to 0.7m
	ball.radius = 0.7f;
	// set the ball position at (1 ,0.7,-1)m
	ball.position = Vector3D(1.0f, 0.7f, -1.0f);
	// set the ball linear velocity to (0,0,0)m/s;
	ball.linearVelocity = Vector3D(0, 0, 0);
	// set the ball vector gravity to (0,-9.81,0)m/s2 
	ball.gravity = Vector3D(0, -9.81, 0);
	// set the ball Dynamic Friction Coefficient to 0.3 .
	ball.DynamicFrictionCoefficient = 0.3f;
	// set the ball Static Friction Coefficient  to 0.7
	ball.StaticFrictionCoefficient = 0.7f;
	// set the ball DragCoefficient to 0.04 
	ball.dragCoefficient = 0.04f;
	// set the ball coefficient of Restitution to 0.80f;
	ball.coefficientOfRestitution = 0.8f;
	// compute the ball weight
	ball.weight = ball.gravity * ball.mass;
	// compute the normal force on the ball. remember N + W =0 so ==> N=-W=-mg
	ball.normalForce = -ball.weight;
	// compute ball area
	ball.area = 4 * PI*ball.radius*ball.radius;
	// set the air density rho on the ball to 1.
	ball.rho = 1;
	return true;
}





void cGame::UpdateGame(float dt)
{
   
      static bool forceApplied=false; // to help apply a one time force to the ball.

	camera.Update(dt);
    Device->SetTransform(D3DTS_VIEW,&camera.GetViewMatrix());

    if(!forceApplied) 
	   {  
		  // if force not yet applied to the ball ,apply a  force ( 100, 400,0 ) Newton to it.
		   // this force will be applied once
		ball.force = Vector3D(100, 400, 0);
		   // set forceApplied to true
		forceApplied = true;
	}
	  else
	   {
	      // if force already applied , decrease its intensity by using a dumping factor=0.99 ( force=0.99*force)
		  ball.force = 0.99 * ball.force;
		 
		 // now clamp the force to zero vector if its magnitude reaches 0.1 Newton.
		  if (ball.force.x < 0.1)
			  ball.force.x = 0;
		  if (ball.force.y < 0.1)
			  ball.force.y = 0;
		  if (ball.force.z < 0.1)
			  ball.force.z = 0;

       }


	COLLISION_STATE  check ;
    // initialize check to No_COLLISION
	check = NO_COLLISION;
    // Check for collision between the ball and the ground
	check = CheckSpherePlaneCollision(ball, ground);
	switch(check)
	{
		// If no collision ,do the followings
	case NO_COLLISION : 
		// compute total force applied=force + weight + dragforce
		ball.totalForces = ball.force+ ball.weight + ball.dragForce;
		// compute acceleration using Newton 2nd law .
		ball.linearAcceleration = ball.totalForces / ball.mass;
			// compute the velocity
		ball.linearVelocity = ball.linearVelocity + ball.linearAcceleration * dt;
		break;
		// If collision
	case COLLISION:
		// Handle sphere plane collision HandleSpherePlaneCollision(ball,ground)
		HandleSpherePlaneCollision(ball, ground);
		break;
		// if resting contact
	case RESTING_CONTACT:
		// handle Resting contact by calling HandleRestingContact(ball,ground,dt)
		HandleRestingContact(ball, ground, dt);

		break;
	}
	
	// update the ball by calling Update(dt)
	ball.Update(dt);
}



bool RenderFrame()
{
    // render the ball
	ball.Render(Device);
	// render the ground
	ground.Render(Device);
	return true;
}




bool cGame::RenderGame()
{
     bool IsRendered=true;
     

	// Clear the backbuffer to a black color
	 
         Device->Clear(0,0,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(225,225,225) ,1.0f,0);
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
		  MessageBox(0," BeginScene()-Failed"," Rendering Error",MB_OK) ;
			IsRendered=false;
	  }
	
    // Present the backbuffer contents to the display
	  
       Device->Present(0,0,0,0);
	return IsRendered;
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
 game->CreateGameWindows(hInstance,"Simulation of a Bouncing ball subject to Frictions and  Aerodynamic Drag Force");
 
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
