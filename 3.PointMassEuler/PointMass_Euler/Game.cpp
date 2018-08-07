  
#include"Game.h"
#include"Game3DModel.h"

 static cGame* game;


 


RigidBody ball1,ball2;

/********************************************************************************************************************
Author  : Richard Bahin
Function: cGame()                                                                                   
Input   : none  																									
Output  : none																											
Returns : none                                                                                                         
comment : cGame class constructor                                                                                                        
TODO    : None 																											
*********************************************************************************************************************/
cGame::cGame():cGameWindows()
{
   
 
}


/********************************************************************************************************************
Author  : Richard Bahin
Function: ~cGame()                                                                                   
Input   : none  																									
Output  : none																											
Returns : none                                                                                                         
comment : cGame class destructor                                                                                                        
TODO    : None 																											
*********************************************************************************************************************/
cGame::~cGame()
{
  

}

/********************************************************************************************************************
Author  : Richard Bahin
Function: SetupMatrices()                                                                                   
Input   : none  																									
Output  : none																											
Returns : boolean(true)                                                                                                         
comment : to setup the view and projection matrices                                                                                                        
TODO    : None 																											
*********************************************************************************************************************/
bool SetupMatrices()
{
   
	D3DXVECTOR3 position(1.0f,4.0f,-10.0f);
	D3DXVECTOR3 target(0.0f,0.0f,0.0f);
	D3DXVECTOR3 up(0.0f,1.0f,0.0f);
	D3DXMatrixLookAtLH(&game->viewMatrix,&position,&target,&up);
	Device->SetTransform(D3DTS_VIEW,&game->viewMatrix);
	D3DXMatrixPerspectiveFovLH(&game->projectionMatrix,D3DX_PI/2.0f ,(float)WIDTH /(float)HEIGHT ,1.0f,10000.0f);
	Device->SetTransform(D3DTS_PROJECTION,&game->projectionMatrix);
	return true;
}



/********************************************************************************************************************
Author  : Richard Bahin
Function: InitializeGame()                                                                                      
Input   : none																										
Output  : none																											
Returns : boolean , true if success                                                                                                          
comment : this function will initialze the game lights , world matrix and objects physical attributes such as mass ,velocity,force....                                                                                                         
TODO    : To initialize the rigid bodies physical attributes(mass ,velocity,orientation,acceleration,force,torque, ......)																											
**********************************************************************************************************************/			
bool cGame::InitializeGame()
{
    // Iniatialize lights
	InitializeLight();
	// Initialize world and view  matrices
	SetupMatrices();
	 
     Vector3D gravity; // vector gravity 
   
   //  initialize the vector gravity.REMEMBER its magnitude is 9.81 m/s2
	 gravity = Vector3D(0, 9.81, 0);
	 // load ball one (ball1) calling Load() , the mesh filename is "bowlball.x" and the  device is Device;
	 ball1.Load("bowlball.x", Device);
	// set its mass=10kg 
	 ball1.mass = 10.0f;
	// set its initial position at location (5,1,3).that is also the loocation of the center of mass;
	 ball1.position = Vector3D(5.0f, 1.0f, 3.0f);
	// set its initial velocity to (0,0,0) m/s
	 ball1.velocity = Vector3D(0.0f, 0.0f, 0.0f);
	// calculate ball1 weight
	 ball1.weight = -(ball1.mass * gravity);

	     
	//do the same thing for ball two
	 // load ball two (ball2) calling Load() , the mesh filename is "bowlball.x" and the  device is Device;
	 ball2.Load("bowlball.x", Device);
   // set its mass=0.15kg
	 ball2.mass = 15.0f;
	//set its initial position at location (-2,5,1).that is also the loocation of the center of mass;
	 ball1.position = Vector3D(-2.0f, 5.0f, 1.0f);
	 //set its initial velocity to (0,0,0) m/s
	 ball2.velocity = Vector3D(0.0f, 0.0f, 0.0f);
	//compute  ball 2 weight .
	 ball2.weight = -(ball2.mass * gravity);
	
	return true;
}



/********************************************************************************************************************
Author  : Richard Bahin
Function: ShutDownD3D()                                                                                  
Input   : none  																									
Output  : none																											
Returns : bolean (true)                                                                                                     
comment : The function will shutdown Drect3D                                                                                                       
TODO    : None 																											
*********************************************************************************************************************/
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


