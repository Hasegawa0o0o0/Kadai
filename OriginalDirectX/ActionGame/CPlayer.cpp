
#include "stdafx.h"
#include "CPlayer.h"

unique_ptr<CPlayer> CPlayer::create(
	ID3D11Device*			pDevice_,			//!< デバイス
	ID3D11DeviceContext*	pDeviceContext_,	//!< デバイスコンテキスト
	D3D11_VIEWPORT          viewPort_[],		//!< ビューポート
	LPCWSTR					shaderName_,		//!< シェーダープログラム
	LPCWSTR					textureName_,		//!< PNGファイル
	XMFLOAT2				size_,				//!< スプライトの大きさ
	MapIndex				index_,				//!< マップの位置(x, y)
	std::vector<QuadrangleTexel>	texels)		//!< テクセルの配列
{
	unique_ptr<CPlayer> object = unique_ptr<CPlayer>(new CPlayer());
	object->init(pDevice_, pDeviceContext_, viewPort_, shaderName_, textureName_, size_, index_, texels);
	return object;
}

void CPlayer::init(
	ID3D11Device*			pDevice_,			//!< デバイス
	ID3D11DeviceContext*	pDeviceContext_,	//!< デバイスコンテキスト
	D3D11_VIEWPORT          viewPort_[],		//!< ビューポート
	LPCWSTR					shaderName_,		//!< シェーダープログラム
	LPCWSTR					textureName_,		//!< PNGファイル
	XMFLOAT2				size_,				//!< スプライトの大きさ
	MapIndex				index_,				//!< マップの位置(x, y)
	std::vector<QuadrangleTexel>	texels)		//!< テクセルの配列
{
	setName("Player");
	m_gravityScale = 0.2f;
	supre::init(pDevice_, pDeviceContext_, viewPort_, shaderName_, textureName_, size_, index_, texels);
	m_partCol.foot.size = { getSize().x / 2.0f, 2.0f };
	m_partCol.head.size = { getSize().x / 2.0f, 2.0f };
	m_partCol.right.size = { 2.0f, getSize().y / 2.0f };
	m_partCol.left.size = { 2.0f, getSize().y / 2.0f };
	recomposeColPos();
	m_debugRect.push_back(CPicture::create(pDevice_, pDeviceContext_, viewPort_, shaderName_, Tex_Dark, m_partCol.foot.pos, m_partCol.foot.size, texels));
	m_debugRect.push_back(CPicture::create(pDevice_, pDeviceContext_, viewPort_, shaderName_, Tex_Dark, m_partCol.right.pos, m_partCol.right.size, texels));
	m_debugRect.push_back(CPicture::create(pDevice_, pDeviceContext_, viewPort_, shaderName_, Tex_Dark, m_partCol.left.pos, m_partCol.left.size, texels));
	m_debugRect.push_back(CPicture::create(pDevice_, pDeviceContext_, viewPort_, shaderName_, Tex_Dark, m_partCol.head.pos, m_partCol.head.size, texels));
}

// 左右移動
void CPlayer::moveHorizone(int x_)
{
	m_speed.x = x_ * 2;
}

// 上下移動
void CPlayer::moveVertical(int y_)
{
	m_speed.y = y_ * 2;
}

// 引数で渡された値で地面に立っているか判定し、オフセットする
// 引数　：めり込んでいる値
void CPlayer::checkAndOffset(XMFLOAT4 check_)
{
	offsetPos(check_);
}
