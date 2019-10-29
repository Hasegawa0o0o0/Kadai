/**
 * @file CScroll.h
 * @brief CScroll�N�X�N���[���N���X���X
 * @author �D�ˁ@�엲
 * @date ���t�i2017.02.14�j
 */
#pragma once

#include "stdafx.h"
#include "CPicture.h"

/*! @class CScroll
@brief  �X�N���[���N���X
*/
class CScroll
{
private:
	eScrollMode						m_scrollMode = eVirtical;	//!< �X�N���[���������
	std::unique_ptr<CPicture>	m_sprite1 = NULL;	//!< �X�N���[������@�X�v���C�g��
	std::unique_ptr<CPicture>	m_sprite2 = NULL;	//!< �X�N���[������@�X�v���C�g��
	XMFLOAT2	m_posLeftTop = { 0.0f, 0.0f }; 			//!< �X�v���C�g����@�ʒu
	XMFLOAT2	m_posRightBottom = { 0.0f, 0.0f }; 		//!< �X�v���C�g�E���@�ʒu
public:
	static std::unique_ptr<CScroll> create(
		ID3D11Device*			pDevice_,			//!< �f�o�C�X
		ID3D11DeviceContext*	pDeviceContext_,	//!< �f�o�C�X�R���e�L�X�g
		D3D11_VIEWPORT			viewPort_[],		//!< �r���[�|�[�g
		LPCWSTR					shaderName_,			//!< �V�F�[�_�[�v���O����
		LPCWSTR					textureName_,			//!< PNG�t�@�C��
		XMFLOAT4				position_,			//!< �E�B���h�E�̈ʒu
		XMFLOAT2				size_,				//!< �X�v���C�g�̑傫��
		std::vector<QuadrangleTexel>	texels,			//!< �e�N�Z���̔z��
		eScrollMode				scrollMode_			//!< �X�N���[���������
		);	
	CScroll();
	~CScroll();
	void setScrollMode(eScrollMode mode_) { m_scrollMode = mode_; }
	void offsetPos(XMFLOAT4 v4Pos_) {
		m_sprite1->offsetPos(v4Pos_);
		m_sprite2->offsetPos(v4Pos_);
	};
	void init(
		ID3D11Device*			pDevice_,			//!< �f�o�C�X
		ID3D11DeviceContext*	pDeviceContext_,	//!< �f�o�C�X�R���e�L�X�g
		D3D11_VIEWPORT			viewPort_[],		//!< �r���[�|�[�g
		LPCWSTR					shaderName_,			//!< �V�F�[�_�[�v���O����
		LPCWSTR					textureName_,			//!< PNG�t�@�C��
		XMFLOAT4				position_,			//!< �E�B���h�E�̈ʒu
		XMFLOAT2				size_,				//!< �X�v���C�g�̑傫��
		std::vector<QuadrangleTexel>	texels,			//!< �e�N�Z���̔z��
		eScrollMode				scrollMode_			//!< �X�N���[���������
	);

	void scroll(float value_);
	void horizontalScroll(float value_);
	void verticalScroll(float value_);
	void render(XMFLOAT4X4 matView_, XMFLOAT4X4 matProj_);
	void release();
};