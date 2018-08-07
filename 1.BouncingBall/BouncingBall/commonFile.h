
#ifndef _COMMONFILE_H
#define _COMMONFILE_H

#include<d3dx9.h>
#include<limits.h>
#include"Physics.h"
#include"Game.h"
#include"MathLib.h"
#include"GameWindows.h"
#include"Plane.h"



#if !defined(SAFE_RELEASE)
    #define SAFE_RELEASE(x) if(x) x->Release(); x=NULL;
#endif

#if !defined(SAFE_DELETE)
    #define SAFE_DELETE(X) if(x) delete x; x=NULL;
#endif

#if !defined(SAFE_DELETE_ARRAY)
    #define SAFE_DELETE_ARRAY(x) if(x) delete[] x ; x=NULL;
#endif

#define INFINITY FLT_MAX
 
const D3DXCOLOR   WHITE=D3DXCOLOR(225,225,225,225);
const D3DXCOLOR   BLACK=D3DXCOLOR(0,0,0,225);
const D3DXCOLOR   BLUE =D3DXCOLOR(0,0,225,225);
const D3DXCOLOR   GREEN=D3DXCOLOR(0,225,0,225);
const D3DXCOLOR   RED  =D3DXCOLOR(225,0,0,225);
D3DMATERIAL9 CreateMaterial(D3DXCOLOR ambientColor, D3DXCOLOR diffuseColor,D3DXCOLOR specularColor ,D3DXCOLOR emissiveColor, float p);

const D3DMATERIAL9 WHITEMATERIAL=CreateMaterial(WHITE,WHITE,WHITE,BLACK,1.0f);
const D3DMATERIAL9 BLACKMATERIAL=CreateMaterial(BLACK,BLACK,BLACK,BLACK,1.0f);
const D3DMATERIAL9 GREENMATERIAL=CreateMaterial(GREEN,GREEN,GREEN,BLACK,1.0f);
const D3DMATERIAL9 BLUEMATERIAL=CreateMaterial(BLUE,BLUE,BLUE,BLACK,1.0f);
const D3DMATERIAL9 REDMATERIAL =CreateMaterial(RED,RED,RED,BLACK,1.0f);

 
#endif;

