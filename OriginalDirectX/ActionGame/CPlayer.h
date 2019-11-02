#pragma once

#include "stdafx.h"
#include "CMapChip.h"
#include "MediaResource.h"

typedef enum eSpriteDirection {
	eSpriteRight = 0,
	eSpriteDownRight = 7,
	eSpriteDown = 7 * 2,
	eSpriteDownLeft = 7 * 3,
	eSpriteLeft = 7 * 4,
	eSpriteUpLeft = 7 * 5,
	eSpriteUp = 7 * 6,
	eSpriteUpRight = 7 * 7,
	eSpriteNone
}eGravityDirection;


class CPlayer : public CMapChip {
	typedef CMapChip supre;

	PartiallyCol m_partCol						= {};			// 部分的な衝突判定
	eSpriteDirection m_spriteDirection			= eSpriteNone;	// スプライトのキャラクターが向いている方向
	int m_animMoveSpriteIndex					= 0;			// 表示している移動スプライト
	const int kAnimMoveSpriteIndexMax			= 7;			// 移動スプライトの最大インデックス
	int m_animFrame								= 0;			// アニメーションさせるまでのフレーム数
	const int kAnimFrameMax						= 4;			// アニメーションさせるフレーム数
	int m_footprintSign							= 1;			// 足跡を生成するための符号
	vector<unique_ptr<CPicture>> m_debugRect;					// デバッグ用判定可視化
public:
	static std::unique_ptr<CPlayer> create(
		ID3D11Device*			pDevice_,			//!< デバイス
		ID3D11DeviceContext*	pDeviceContext_,	//!< デバイスコンテキスト
		D3D11_VIEWPORT          viewPort_[],		//!< ビューポート
		LPCWSTR					shaderName_,		//!< シェーダープログラム
		LPCWSTR					textureName_,			//!< PNGファイル
		XMFLOAT2				size_,				//!< スプライトの大きさ
		MapIndex				index_,				//!< マップの位置(x, y)
		std::vector<QuadrangleTexel>	texels);			//!< テクセルの配列
	void init(
		ID3D11Device*			pDevice_,			//!< デバイス
		ID3D11DeviceContext*	pDeviceContext_,	//!< デバイスコンテキスト
		D3D11_VIEWPORT          viewPort_[],		//!< ビューポート
		LPCWSTR					shaderName_,			//!< シェーダープログラム
		LPCWSTR					textureName_,			//!< PNGファイル
		XMFLOAT2				size_,				//!< スプライトの大きさ
		MapIndex				index_,				//!< マップの位置(x, y)
		std::vector<QuadrangleTexel>	texels);			//!< テクセルの配列
	// 当たり判定を自分の位置に合わせる
	void recomposeColPos()
	{
		m_partCol.foot.pos = { getPos().x, getPos().y - getSize().y / 2.0f,
			0.0f, 0.0f };
		m_partCol.head.pos = { getPos().x, getPos().y + getSize().y / 2.0f,
			0.0f, 0.0f };
		m_partCol.right.pos = { getPos().x + getSize().x / 2.0f, getPos().y,
			0.0f,0.0f };
		m_partCol.left.pos = { getPos().x - getSize().x / 2.0f, getPos().y,
			0.0f,0.0f };
	}
	// 移動
	void move(XMFLOAT4 speed_);
	// 引数で渡された値で地面に立っているか判定し、オフセットする
	void checkAndOffset(XMFLOAT4 check_);
	PartiallyCol getPartCol()const { return m_partCol; }
	int getAnimIndex()const { return m_animIndex; }
	void debugRectRender(XMFLOAT4X4 matView_, XMFLOAT4X4 matProj_, shared_ptr<CTexture> texture_)
	{
		vector<unique_ptr<CPicture>>::iterator itr = m_debugRect.begin();
		for (int i = 0; i < (int)m_debugRect.size(); ++i)
		{
			switch (i)
			{
			case 0:
				itr[i]->setPos(m_partCol.foot.pos);
				break;
			case 1:
				itr[i]->setPos(m_partCol.right.pos);
				break;
			case 2:
				itr[i]->setPos(m_partCol.left.pos);
				break;
			case 3:
				itr[i]->setPos(m_partCol.head.pos);
				break;
			default:
				break;
			}
			itr[i]->render(matView_, matProj_, texture_);
		}
	}
};
