/**
 * @file CDotEatApp.cpp
 * @brief DirectX11���x�[�X�ɂ����A�v���P�[�V�����N���X
 * @author �D�ˁ@�엲
 * @date ���t�i2017.02.14�j
 */

#include "stdafx.h"
#include "CDotEatApp.h"

CDotEatApp::CDotEatApp()
{
}

CDotEatApp::~CDotEatApp()
{
}

/**
 * @fn void CDotEatApp::initCameraInfo()
 * @brief �J�����̐ݒ�
 * @param	����
 * @return	����
 */
void CDotEatApp::initCameraInfo()
{
	const FLOAT x = 32.0f * 5.5;
	const FLOAT y = 32.0f * 4;
	m_vEyePt	= XMFLOAT3{ x, y,  -400.0f };		//!< �J�����i���_�j�ʒu
	m_vLookatPt = XMFLOAT3{ x, y,     0.0f };		//!< �����ʒu
	m_vUpVec	= XMFLOAT3{ 0.0f, 1.0f,     0.0f };	//!< ����ʒu
	m_angle		= (FLOAT)XM_PI / 4;					//!< ����p
	m_aspect	= ASPECT;							//!< �A�X�y�N�g��
	m_near		= 0.1f;								//!< �O���N���b�v
	m_far		= 1000.0f;							//!< ����N���b�v
}

/**
 * @fn bool CDotEatApp::createSprites(void)
 * @brief �X�v���C�g�̐���
 * @param	����
 * @return	�����E���s
 */
bool CDotEatApp::createSprites(void)
{
	super::createSprites(); //!< �X�[�p�[�N���X�̃��\�b�h�����s
	try {
		vector <QuadrangleTexel>  iTexel1_1 = {
			QuadrangleTexel{ { 0, 1.0f },{ 0, 0.0f },{ 1, 1.0f },{ 1, 0.0f } }
		};
		m_pOpening		= CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, Tex_Opening, { 180.0f, 112.0f, 110.0f, 0.0f }, { WINDOW_WIDTH , WINDOW_HEIGHT }, iTexel1_1);
		m_pClear		= CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, Tex_Clear, { 200.0f, 134.0f, 100.0f, 0.0f }, { WINDOW_WIDTH , WINDOW_HEIGHT }, iTexel1_1);
		m_pOver			= CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, Tex_Over, { 226.0f, 106.0f, 110.0f, 0.0f }, { WINDOW_WIDTH , WINDOW_HEIGHT }, iTexel1_1);
		m_pBackground	= CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, Tex_Background, { 180.0f, 112.0f, 110.0f, 0.0f }, { WINDOW_WIDTH , WINDOW_HEIGHT }, iTexel1_1);
		
		createMap();		 //!< Map�𐶐�
		return true;
	}
	catch (LPCWSTR str) {
		MessageBox(0, str, NULL, MB_OK);
		return false;
	}
}

/**
 * @fn void CDotEatApp::createMap()
 * @brief �h�b�g�C�[�g�̃}�b�v���쐻
 * @param	����
 * @return	����
 */
void CDotEatApp::createMap()
{
	/**
	 * �Q�[���̏�����
	 */
	//m_pMapManager = unique_ptr<CMapManager>(new CMapManager());
	//m_pMapManager->init(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL);
	m_pMapManager = CMapManager::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL);
}

/**
 * @fn void CDotEatApp::doOpenning()
 * @brief �I�[�v�j���O
 * @param	����
 * @return	����
 */
void CDotEatApp::doOpenning()
{
	if (m_pDirectInput->isKeyPressed(DIK_X)) {
		m_gameStatus = ePlaying;
	}
}

/**
 * @fn void CDotEatApp::doPlaying()
 * @brief �v���[��
 * @param	����
 * @return	����
 */
