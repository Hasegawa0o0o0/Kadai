
#include "stdafx.h"
#include "CFootprint.h"

shared_ptr<CFootprint> CFootprint::create(
	ID3D11Device*			pDevice_,			//!< �f�o�C�X
	ID3D11DeviceContext*	pDeviceContext_,	//!< �f�o�C�X�R���e�L�X�g
	D3D11_VIEWPORT			viewPort_[],		//!< �r���[�|�[�g
	LPCWSTR					shaderName_,		//!< �V�F�[�_�[�v���O����
	LPCWSTR					textureName_,		//!< �摜�t�@�C��
	XMFLOAT4				position_,			//!< �E�B���h�E�̈ʒu
	XMFLOAT2				size_,				//!< �X�v���C�g�̑傫��
	std::vector<QuadrangleTexel>	texels)		//!< �e�N�Z���̔z��
{
	shared_ptr<CFootprint> obj = shared_ptr<CFootprint>(new CFootprint());
	obj->init(pDevice_, pDeviceContext_, viewPort_, shaderName_, textureName_, position_, size_, texels);
	return obj;
}

void CFootprint::init(
	ID3D11Device*			pDevice_,			//!< �f�o�C�X
	ID3D11DeviceContext*	pDeviceContext_,	//!< �f�o�C�X�R���e�L�X�g
	D3D11_VIEWPORT			viewPort_[],		//!< �r���[�|�[�g
	LPCWSTR					shaderName_,		//!< �V�F�[�_�[�v���O����
	LPCWSTR					textureName_,		//!< �摜�t�@�C��
	XMFLOAT4				position_,			//!< �E�B���h�E�̈ʒu
	XMFLOAT2				size_,				//!< �X�v���C�g�̑傫��
	std::vector<QuadrangleTexel>	texels)		//!< �e�N�Z���̔z��
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
