////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_

#include <vector>

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "define.h"
#include "d3dclass.h"
#include "shadermanagerclass.h"
#include "cameraclass.h"
#include "lightclass.h"
#include "pointlightclass.h"
#include "modelclass.h"
#include "bumpmodelclass.h"
#include "inputclass.h"
#include "textclass.h"

#include "skyboxclass.h"
#include "raycastingclass.h"
#include "md5modelclass.h"

#include "bitmapclass.h"
#include "bitmapshaderclass.h"

#include "soundclass.h"

#include "gameclass.h"


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 100000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(HWND, int, int, int, int, int, int, float, DIMOUSESTATE, bool, bool, bool, bool, bool, bool, bool, bool, bool);

	void MoveCameraAndChar(int);
	void RotateCameraAndChar(float, float, float);
	void MovePad(int, float);
	void MovePadAI(float);

	void AnimCharWalk(float);
	void AnimCharConstruct(float);

private:
	bool Render(float, DIMOUSESTATE, float, bool, bool);
	void Main2CollisionControl(int);

private:
	vector<D3DXVECTOR3> insPos;
	vector<float> insRot;

	D3DClass* m_D3D;
	ShaderManagerClass* m_ShaderManager;
	CameraClass* m_Camera;
	LightClass* m_Light[LIGHTNUM];
	ModelClass* m_Model[MAXMODELNUM];
	PointLightClass *m_PointLight0;

	TextClass* m_Text;

	SkyboxClass* m_Skybox;

	RaycastingClass* m_Raycast;

	Md5ModelClass* m_Md5Model;

	BitmapShaderClass* m_BitmapShader;

	BitmapClass* m_Bitmap[BITMAPNUM];

	SoundClass* m_Sound;

	GameClass* m_Game;

	float m_movement;
	float m_AImovement;
	int plusMinus;

	HWND m_hwnd;

	int m_obj, m_poly;
	bool checkFirst;

	bool isLClicked, isRClicked;
	bool isEnterOn;
	bool isF5On;

	D3DXVECTOR3 m_charPos;
	D3DXVECTOR3 m_charRot;

	D3DXMATRIX m_BaseViewMatrix;

	float m_animTimeStack;
	bool m_constructAnimTrigger;

	bool m_isLootModelRender[LOOTINGMODELNUM];

	bool tfI;
	bool isIOn;

	bool tfE;
	bool isEOn;

	bool cactusCollision1;
	bool cactusCollision2;
	bool cactusCollision3;

	bool palmTreeExTF1;
	bool palmTreeExTF2;
	bool palmTreeExTF3;

	bool woodStackTF1;
	bool woodStackTF2;
	bool woodStackTF3;
	
//public:
//	float m_oldCamRot;
};

#endif