/**
* @file CSingleSprite.h
* @brief �e�� �e�N�X�`�����N���X�ϐ��Ƃ��ċ��L����
* @author �D�ˁ@�엲
* @date ���t�i2018.07.23�j
*/
#pragma once

#include "stdafx.h"
#include "CommonType.h"
#include "CPolygon.h"
#include "CXMMath.h"

class CSingleSprite :
	public CPolygon
{
	typedef CPolygon super;
private:
	static ID3D11SamplerState*			g_pSampleLinear;	//!< �y�N���X�ϐ��z�e�N�X�`���[�̃T���v���[
	static ID3D11ShaderResourceView*	g_pTexture;			//!< �y�N���X�ϐ��z�e�N�X�`���[

public:
	static std::unique_ptr<CSingleSprite> create(//!< �y�N���X���\�b�h�z
		ID3D11Device*			pDevice_,		//!< �f�o�C�X
		ID3D11DeviceContext*	pDeviceContext_,//!< �f�o�C�X�R���e�L�X�g
		D3D11_VIEWPORT			viewPort_[],	//!< �r���[�|�[�g
		LPCWSTR					shaderName_,	//!< �V�F�[�_�[�v���O����
		LPCWSTR					textureName_,	//!< �����̉摜�t�@�C��
		XMFLOAT4				position_,		//!< �E�B���h�E�̈ʒu
		XMFLOAT2				size_,			//!< �X�v���C�g�̑傫��
		std::vector<UVCoord>	uvArray_);		//!< ������UV�z��

	CSingleSprite();
	~CSingleSprite();
	virtual void init(
		ID3D11Device*			pDevice_,		//!< �f�o�C�X
		ID3D11DeviceContext*	pDeviceContext_,//!< �f�o�C�X�R���e�L�X�g
		D3D11_VIEWPORT			viewPort_[],	//!< �r���[�|�[�g
		LPCWSTR					shaderName_,	//!< �V�F�[�_�[�v���O����
		LPCWSTR					textureName_,	//!< �����̉摜�t�@�C��
		XMFLOAT4				position_,		//!< �E�B���h�E�̈ʒu
		XMFLOAT2				size_,			//!< �X�v���C�g�̑傫��
		std::vector<UVCoord>	uvArray_);		//!< ������UV�z��
	void createSamplerAndTexture(ID3D11Device*pDevice_, LPCWSTR textureName_);
	virtual void setSamplerAndTexture();
	virtual void render(XMFLOAT4X4 matView_, XMFLOAT4X4 matProj_, size_t uvIndex_ = 0, XMFLOAT4 diffuse_ = { 0, 0, 0, 0 }); //!< �e�N�X�`�����N���X�ϐ��Ƃ��ċ��L����
	void release(void);
};

