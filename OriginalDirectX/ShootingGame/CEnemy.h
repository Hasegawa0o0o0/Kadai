/**
* @file CEnemy.h
* @brief �G
* @author �D�ˁ@�엲
* @date ���t�i2017.02.14�j
*/
#pragma once

#include "stdafx.h"
#include "CSpaceship.h"

class CEnemy :
	public CSpaceship
{
	typedef CSpaceship super;

public:
	static std::shared_ptr<CEnemy> create(
		ID3D11Device*			pDevice_,			// �f�o�C�X
		ID3D11DeviceContext*	pDeviceContext_,	// �f�o�C�X�R���e�L�X�g
		D3D11_VIEWPORT          viewPort_[],		// �r���[�|�[�g
		LPCWSTR					shaderName_,		// �V�F�[�_�[�v���O����
		XMFLOAT4				position_,			// �E�B���h�E�̈ʒu
		XMFLOAT2				size_,				// �X�v���C�g�̑傫��
		int						bulletTexelIndex_);	// �e�ۂ̃e�N�Z���̃C���f�b�N�X�i�G�Ƌ��L�j
	CEnemy();
	~CEnemy();
	XMFLOAT4 computeBulletPos(size_t index_) {
		FLOAT x = getPos().x;
		FLOAT y = getPos().y - 8.0f;
		return{ x, y, 0, 0 };
	}
	void init(
		ID3D11Device*			pDevice_,			// �f�o�C�X
		ID3D11DeviceContext*	pDeviceContext_,	// �f�o�C�X�R���e�L�X�g
		D3D11_VIEWPORT          viewPort_[],		// �r���[�|�[�g
		LPCWSTR					shaderName_,		// �V�F�[�_�[�v���O����
		XMFLOAT4				position_,			// �E�B���h�E�̈ʒu
		XMFLOAT2				size_,				// �X�v���C�g�̑傫��
		int						bulletTexelIndex_);	// �e�ۂ̃e�N�Z���̃C���f�b�N�X�i�v���[���[�Ƌ��L�j
	void stepAnimation (BOOL enable_);
	void render(XMFLOAT4X4	matView_, XMFLOAT4X4 matProj_, std::function<void(ID3D11DeviceContext* pDeviceContext_)> callbackTextureProc_);
	void shot(void);
};