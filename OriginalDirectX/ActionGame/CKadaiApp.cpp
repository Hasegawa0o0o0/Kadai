/*
 * CBounceBallApp.cpp
 * アプリケーションクラス
 * 17CU0126 長谷川勇太
 * 20181106
*/

#include "stdafx.h"
#include "CKadaiApp.h"

CKadaiApp::CKadaiApp() {}
CKadaiApp::~CKadaiApp() {}

/**
* @fn void CDotEatApp::initCameraInfo()
* @brief カメラの設定
* @param	無し
* @return	無し
*/
void CKadaiApp::initCameraInfo()
{
	const FLOAT x = 32.0f * 8;
	const FLOAT y = 32.0f * 6;
	m_vEyePt = XMFLOAT3{ x, y,  -500.0f };		//!< カメラ（視点）位置
	m_vLookatPt = XMFLOAT3{ x, y,     0.0f };		//!< 注視位置
	m_vUpVec = XMFLOAT3{ 0.0f, 1.0f,     0.0f };	//!< 上方位置
	m_angle = (FLOAT)XM_PI / 4;					//!< 視野角
	m_aspect = ASPECT;							//!< アスペクト比
	m_near = 0.1f;								//!< 前方クリップ
	m_far = 1000.0f;							//!< 後方クリップ
}

// テクスチャの作成
void CKadaiApp::createTexture()
{
	if (m_pvTexture.size() != 0)
	{
		vector<shared_ptr<CTexture>>::iterator itr = m_pvTexture.end() - 1;
		for (; itr != m_pvTexture.begin(); --itr)
		{
			(*itr)->release();
		}
		(*itr)->release();
		m_pvTexture.clear();
	}
	m_pvTexture.push_back(CTexture::create(m_pDevice, Tex_Opening));
	m_pvTexture.push_back(CTexture::create(m_pDevice, Tex_Clear));
	m_pvTexture.push_back(CTexture::create(m_pDevice, Tex_Over));
	m_pvTexture.push_back(CTexture::create(m_pDevice, Tex_Background));
	m_pvTexture.push_back(CTexture::create(m_pDevice, Tex_KadaiPlayer));
	m_pvTexture.push_back(CTexture::create(m_pDevice, Tex_Block));
	m_pvTexture.push_back(CTexture::create(m_pDevice, Tex_Dot));
	m_pvTexture.push_back(CTexture::create(m_pDevice, Tex_Font));
	m_pvTexture.push_back(CTexture::create(m_pDevice, Tex_Enemy));
	m_pvTexture.push_back(CTexture::create(m_pDevice, Tex_Dark));
	m_pvTexture.push_back(CTexture::create(m_pDevice, Tex_Goal));
	m_pvTexture.push_back(CTexture::create(m_pDevice, Tex_Footprint));
}

/**
* @fn bool CDotEatApp::createSprites(void)
* @brief スプライトの生成
* @param	無し
* @return	成功・失敗
*/
bool CKadaiApp::createSprites(void)
{
	super::createSprites(); //!< スーパークラスのメソッドを実行
	try {
		createTexture();
		vector <QuadrangleTexel>  iTexel1_1 = {
			QuadrangleTexel{ { 0, 1.0f },{ 0, 0.0f },{ 1, 1.0f },{ 1, 0.0f } }
		};
		m_pOpening = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, Tex_Opening, { 180.0f, 112.0f, 110.0f, 0.0f }, { WINDOW_WIDTH , WINDOW_HEIGHT }, iTexel1_1);
		m_pClear = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, Tex_Clear, { 200.0f, 134.0f, 100.0f, 0.0f }, { WINDOW_WIDTH , WINDOW_HEIGHT }, iTexel1_1);
		m_pGameOver = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, Tex_Over, { 226.0f, 106.0f, 110.0f, 0.0f }, { WINDOW_WIDTH , WINDOW_HEIGHT }, iTexel1_1);
		m_pBackground = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, Tex_Background, { 32.0f * 8.0f, 32.0f * 6.0f, 85.0f, 0.0f }, { WINDOW_WIDTH , WINDOW_HEIGHT }, iTexel1_1);

		createMap();		 //!< Mapを生成
		return true;
	}
	catch (LPCWSTR str) {
		MessageBox(0, str, NULL, MB_OK);
		return false;
	}
}

