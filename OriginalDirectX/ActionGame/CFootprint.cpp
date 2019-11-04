
#include "stdafx.h"
#include "CFootprint.h"

shared_ptr<CFootprint> CFootprint::create(
	ID3D11Device*			pDevice_,			//!< デバイス
	ID3D11DeviceContext*	pDeviceContext_,	//!< デバイスコンテキスト
	D3D11_VIEWPORT			viewPort_[],		//!< ビューポート
	LPCWSTR					shaderName_,		//!< シェーダープログラム
	LPCWSTR					textureName_,		//!< 画像ファイル
	XMFLOAT4				position_,			//!< ウィンドウの位置
	XMFLOAT2				size_,				//!< スプライトの大きさ
	std::vector<QuadrangleTexel>	texels)		//!< テクセルの配列
{
	shared_ptr<CFootprint> obj = shared_ptr<CFootprint>(new CFootprint());
	obj->init(pDevice_, pDeviceContext_, viewPort_, shaderName_, textureName_, position_, size_, texels);
	return obj;
}

void CFootprint::init(
	ID3D11Device*			pDevice_,			//!< デバイス
	ID3D11DeviceContext*	pDeviceContext_,	//!< デバイスコンテキスト
	D3D11_VIEWPORT			viewPort_[],		//!< ビューポート
	LPCWSTR					shaderName_,		//!< シェーダープログラム
	LPCWSTR					textureName_,		//!< 画像ファイル
	XMFLOAT4				position_,			//!< ウィンドウの位置
	XMFLOAT2				size_,				//!< スプライトの大きさ
	std::vector<QuadrangleTexel>	texels)		//!< テクセルの配列
{
	super::init(pDevice_, pDeviceContext_, viewPort_, shaderName_, textureName_, position_, size_, texels);
	m_active = FALSE;
}

void CFootprint::activate(BOOL isFlip_, XMFLOAT4 position_)
{
	m_active = true;
	m_RGBDiffuseValue = 0.0f;
	m_position.pos = position_;
}

void CFootprint::update()
{
	m_RGBDiffuseValue += kWhiteoutValue;
	if (m_RGBDiffuseValue >= 1.0f)
	{
		m_active = false;
	}
}
