/**
* @file CPlayer.h
* @brief �v���[���[
* @author �D�ˁ@�엲
* @date ���t�i2017.02.14�j
*/
#pragma once

#include "stdafx.h"
#include "CSpaceship.h"

/*! @struct BulletPlace
@brief  �e�ۂ̍\���� <���� �ʒu>
*/
struct BulletPlace {
	FLOAT dir;
	FLOAT pos;
};

class CPlayer :
	public CSpaceship
{
	typedef CSpaceship super;

public:
	static std::unique_ptr<CPlayer> create(
		ID3D11Device*			pDevice_,			// �f�o�C�X
		ID3D11DeviceContext*	pDeviceContext_,	// �f�o�C�X�R���e�L�X�g
		D3D11_VIEWPORT			viewPort_[],		// �r���[�|�[�g
		LPCWSTR					shaderName_,		// �V�F�[�_�[�v���O����
		XMFLOAT4				position_,			// �E�B���h�E�̈ʒu
		XMFLOAT2				size_,				// �X�v���C�g�̑傫��
		int						bulletTexelIndex_);	// �e�ۂ̃e�N�Z���̃C���f�b�N�X�i�G�Ƌ��L�j
	CPlayer();
	~CPlayer();
	XMFLOAT4 computeBulletPos(size_t index_) {
		FLOAT x = getPos().x + kBullet_Left;
		FLOAT y = getPos().y + 7.0f;
		if (countSideBullet(x) == 0)
		{
			x = getPos().x + kBullet_Left;
		}
		else {
			x = getPos().x + kBullet_Right;
		}
		return{ x, y, 0, 0 };
	}
	int countSideBullet(FLOAT x_)
	{
		int ans = 0;
		enumBullets([&](std::shared_ptr<CQuadPolygon> bullet_, size_t index_) -> BOOL {
			if ((bullet_->getState() == eWaiting) && (bullet_->getPos().x == x_))
			{
				ans++;
			}
			return TRUE; //!< �񋓂𑱍s
		});
		return ans;
	}
	void init(
		ID3D11Device*			pDevice_,			// �f�o�C�X
		ID3D11DeviceContext*	pDeviceContext_,	// �f�o�C�X�R���e�L�X�g
		D3D11_VIEWPORT			viewPort_[],		// �r���[�|�[�g
		LPCWSTR					shaderName_,		// �V�F�[�_�[�v���O����
		XMFLOAT4				position_,			// �E�B���h�E�̈ʒu
		XMFLOAT2				size_,				// �X�v���C�g�̑傫��
		int						bulletTexelIndex_);	// �e�ۂ̃e�N�Z���̃C���f�b�N�X�i�G�Ƌ��L�j
	void stepAnimation (BOOL enable_);
	void render(XMFLOAT4X4	matView_, XMFLOAT4X4	matProj_, std::function<void(ID3D11DeviceContext* pDeviceContext_)> callbackTextureProc_ );
	void shot(void);
	BOOL isExplosionCompleted()
	{
		return m_pExplosion->isCompleted();
	}
};