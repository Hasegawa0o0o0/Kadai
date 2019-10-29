/**
* @file CSpaceship.h
* @brief �X�y�[�X�V�b�v�i���ۃN���X�j
* @author �D�ˁ@�엲
* @date ���t�i2017.02.14�j
*/
#pragma once

#include "stdafx.h"
#include "CExplosion.h"
#include "CTexture.h"
#include "MediaResource.h"

class CSpaceship :
	public CQuadPolygon
{
	typedef CQuadPolygon super;
protected:
	std::shared_ptr<CQuadPolygon>	m_pBullets[32] = { NULL,NULL };
	int								m_bulletTexelIndex = 0;
	std::shared_ptr<CExplosion>		m_pExplosion = NULL;
	int								m_hp = kMaxHP;
	std::shared_ptr<CTexture>		m_pBulletTex = NULL;	//!< �e�N�Z��
	std::shared_ptr<CTexture>		m_pExplosionTex = NULL;	//!< �e�N�Z��
public:
	CSpaceship();
	~CSpaceship();
	size_t countEmptyBullets ()
	{
		int ret_ = 0;
		enumBullets(	
			[&](std::shared_ptr<CQuadPolygon> bullet_, size_t index_) -> BOOL {
			if (bullet_->getState() == eWaiting)
			{
				ret_++;
			}
			return TRUE; //!< �񋓂𑱍s
		});
		return ret_;
	}
	virtual XMFLOAT4 computeBulletPos(size_t index_) {
		return{ 0, 0, 0, 0 };	// �y�d�v�z�K���T�u�N���X�ŃI�[�o�[���C�h���邱��
	}
	virtual void init(
		ID3D11Device*			pDevice_,			// �f�o�C�X
		ID3D11DeviceContext*	pDeviceContext_,	// �f�o�C�X�R���e�L�X�g
		D3D11_VIEWPORT			viewPort_[],		// �r���[�|�[�g
		LPCWSTR					shaderName_,		// �V�F�[�_�[�v���O����
		XMFLOAT4				position_,			// �E�B���h�E�̈ʒu
		XMFLOAT2				size_,				// �X�v���C�g�̑傫��
		std::vector<QuadrangleTexel>	texels,			// �X�y�[�X�V�b�v�̃e�N�Z���̔z��
		int						bulletTexelIndex_);	// �e�ۂ̃e�N�Z���̃C���f�b�N�X�i�v���[���[�Ƌ��L�j
	void release();
	virtual void render(XMFLOAT4X4	matView_, XMFLOAT4X4 matProj_, std::function<void(ID3D11DeviceContext* pDeviceContext_)> callbackTextureProc_, size_t texelIndex_ = 0, XMFLOAT4 v4Diffuse_ = { 0, 0, 0, 0 });
	virtual void shot(void) = 0;
	void shot(std::vector<FLOAT> directions_);
	void shotOpt(BOOL ready_) {
		if (ready_)
			shot();
	};
	BOOL collisionBullet(XMFLOAT4 pos_, FLOAT range_);
	void explode()						{ m_pExplosion->explode(); };
	void resetAllBullets();
	void enumBullets(std::function<BOOL(std::shared_ptr<CQuadPolygon>, size_t)> callbackEnumeProc_);
	void stepAnimation(BOOL enable_, std::vector <QuadrangleTexel> animations_)
	{
		if (enable_)
		{
			m_animIndex++;
			m_animIndex = m_animIndex >= animations_.size() ? 0 : m_animIndex;
		}
	}
	BOOL receiveDamage() {
		m_hp--;
		if (m_hp <= 0)
		{
			return TRUE;
		}
		else {
			return FALSE;
		}
	}
};

