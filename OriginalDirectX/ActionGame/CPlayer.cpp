
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
	super::init(pDevice_, pDeviceContext_, viewPort_, shaderName_, textureName_, size_, index_, texels);
	m_partCol.foot.size = { getSize().x / 2.0f, 2.0f };
	m_partCol.head.size = { getSize().x / 2.0f, 2.0f };
	m_partCol.right.size = { 2.0f, getSize().y / 2.0f };
	m_partCol.left.size = { 2.0f, getSize().y / 2.0f };
	recomposeColPos();
	m_debugRect.push_back(CPicture::create(pDevice_, pDeviceContext_, viewPort_, shaderName_, Tex_Dark, m_partCol.foot.pos, m_partCol.foot.size, texels));
	m_debugRect.push_back(CPicture::create(pDevice_, pDeviceContext_, viewPort_, shaderName_, Tex_Dark, m_partCol.right.pos, m_partCol.right.size, texels));
	m_debugRect.push_back(CPicture::create(pDevice_, pDeviceContext_, viewPort_, shaderName_, Tex_Dark, m_partCol.left.pos, m_partCol.left.size, texels));
	m_debugRect.push_back(CPicture::create(pDevice_, pDeviceContext_, viewPort_, shaderName_, Tex_Dark, m_partCol.head.pos, m_partCol.head.size, texels));
	// 10個の足跡を生成しておく
	vector <QuadrangleTexel>  texel1_1 = {
		QuadrangleTexel{ { 0, 1.0f },{ 0, 0.0f },{ 1, 1.0f },{ 1, 0.0f } }
	};
	for (int i = 0; i < 10; ++i)
	{
		m_footprintList.push_back(CFootprint::create(pDevice_, pDeviceContext_, viewPort_, HLSL_BlendHLSL, Tex_Footprint, {}, kFootprintSize, texel1_1));
	}
}

// 移動
void CPlayer::move(XMFLOAT4 speed_)
{
	m_speed.x = speed_.x;
	m_speed.y = speed_.y;
	// 歩くスプライトの方向の設定
	if ((int)m_speed.x == 0 && m_speed.y > 0.0f)
	{
		m_spriteDirection = eSpriteUp;
	}
	else if (m_speed.x > 0.0f && m_speed.y > 0.0f)
	{
		m_spriteDirection = eSpriteUpRight;
	}
	else if (m_speed.x > 0.0f && (int)m_speed.y == 0)
	{
		m_spriteDirection = eSpriteRight;
	}
	else if (m_speed.x > 0.0f && m_speed.y < 0.0f)
	{
		m_spriteDirection = eSpriteDownRight;
	}
	else if ((int)m_speed.x == 0 && m_speed.y < 0.0f)
	{
		m_spriteDirection = eSpriteDown;
	}
	else if (m_speed.x < 0.0f && m_speed.y < 0.0f)
	{
		m_spriteDirection = eSpriteDownLeft;
	}
	else if (m_speed.x < 0.0f && (int)m_speed.y == 0)
	{
		m_spriteDirection = eSpriteLeft;
	}
	else if (m_speed.x < 0.0f && m_speed.y > 0.0f)
	{
		m_spriteDirection = eSpriteUpLeft;
	}
	m_animIndex = m_spriteDirection;
	// 歩きアニメーション判定
	if ((int)m_speed.x == 0 && (int)m_speed.y == 0)
	{
		m_animMoveSpriteIndex = 0;
		m_animFrame = 0;
	}
	// 歩いているときは歩くアニメーションをさせる
	else
	{
		++m_animFrame;
		// 設定したフレーム数を過ぎたらスプライトを変える
		if (m_animFrame > kAnimFrameMax)
		{
			++m_animMoveSpriteIndex;
			// 要素番号外に行かないように制限する
			if (m_animMoveSpriteIndex >= kAnimMoveSpriteIndexMax)
			{
				m_animMoveSpriteIndex = 1;
			}
			m_animFrame = 0;
		}
	}
	m_animIndex += m_animMoveSpriteIndex;
	// 移動
	m_previousPosition = m_position.pos;
	offsetPos(m_speed);
	// 1フレーム前から動いているか確認する
	if (m_previousPosition.x != m_position.pos.x ||
		m_previousPosition.y != m_position.pos.y ||
		m_previousPosition.z != m_position.pos.z)
	{
		++m_footprintActivateCnt;
	}
	// 動いているフレーム数が設定したフレーム数を超えたら足跡をつける
	if (m_footprintActivateCnt > kFootprintActivateCntMax)
	{
		activateFootprint();
		m_footprintActivateCnt = 0;
	}
	// アクティブな足跡のアップデート処理
	vector<shared_ptr<CFootprint>>::iterator itr = m_footprintList.begin();
	for (itr; itr != m_footprintList.end(); ++itr)
	{
		if (itr->get()->getActive())
		{
			itr->get()->update();
		}
	}
}

// 足跡を一つアクティブにする
void CPlayer::activateFootprint()
{
	vector<shared_ptr<CFootprint>>::iterator itr = m_footprintList.begin();
	for (itr; itr != m_footprintList.end(); ++itr)
	{
		if (!itr->get()->getActive())
		{
			itr->get()->activate(TRUE, m_position.pos);
			break;
		}
	}
}

// 引数で渡された値で地面に立っているか判定し、オフセットする
// 引数　：めり込んでいる値
void CPlayer::checkAndOffset(XMFLOAT4 check_)
{
	offsetPos(check_);
}

// レンダリング
void CPlayer::render(XMFLOAT4X4 matView_, XMFLOAT4X4 matProj_, vector<shared_ptr<CTexture>> vTexture_, size_t texelIndex_, XMFLOAT4 diffuse_)
{
	super::render(matView_, matProj_, vTexture_[ePlayerTexture], texelIndex_, diffuse_);
	// アクティブな足跡をレンダリング
	vector<shared_ptr<CFootprint>>::iterator itr = m_footprintList.begin();
	for (itr; itr != m_footprintList.end(); ++itr)
	{
		if (itr->get()->getActive())
		{
			itr->get()->render(matView_, matProj_, vTexture_[eFootprintTexture], 0, diffuse_);
		}
	}
}