/********************************************************************************************************************
Author  : Richard Bahin
Function: UpdateGame()                                                                                      
Input   : time step dt   																										
Output  : none																											
Returns : void                                                                                                          
comment : this function will update the game                                                                                                           
TODO    : see handouts																											
*********************************************************************************************************************/				
void cGame::UpdateGame(float dt)
{
      
static bool forceApplied=false;


	   if(!forceApplied) // if outer forces have been applied yet
	   {      // remember the outer will be applied once in the simulation


           // set the outer  force on ball one to Force(5,0,0)Newtons
		   ball1.force = Vector3D(5.0f, 0.0f, 0.0f);

		   // set the outer  force on ball two to Force(1,0,1)Newtons
		   ball2.force = Vector3D(1.0f, 0.0f, 1.0f);
		   
		   // force has been applied ,so set forceApplied to TRUE;        

		   forceApplied = true;
		}

	   else
	   {
		   // if the outer force have been applied reset them to zero vector for each ball.

             // set ball1 force to Zero vector
		   ball1.force = Vector3D(0.0f, 0.0f, 0.0f);

		     // set ball2 force to Zero vector
		   ball2.force = Vector3D(0.0f, 0.0f, 0.0f);

	   }

	   // update ball one by calling Update(dt), where dt=time step or delta t*/
	ball1.Update(dt);

	   // update ball two by calling Update(dt), dt=time step or delta t*/
	ball2.Update(dt);
	 
}


/********************************************************************************************************************
Author  : Richard Bahin
Function: RenderFrame()                                                                                   
Input   : none  																									
Output  : none																											
Returns : boolean (true)                                                                                                         
comment : This function will render the objects involved in the simulation                                                                                                     
TODO    : None 																											
*********************************************************************************************************************/
bool RenderFrame()
{
    // render ball one by calling Render() function  with input value Device 
	ball1.Render(Device);
	// render ball two by calling Render() function  with input value Device
	ball2.Render(Device);

	return true;
}



/********************************************************************************************************************
Author  : Richard Bahin
Function: RenderGame()                                                                                   
Input   : none  																									
Output  : none																											
Returns : boolean (true)                                                                                                         
comment : This function will render the game frame                                                                                                    
TODO    : None 																											
*********************************************************************************************************************/
bool cGame::RenderGame()
{
     bool IsRendered=true;
     

	// Clear the backbuffer 
	 
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


/********************************************************************************************************************
Author  : Richard Bahin
Function: Cleanup()                                                                                   
Input   : none  																									
Output  : none																											
Returns : none (void)                                                                                                         
comment : not implemented for now                                                                                                    
TODO    : None 																											
*********************************************************************************************************************/
void cGame::Cleanup()
{
   
	
}


/********************************************************************************************************************
Author  : Richard Bahin
Function: InitializeLight()                                                                                   
Input   : none  																									
Output  : none																											
Returns : boolean (true)                                                                                                         
comment : This function will initialize the game lights                                                                                                    
TODO    : None 																											
*********************************************************************************************************************/
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


/********************************************************************************************************************
Author  : Richard Bahin
Function: WinMain()                                                                                   
Input   : none  																									
Output  : none																											
Returns : boolean (true)                                                                                                         
comment : The main Window function                                                                                                    
TODO    : None 																											
*********************************************************************************************************************/
INT WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInst,LPSTR lpCmdLine, int nShowCmd)
{
  
 game=new cGame();
  /* Create window */
 game->CreateGameWindows(hInstance,"y  Euler Method simulation, Lab1 ");
 
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


/********************************************************************************************************************
Author  : Richard Bahin
Function: InitializeD3D()                                                                                   
Input   : none  																									
Output  : none																											
Returns : boolean                                                                                                        
comment : This function will initialize Direct3D                                                                                                   
TODO    : None 																											
*********************************************************************************************************************/
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

    }

	     // Turn on the zbuffer
    Device->SetRenderState( D3DRS_ZENABLE, TRUE );

    // Turn on ambient lighting 
    Device->SetRenderState( D3DRS_AMBIENT, 0xffffffff );
  return hr;
}

