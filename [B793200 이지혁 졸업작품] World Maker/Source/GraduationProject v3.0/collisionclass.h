#pragma once
#pragma comment (lib, "DXGI.lib")
#pragma comment (lib, "D2D1.lib")
#pragma comment (lib, "dwrite.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <xnamath.h>
#include <D3D10_1.h>
#include <DXGI.h>
#include <D2D1.h>
#include <sstream>
#include <dwrite.h>
#include <dinput.h>
///////////////**************new**************////////////////////
#include <vector>
///////////////**************new**************////////////////////

class CollisionClass
{
public:
	// BoundingVolume�� ����� �Լ�
	static void CreateBoundingVolumes(std::vector<XMFLOAT3> &vertPosArray,
		std::vector<XMFLOAT3> &boundingBoxVerts,
		std::vector<DWORD> &boundingBoxIndex,
		float &boundingSphere,
		XMVECTOR &objectCenterOffset);

	// AABB�� ����� �Լ�
	static void CalculateAABB(std::vector<XMFLOAT3> boundingBoxVerts,
		XMMATRIX& worldSpace,
		XMVECTOR& boundingBoxMin,
		XMVECTOR& boundingBoxMax);

	// ���� Collision üũ
	static bool BoundingSphereCollision(const float firstObjBoundingSphere,
		const XMVECTOR firstObjCenterOffset,
		const XMMATRIX& firstObjWorldSpace,
		const float secondObjBoundingSphere,
		const XMVECTOR secondObjCenterOffset,
		const XMMATRIX& secondObjWorldSpace);

	// �ڽ��� Collision üũ
	static bool BoundingBoxCollision(const XMVECTOR& firstObjBoundingBoxMinVertex,
		const XMVECTOR& firstObjBoundingBoxMaxVertex,
		const XMVECTOR& secondObjBoundingBoxMinVertex,
		const XMVECTOR& secondObjBoundingBoxMaxVertex,
		bool);
};