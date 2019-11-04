#pragma once

#include "stdafx.h"
#include "CPicture.h"

class CFootprint : public CPicture {
	typedef CPicture super;

	const FLOAT kWhiteoutValue	= 1.0f / 60.0f;
	FLOAT m_RGBDiffuseValue		= 0.0f;
public:
	static std::shared_ptr<CFootprint> create(
		ID3D11Device*			pDevice_,			//!< デバイス
		ID3D11DeviceContext*	pDeviceContext_,	//!< デバイスコンテキスト
		D3D11_VIEWPORT			viewPort_[],		//!< ビューポート
		LPCWSTR					shaderName_,		//!< シェーダープログラム
		LPCWSTR					textureName_,		//!< 画像ファイル
		XMFLOAT4				position_,			//!< ウィンドウの位置
		XMFLOAT2				size_,				//!< スプライトの大きさ
		std::vector<QuadrangleTexel>	texels);	//!< テクセルの配列
	virtual void init(
		ID3D11Device*			pDevice_,			//!< デバイス
		ID3D11DeviceContext*	pDeviceContext_,	//!< デバイスコンテキスト
		D3D11_VIEWPORT			viewPort_[],		//!< ビューポート
		LPCWSTR					shaderName_,		//!< シェーダープログラム
		LPCWSTR					textureName_,		//!< 画像ファイル
		XMFLOAT4				position_,			//!< ウィンドウの位置
		XMFLOAT2				size_,				//!< スプライトの大きさ
		std::vector<QuadrangleTexel>	texels);	//!< テクセルの配列
	void activate(BOOL isFlip_, XMFLOAT4 position_);
	void update();
	FLOAT getRGBDiffuseValue()const { return m_RGBDiffuseValue; }
};
