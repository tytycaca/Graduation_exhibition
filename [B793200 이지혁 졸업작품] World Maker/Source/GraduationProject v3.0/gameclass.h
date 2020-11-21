////////////////////////////////////////////////////////////////////////////////
// Filename: gameclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GAMECLASS_H_
#define _GAMECLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3dx10math.h>
#include "timerclass.h"
#include "soundclass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name : SceneType
////////////////////////////////////////////////////////////////////////////////

enum class SceneType
{
	TITLE, CONTROLS, MAIN1, MAIN2, ENDING
};


////////////////////////////////////////////////////////////////////////////////
// Class name : SceneType
////////////////////////////////////////////////////////////////////////////////

enum class BuildType
{
	SCFICRATE, ENERGYCELL, MARKETTENT, MARKETTENTADVENCED
};


////////////////////////////////////////////////////////////////////////////////
// Class name: GameClss
////////////////////////////////////////////////////////////////////////////////
class GameClass
{
public:
	GameClass();
	GameClass(const GameClass&);
	~GameClass();

	bool Initialize();

	SceneType GetSceneType();
	void SetSceneType(SceneType);

	BuildType GetBuildType();
	void SetBuildType(BuildType);

	int GetEmeralCnt();
	int GetRubyCnt();
	int GetSapphCnt();
	int GetAmethCnt();
	int GetDiaCnt();
	int GetWoodStackCnt();

	void SetEmeralCnt(int);
	void SetRubyCnt(int);
	void SetSapphCnt(int);
	void SetAmethCnt(int);
	void SetDiaCnt(int);
	void SetWoodStackCnt(int);

	void IncEmeralCnt();
	void IncRubyCnt();
	void IncSapphCnt();
	void IncAmethCnt();
	void IncDiaCnt();
	void IncWoodStackCnt();
	void IncExtractCnt(int);

	void DecEmeralCnt();
	void DecRubyCnt();
	void DecSapphCnt();
	void DecAmethCnt();
	void DecDiaCnt();
	void DecWoodStackCnt();

	void ConstructCrate();
	void DestructCrate();

	void ConstructMarketTent();
	void DestructTent();

	int GetConsModelNum(int);
	void SetConsModelNum(int, int);

	bool AbleToConstruct(int);

private:
	int m_consCrateNum;
	int m_consTentNum;

	int m_sapphireCnt;
	int m_emeraldCnt;
	int m_diamondCnt;
	int m_amethystCnt;
	int m_rubyCnt;
	int m_woodStackCnt;
	int m_extractCnt1;
	int m_extractCnt2;
	int m_extractCnt3;

	bool m_isGameCleared;
	SceneType m_sceneType;
	BuildType m_buildType;
};

#endif