void CDotEatApp::doPlaying()
{
	try
	{
		m_frameCounter++;
		m_frameCounter = m_frameCounter > 65536 ? 0 : m_frameCounter;

		eDirection dir = eNone;
		if (m_pDirectInput->isPressedOnce(DIK_LEFT))	dir = eLeft;
		if (m_pDirectInput->isPressedOnce(DIK_RIGHT))	dir = eRight;
		if (m_pDirectInput->isPressedOnce(DIK_UP))		dir = eDown;
		if (m_pDirectInput->isPressedOnce(DIK_DOWN))	dir = eUp;

		//m_pMapManager->update(m_frameCounter, 0, FALSE);

	}// end of try
	catch (eGameStatus status_)
	{
		if (status_ == eGameClear)
		{
			m_gameStatus = eGameClear;
			//MessageBox(0, L"�Q�[���N���A�ł��B", NULL, MB_OK);
		}
		else if (status_ == eGameOver)
		{
			m_gameStatus = eGameOver;
			//MessageBox(0, L"�Q�[���I�[�o�[�ł��B", NULL, MB_OK);
		}
	}//end of catch
}

/**
 * @fn void CDotEatApp::doGameClear()
 * @brief �Q�[���N���A
 * @param	����
 * @return	����
 */

void CDotEatApp::doGameClear()
{
	if (m_pDirectInput->isKeyPressed(DIK_X)) {
		m_gameStatus = ePlaying;
		createMap();
	}
}

/**
 * @fn void CDotEatApp::doGameOver()
 * @brief �Q�[���I�[�o�[
 * @param	����
 * @return	����
 */
void CDotEatApp::doGameOver()
{
	if (m_pDirectInput->isKeyPressed(DIK_X)) {
		m_gameStatus = ePlaying;
		createMap();
	}
}

/**
 * @fn void CDotEatApp::doEnding()
 * @brief �G���f�B���O
 * @param	����
 * @return	����
 */
void CDotEatApp::doEnding()
{
}

/**
 * @fn void CDotEatApp::renderSprite(XMFLOAT4X4 matView_, XMFLOAT4X4 matProj_)
 * @brief �����_�[
 * @param	matView_	�r���[�s��
 * @param	matProj_	�v���W�F�N�V�����s��
 * @return				����
 */
void CDotEatApp::render(XMFLOAT4X4 matView_, XMFLOAT4X4 matProj_)
{
	//switch (m_gameStatus)
	//{
	//case eOpenning:
	//	m_pOpening->render(matView_, matProj_/*,
	//		[&](ID3D11DeviceContext* pDeviceContext_) -> void {
	//		m_pOpeningTex->setup(pDeviceContext_);
	//	}*/);
	//	break;
	//case ePlaying:
	//	m_pMapManager->render(matView_, matProj_);
	//	m_pBackground->render(matView_, matProj_);
	//	break;
	//case eGameClear:
	//	m_pClear->render(matView_, matProj_/*,
	//		[&](ID3D11DeviceContext* pDeviceContext_) -> void {
	//		m_pClearTex->setup(pDeviceContext_);
	//	}*/);
	//	break;
	//case eGameOver:
	//	m_pOver->render(matView_, matProj_/*,
	//		[&](ID3D11DeviceContext* pDeviceContext_) -> void {
	//		m_pOverTex->setup(pDeviceContext_);
	//	}*/);
	//	break;
	//case eEnding:
	//	break;
	//default:
	//	break;
	//}

	/**
	 * �f�o�b�O���
	 */
	//debugString(m_hWnd, 10, 10, L"�X�y�[�X�V�b�v�U");
	OutputDebugString(L"�X�y�[�X�V�b�v�U\n");
}

/**
 * @fn void CDotEatApp::release()
 * @brief ���
 * @param	����
 * @return	����
 */
void CDotEatApp::release()
{
	m_pOver->release();
	m_pClear->release();
	m_pOpening->release();
	m_pMapManager->release();
	super::release();			//!< �X�[�p�[�N���X�̃��\�b�h�����s
}