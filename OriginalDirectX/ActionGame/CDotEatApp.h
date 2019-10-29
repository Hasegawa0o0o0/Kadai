/**
* @file CDotEatApp.h
* @brief �h�b�g�C�[�g�@�A�v��
* @author �D�ˁ@�엲
* @date ���t�i2017.02.14�j
*/
#pragma once

#include "stdafx.h"
#include "CApplication.h"
#include "CMapManager.h"

class CDotEatApp :
	public CApplication
{
	typedef CApplication super;
private:
	std::unique_ptr<CPicture>	m_pOpening		= NULL;
	std::unique_ptr<CPicture>	m_pClear		= NULL;
	std::unique_ptr<CPicture>	m_pOver			= NULL;
	std::unique_ptr<CPicture>	m_pBackground	= NULL;

	std::unique_ptr<CMapManager>	m_pMapManager	= NULL;
	//*****************************************************************
	//�yMethod�z <Private>
	//*****************************************************************
	bool createSprites(void);
	void initCameraInfo();
	void createMap();
	void doOpenning();
	void doPlaying();
	void doGameClear();
	void doGameOver();
	void doEnding();
public:
	CDotEatApp();
	~CDotEatApp();
	void render(XMFLOAT4X4 matView, XMFLOAT4X4 matProj);
	void release();
};