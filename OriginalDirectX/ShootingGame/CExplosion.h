/**
* @file CExplosion.h
* @brief ����
* @author �D�ˁ@�엲
* @date ���t�i2017.02.14�j
*/
#pragma once

#include "stdafx.h"
#include "UVAnimation.h"
#include "CQuadPolygon.h"

// Const

class CExplosion :
	public CQuadPolygon
{
	typedef CQuadPolygon super;

	BOOL m_started		= FALSE;	// �����J�n
	BOOL m_completed	= FALSE;	// ����
	size_t m_TexelIndex	= 0;		// �A�j���[�V�����̃C���f�b�N�X
	int m_waitCounter	= 0;		// �A�j���[�V����1��������̃J�E���^
	int m_framesOfWait	= 0;		// �A�j���[�V����1��������̃t���[����
public:
	static std::shared_ptr<CExplosion> CExplosion::create(
		ID3D11Device*			pDevice_,			// �f�o�C�X
		ID3D11DeviceContext*	pDeviceContext_,	// �f�o�C�X�R���e�L�X�g
		D3D11_VIEWPORT			viewPort_[],		// �r���[�|�[�g
		LPCWSTR					shaderName_,		// �V�F�[�_�[�v���O����
		XMFLOAT4				position_,			// �E�B���h�E�̈ʒu
		XMFLOAT2				size_,				// �X�v���C�g�̑傫��
		std::vector<QuadrangleTexel>	texels,			// �e�N�Z���̔z��
		int						framesOfWait_);		// �|�[�Y����t���[����
	CExplosion();
	~CExplosion();

	void explode()		{ m_started = TRUE; }
	void init(
		ID3D11Device*			pDevice_,			// �f�o�C�X
		ID3D11DeviceContext*	pDeviceContext_,	// �f�o�C�X�R���e�L�X�g
		D3D11_VIEWPORT			viewPort_[],		// �r���[�|�[�g
		LPCWSTR					shaderName_,		// �V�F�[�_�[�v���O����
		XMFLOAT4				position_,			// �E�B���h�E�̈ʒu
		XMFLOAT2				size_,				// �X�v���C�g�̑傫��
		std::vector<QuadrangleTexel>	texels,			// �e�N�Z���̔z��
		int						framesOfWait_);		// �|�[�Y����t���[����
	void render(XMFLOAT4X4 matView_, XMFLOAT4X4 matProj_, std::function<void(ID3D11DeviceContext* pDeviceContext_)> callbackTextureProc_, size_t texelIndex_ = 0);
	void reset();
	BOOL isCompleted() { return m_started && m_completed; };
};
