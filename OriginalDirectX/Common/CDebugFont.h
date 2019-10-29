/**
* @file CDebugFont.h
* @brief �t�H���g
* @author �D�ˁ@�엲
* @date ���t�i2017.12.18�j
*/
#pragma once
#include "CQuadPolygon.h"	//"CSprite.h"
#include "DotEat.h"

class CDebugFont// :
	//public CSprite
{
	//typedef CSprite super;
private:
	std::vector<std::unique_ptr<CQuadPolygon>> m_text;
public:
	CDebugFont();
	~CDebugFont();
	QuadrangleTexel createSprites(char s);
	void createSprites(char s[]);
};