/**
* @fn void CDotEatApp::createMap()
* @brief ドットイートのマップを作製
* @param	無し
* @return	無し
*/
void CKadaiApp::createMap()
{
	/**
	* ゲームの初期化
	*/
	m_pMapManager = CMapManager::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL);
}

void CKadaiApp::doOpenning()
{
	m_gameStatus = ePlaying;
}

void CKadaiApp::doPlaying()
{
	++m_frameCounter;
	try
	{
		int inputX = 0;
		int inputY = 0;
		if (m_pDirectInput->isKeyPressed(DIK_LEFT))		inputX -= 1;
		if (m_pDirectInput->isKeyPressed(DIK_RIGHT))	inputX += 1;
		if (m_pDirectInput->isKeyPressed(DIK_UP))		inputY += 1;
		if (m_pDirectInput->isKeyPressed(DIK_DOWN))		inputY -= 1;

		m_pMapManager->update(m_frameCounter, inputX, inputY, m_pDirectInput->isPressedOnce(DIK_SPACE));
	}
	catch (eGameStatus status_)
	{
		m_gameStatus = status_;
	}
}

void CKadaiApp::doGameClear()
{
	if ((int)m_pvText.size() == 0)
	{
		m_pvText.push_back(CText::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, Tex_Font,
			{ 32.0f * 5.0f, 32.0f * 9.0f, 0.0 , 0.0f }, { 64.0f, 128.0f }, gTextTexel, "GOAL"));
		m_pvText.push_back(CText::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, Tex_Font,
			{ 32.0f * 3.0f, 32.0f * 5.0f, 0.0 , 0.0f }, { 24.0f, 48.0f }, gTextTexel, "ClearTime "));
		m_pvText.push_back(CText::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, Tex_Font,
			{ 32.0f * 11.0f, 32.0f * 5.0f, 0.0 , 0.0f }, { 24.0f, 48.0f }, gTextTexel, "00"));
		m_pvText[2]->resetTest();
		m_pvText[2]->setText(m_frameCounter / 60);
		m_pvText.push_back(CText::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, Tex_Font,
			{ 32.0f * 1.75f, 32.0f * 3.0f, 0.0 , 0.0f }, { 24.0f, 48.0f }, gTextTexel, "Restart To Press X"));
	}
	if (m_pDirectInput->isPressedOnce(DIK_X))
	{
		m_gameStatus = ePlaying;
		for (int i = 0; i < (int)m_pvText.size(); ++i)
			m_pvText[i]->clearText();
		m_pvText.clear();
		m_pvText.push_back(CText::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, Tex_Font,
			{ 32.0f * 8.0f, 32.0f * 6.0f, 0.0 , 0.0f }, { 64.0f, 128.0f }, gTextTexel, "00000"));
		createMap();
		m_frameCounter = 0;
	}
}

void CKadaiApp::doGameOver()
{
	if ((int)m_pvText.size() == 0)
	{
		m_pvText.push_back(CText::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, Tex_Font,
			{ 32.0f * 2.0f, 32.0f * 7.0f, 0.0 , 0.0f }, { 64.0f, 128.0f }, gTextTexel, "Time Up"));
		m_pvText.push_back(CText::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, Tex_Font,
			{ 32.0f * 1.75f, 32.0f * 3.0f, 0.0 , 0.0f }, { 24.0f, 48.0f }, gTextTexel, "Restart To Press X"));
	}
	if (m_pDirectInput->isPressedOnce(DIK_X))
	{
		m_gameStatus = ePlaying;
		for (int i = 0; i < (int)m_pvText.size(); ++i)
			m_pvText[i]->clearText();
		m_pvText.clear();
		m_pvText.push_back(CText::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, Tex_Font,
			{ 32.0f * 8.0f, 32.0f * 6.0f, 0.0 , 0.0f }, { 64.0f, 128.0f }, gTextTexel, "00000"));
		createMap();
		m_frameCounter = 0;
	}
}

void CKadaiApp::doEnding()
{

}

void CKadaiApp::render(XMFLOAT4X4	matView_, XMFLOAT4X4 matProj_)
{
	for (int i = 0; i < (int)m_pvText.size(); ++i)
	{
		m_pvText[i]->render(matView_, matProj_, m_pvTexture);
	}
	m_pBackground->render(matView_, matProj_, m_pvTexture[eBackgroundTexture]);
	m_pMapManager->render(matView_, matProj_, m_pvTexture);
}
