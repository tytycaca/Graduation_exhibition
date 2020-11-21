////////////////////////////////////////////////////////////////////////////////
// Filename: gameclss.cpp
////////////////////////////////////////////////////////////////////////////////
#include "gameclass.h"

GameClass::GameClass()
{
	m_consCrateNum = 0;
	m_consTentNum = 0;

	m_emeraldCnt = 0;
	m_rubyCnt = 0;
	m_sapphireCnt = 0;
	m_amethystCnt = 0;
	m_diamondCnt = 0;
	m_woodStackCnt = 0;
	m_extractCnt1 = 0;
	m_extractCnt2 = 0;
	m_extractCnt3 = 0;
}


GameClass::GameClass(const GameClass& other)
{

}


GameClass::~GameClass()
{

}


////////////////
// Initialize //
////////////////

bool GameClass::Initialize()
{
	m_sceneType = SceneType::TITLE;
	m_buildType = BuildType::SCFICRATE;

	return true;
}


//////////////////
// GetSceneType //
//////////////////

SceneType GameClass::GetSceneType()
{
	return m_sceneType;
}


//////////////////
// GetBuildType //
//////////////////

BuildType GameClass::GetBuildType()
{
	return m_buildType;
}


//////////////////
// SetSceneType //
//////////////////

void GameClass::SetSceneType(SceneType sceneType)
{
	m_sceneType = sceneType;
}


//////////////////
// SetBuildType //
//////////////////

void GameClass::SetBuildType(BuildType buildType)
{
	m_buildType = buildType;
}


//////////////////
// Get GemCount //
//////////////////

int GameClass::GetEmeralCnt()
{
	return m_emeraldCnt;
}


int GameClass::GetRubyCnt()
{
	return m_rubyCnt;
}


int GameClass::GetSapphCnt()
{
	return m_sapphireCnt;
}


int GameClass::GetAmethCnt()
{
	return m_amethystCnt;
}


int GameClass::GetDiaCnt()
{
	return m_diamondCnt;
}

int GameClass::GetWoodStackCnt()
{
	return m_woodStackCnt;
}


//////////////////
// Set GemCount //
//////////////////

void GameClass::SetEmeralCnt(int cnt)
{
	m_emeraldCnt = cnt;
}


void GameClass::SetRubyCnt(int cnt)
{
	m_rubyCnt = cnt;
}


void GameClass::SetSapphCnt(int cnt)
{
	m_sapphireCnt = cnt;
}


void GameClass::SetAmethCnt(int cnt)
{
	m_amethystCnt = cnt;
}


void GameClass::SetDiaCnt(int cnt)
{
	m_diamondCnt = cnt;
}


void GameClass::SetWoodStackCnt(int cnt)
{
	m_woodStackCnt = cnt;
}


////////////////////
// ConstructCrate //
////////////////////

void GameClass::ConstructCrate()
{
	++m_consCrateNum;

	--m_emeraldCnt;
	--m_rubyCnt;
	--m_sapphireCnt;
	--m_amethystCnt;
}


///////////////////
// DestructCrate //
///////////////////

void GameClass::DestructCrate()
{
	--m_consCrateNum;

	++m_emeraldCnt;
	++m_rubyCnt;
	++m_sapphireCnt;
	++m_amethystCnt;
}


///////////////////
// ConstructTent //
///////////////////

void GameClass::ConstructMarketTent()
{
	++m_consTentNum;

	--m_woodStackCnt;
}


//////////////////
// DestructTent //
//////////////////

void GameClass::DestructTent()
{
	--m_consTentNum;

	++m_woodStackCnt;
}


/////////////////////
// GetConsModelNum //
/////////////////////

int GameClass::GetConsModelNum(int type)
{
	if (type == 1)
		return m_consCrateNum;
	else if (type == 2)
		return m_consTentNum;
}


/////////////////////
// SetConsModelNum //
/////////////////////

void GameClass::SetConsModelNum(int type, int num)
{
	if (type == 1)
		m_consCrateNum = num;
	else if (type == 2)
		m_consTentNum = num;
}


/////////////////////
// AbleToConstruct //
/////////////////////

bool GameClass::AbleToConstruct(int type)
{
	if (type == 1 && GetEmeralCnt() >= 1 && GetRubyCnt() >= 1 && GetSapphCnt() >= 1 && GetAmethCnt() >= 1)
		return true;
	if (type == 2 && m_woodStackCnt > 0)
		return true;

	return false;
}


//////////////
// Increase //
//////////////

void GameClass::IncEmeralCnt()
{
	++m_emeraldCnt;
}

void GameClass::IncRubyCnt()
{
	++m_rubyCnt;
}

void GameClass::IncSapphCnt()
{
	++m_sapphireCnt;
}

void GameClass::IncAmethCnt()
{
	++m_amethystCnt;
}

void GameClass::IncDiaCnt()
{
	++m_diamondCnt;
}

void GameClass::IncWoodStackCnt()
{
	++m_woodStackCnt;
}

void GameClass::IncExtractCnt(int type)
{
	if (type == 1)
		++m_extractCnt1;
	if (type == 1)
		++m_extractCnt2;
	if (type == 1)
		++m_extractCnt3;

}


//////////////
// Decrease //
//////////////

void GameClass::DecEmeralCnt()
{
	--m_emeraldCnt;
}

void GameClass::DecRubyCnt()
{
	--m_rubyCnt;
}

void GameClass::DecSapphCnt()
{
	--m_sapphireCnt;
}

void GameClass::DecAmethCnt()
{
	--m_amethystCnt;
}

void GameClass::DecDiaCnt()
{
	--m_diamondCnt;
}

void GameClass::DecWoodStackCnt()
{
	--m_woodStackCnt;
}