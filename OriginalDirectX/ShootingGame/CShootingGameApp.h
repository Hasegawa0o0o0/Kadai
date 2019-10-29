/**
* @file CShootingGameApp.h
* @brief �X�y�[�X�V�b�v�i���ۃN���X�j
* @author �D�ˁ@�엲
* @date ���t�i2017.02.14�j
*/
#pragma once

#include "stdafx.h"
#include "CApplication.h"
#include "CScroll.h"
#include "CPlayer.h"
#include "CEnemy.h"

class CShootingGameApp :
	public CApplication
{
	typedef CApplication super;
private:
	//*****************************************************************
	//�yMethod�z <Private>
	//*****************************************************************
	std::unique_ptr<CPicture>	m_pTitle			= NULL;
	std::unique_ptr<CPicture>	m_pGameOver	= NULL;
	std::unique_ptr<CScroll>	m_pBack		= NULL;
	std::unique_ptr<CScroll>	m_pMiddle		= NULL;
	std::unique_ptr<CScroll>	m_pFront		= NULL;
	std::unique_ptr<CPlayer>	m_pPlayer		= NULL;	//!< �y�X�e�b�v6�zCSpaceship
	std::shared_ptr<CEnemy>	m_pEnemys[5]	= { };	//!< �S�Ă̗v�f���[���ɂ��鏑����

	std::unique_ptr<CTexture>		m_pPlayerTex	= NULL;	//!< �e�N�X�`��
	std::shared_ptr<CTexture>	m_pEnemyTex	= NULL;	//!< �e�N�X�`��
	int m_activeEnemys										= 0;

	bool createSprites(void);
	bool createSpaceship(void);
	void initCameraInfo();
	void prepareFrame (shared_ptr<CEnemy> pEnemy_, int i);
	void doOpenning();
	void doPlaying();
	void doGameClear();
	void doGameOver();
	void doEnding();
	BOOL isActiveEnemys();
public:
	CShootingGameApp();
	~CShootingGameApp();
	void enumEnemys(std::function<BOOL(std::shared_ptr<CEnemy>, size_t)> callbackEnumeProc_);
	void render(XMFLOAT4X4 matView, XMFLOAT4X4 matProj);
	void release();
};