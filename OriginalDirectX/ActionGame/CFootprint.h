#pragma once

#include "stdafx.h"
#include "CPicture.h"

class CFootprint : public CPicture {
	typedef CPicture super;

	const FLOAT kWhiteoutValue	= 1.0f / 60.0f;
	FLOAT m_RGBDiffuseValue		= 0.0f;
public:
	static std::shared_ptr<CFootprint> create(
		ID3D11Device*			pDevice_,			//!< �f�o�C�X
		ID3D11DeviceContext*	pDeviceContext_,	//!< �f�o�C�X�R���e�L�X�g
		D3D11_VIEWPORT			viewPort_[],		//!< �r���[�|�[�g
		LPCWSTR					shaderName_,		//!< �V�F�[�_�[�v���O����
		LPCWSTR					textureName_,		//!< �摜�t�@�C��
		XMFLOAT4				position_,			//!< �E�B���h�E�̈ʒu
		XMFLOAT2				size_,				//!< �X�v���C�g�̑傫��
		std::vector<QuadrangleTexel>	texels);	//!< �e�N�Z���̔z��
	virtual void init(
		ID3D11Device*			pDevice_,			//!< �f�o�C�X
		ID3D11DeviceContext*	pDeviceContext_,	//!< �f�o�C�X�R���e�L�X�g
		D3D11_VIEWPORT			viewPort_[],		//!< �r���[�|�[�g
		LPCWSTR					shaderName_,		//!< �V�F�[�_�[�v���O����
		LPCWSTR					textureName_,		//!< �摜�t�@�C��
		XMFLOAT4				position_,			//!< �E�B���h�E�̈ʒu
		XMFLOAT2				size_,				//!< �X�v���C�g�̑傫��
		std::vector<QuadrangleTexel>	texels);	//!< �e�N�Z���̔z��
	void activate(BOOL isFlip_, XMFLOAT4 position_);
	void update();
	FLOAT getRGBDiffuseValue()const { return m_RGBDiffuseValue; }
};
