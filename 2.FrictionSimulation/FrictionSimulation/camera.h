
#ifndef _CAMERA_H
#define _CAMERA_H

#include"commonFile.h"
#include"game.h"

class Camera
{

private:

	 D3DXVECTOR3 up; // the up vector in camera orientation
	 D3DXVECTOR3 side; // the side vector in camera orientation
	 D3DXVECTOR3 look;// the look vector in camera orientation
	 D3DXVECTOR3 position;// camera position
	 D3DXVECTOR3 velocity; // camera constant linear velocity
	 D3DXMATRIX  viewMatrix; // view matrix to be computed
	 D3DXMATRIX  orientation; // camera orientation to be computed
	 D3DXMATRIX  rotation;    // camera rotation matrix 
     bool isOnLand; // is the camera on land or in airspace ?
	 float angle; // angle of rotation
	
public:

	Camera();
	~Camera(){};

    void Walk(float dt);
    void WalkBack(float dt);
	void WalkRight(float dt);
	void WalkLeft(float dt);
	


	void TakeOff(float dt);
    void Fly(float dt);
	void Land(float dt);

    void Yaw(float angle);
	void Pitch(float angle);
	void Roll(float angle);
	void YawBack(float angle);
	void PitchBack(float angle);
	void RollBack(float angle);

	D3DXMATRIX GetViewMatrix();
	void       SetViewMatrix();
    D3DXVECTOR3 GetPosition();
	void        SetPosition(float x, float y, float z);
	D3DXVECTOR3 GetVelocity();
	void        SetVelocity(float x,float y,float z);
	void        Update(float dt); // to update camera position and orientation


};
#endif
