
#include "commonFile.h"


D3DMATERIAL9 CreateMaterial(D3DXCOLOR ambientColor, D3DXCOLOR diffuseColor,D3DXCOLOR specularColor ,D3DXCOLOR emissiveColor, float p)
{
	D3DMATERIAL9 mtrl;
	mtrl.Ambient=ambientColor;
	mtrl.Diffuse=diffuseColor;
	mtrl.Emissive=emissiveColor;
	mtrl.Specular=specularColor;
	mtrl.Power   =p;
	return mtrl;
}