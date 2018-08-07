
#include"camera.h"



Camera::Camera()
{
	// set camera position at (0,2,-30)
	position=D3DXVECTOR3(0,2,-20); 
	// set camera look vector at (0,0,1)
	look    =D3DXVECTOR3(0,0,1);
	// set camera up vector at (0,1,0)
	up      =D3DXVECTOR3(0,1,0);
	// set camera side vector at (1,0,0)
	side    =D3DXVECTOR3(1,0,0);
	// set camera constant velocity to (50,50,50) m/s
	velocity=D3DXVECTOR3(50,50,50);
	// initialize camera orientation by calling D3DXMatrixIdentity
	D3DXMatrixIdentity(&orientation);
	isOnLand=true;
}

void Camera::Walk(float dt)
{
	if(isOnLand)
	{  
		// update the z component of camera position 
		// with the z component of the velocity
		position.z= position.z + velocity.z*dt;
	}
}

void Camera::WalkBack(float dt)
{
	if(isOnLand)
	{ 
	  // update the z component of camera position backward
	  // with the z component of the velocity
	  position.z= position.z - velocity.z*dt;
	}
}

void Camera::WalkRight(float dt)
{
	if(isOnLand)
	{ 
	// update the x component of camera position 
	// //with the x component of the velocity
	  position.x= position.x + velocity.x*dt;
	}
}

void Camera::WalkLeft(float dt)
{
	if(isOnLand)
	{
	    // update the x component of camera position  backward
		// with the x component of the velocity
		position.x= position.x - velocity.x*dt;

	}
}



void Camera::Yaw(float angle)
{
	D3DXMATRIX mat;
	
	if(isOnLand)
	{
		// rotate camera angle degree about the Y-Axis
		D3DXMatrixRotationY(&mat,angle);
	}
	else
	{
		// if not on land then it could rotate an angle degree on any arbitrary axis 
		// that still your camera up vector. 
		D3DXMatrixRotationAxis(&mat,&up,angle);
	}
    // now 
	//calculate the new look vector after the rotation defined by the matrix mat
	D3DXVec3TransformCoord(&look,&look,&mat);
	//calculate the new side vector after the rotation defined by the matrix mat
	D3DXVec3TransformCoord(&side,&side,&mat);

}

void Camera::YawBack(float angle)
{
	Yaw(-angle);
}


void Camera::Pitch(float angle)
{
	D3DXMATRIX mat;
	
	if(!isOnLand)
	{
	  // build the rotation about the axis spanned by side vector
	  D3DXMatrixRotationAxis(&mat,&side,angle);
	  // rotate the up vectors by the previous rotation matrix
	  D3DXVec3TransformCoord(&up,&up,&mat);
	  // rotate the look vectors by the previous rotation matrix
	  D3DXVec3TransformCoord(&look,&look,&mat);
	}
}


void Camera::PitchBack(float angle)
{
	Pitch(-angle);
}


void Camera::Roll(float angle)
{
	D3DXMATRIX mat;

	if(!isOnLand)
	{
      // build the rotation about the axis spanned by look vector
	    D3DXMatrixRotationAxis(&mat,&look,angle);
   	  // rotate the up  vectors by the previous rotation matrix
		D3DXVec3TransformCoord(&up,&up,&mat);
	  // rotate the side vectors by the previous rotation matrix
		D3DXVec3TransformCoord(&side,&side,&mat);
	}
}


void Camera::RollBack(float angle)
{
	Roll(-angle);
}


void Camera::Fly(float dt)
{
	if(!isOnLand)
	{
		// if in air update z component of the camera position
		//with the z component of the velocity
		position.z= position.z + velocity.z*dt;
	}
}

void Camera::TakeOff(float dt)
{
	// update the y component of the camera position 
	//with the y component of the velocity
	position.y= position.y + velocity.y*dt;
	
	// if the position.y>=0 then isOnLand is set to false.we are flyiiiiiiiiiing
	if(position.y>=0.0f) isOnLand=false;
}

void Camera::Land(float dt)
{
	if(!isOnLand)
	{
	  // if in air decrease the y component of the position
	  // with the y component of the velocity
      position.y= position.y - velocity.y*dt;
	}
	  // positionY<=0 clamp to 0 to prevent camera from penetrating the ground
	  // and set isOnLand true
	 if(position.y<=2.0f)  
	 {
		 position.y=2.0f;
		 isOnLand=true;
	 }
}

void Camera::SetPosition(float x,float y,float z)
{
	position=D3DXVECTOR3(position.x,position.y,position.z);
}

D3DXVECTOR3 Camera::GetPosition()
{
	return position;
}


void Camera::SetVelocity(float x,float y , float z)
{
	velocity=D3DXVECTOR3(x,y,z);
}

D3DXVECTOR3 Camera::GetVelocity()
{
	return velocity;
}


D3DXMATRIX Camera::GetViewMatrix()
{
	return viewMatrix;
}


void Camera::SetViewMatrix()
{
  D3DXMATRIX translate;

  // normalize the look vector
  D3DXVec3Normalize(&look,&look);
  // use Gram-Schmidt 2nd step to calculate the up vector
  up=up - D3DXVec3Dot(&look,&up)*look;
  // then normalize the up
  D3DXVec3Normalize(&up,&up);
  // compute the side vector, side=(up)X(look)
  D3DXVec3Cross(&side,&up,&look);

  // build  the camera oientation matrix( 4x4) with first the components
  // of side , up and then look in column major
  orientation=D3DXMATRIX(side.x ,up.x , look.x , 0  ,
	                     side.y ,up.y , look.y , 0  ,
						 side.z ,up.z , look.z , 0  ,
						   0    ,  0  ,  0     , 1.0f
						 );
  D3DXMatrixTranspose(&rotation,&orientation);

  // compute the translation matrix with the components of vector position.
  // the name of the matrix is translate.
  D3DXMatrixTranslation(&translate,-position.x, -position.y, -position.z);
  // finally compute the view matrix by concatenate the 2 matrices
  // in the following order translation(translate), then rotation(orientation)
  viewMatrix= translate*rotation;
  
}


  
void Camera::Update(float dt)
{
	D3DXMATRIX M;
	if((GetAsyncKeyState(VK_UP) & 0x8000f))   Walk(dt);
	if(GetAsyncKeyState(VK_DOWN) & 0x8000f)   WalkBack(dt);
	if(GetAsyncKeyState(VK_RIGHT)& 0x8000f)   WalkRight(dt);
	if(GetAsyncKeyState(VK_LEFT) & 0x8000f)   WalkLeft(dt);
	if(GetAsyncKeyState('T')     & 0x8000f)   TakeOff(dt);
	if(GetAsyncKeyState('L')     & 0x8000f)   Land(dt);
	if(GetAsyncKeyState('F')     & 0x8000f)   Fly(dt);
	if(GetAsyncKeyState('Y')     & 0x8000f)   Yaw(dt);
	if(GetAsyncKeyState('U')     & 0x8000f)   YawBack(dt);
	if(GetAsyncKeyState('E')     & 0x8000f)   RollBack(dt);
	if(GetAsyncKeyState('O')     & 0x8000f)   PitchBack(dt);
    if(GetAsyncKeyState('R')     & 0x8000f)   Roll(dt);
	if(GetAsyncKeyState('P')     & 0x8000f)   Pitch(dt);

	SetViewMatrix();
}


 




