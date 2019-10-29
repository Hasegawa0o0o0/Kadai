/**
* @file CMapChip.h
* @brief �}�b�v�`�b�v
* @author �D�ˁ@�엲
* @date ���t�i2017.10.13�j
*/
#pragma once

#include "stdafx.h"
#include "CPicture.h"
#include "DotEat.h"

class CMapChip :
	public CPicture
{
	typedef CPicture super;

private:
	MapIndex m_index = { 0, 0 };
	string m_objectName = "";		// �����I�u�W�F�N�g�̖��O

public:
	static std::unique_ptr<CMapChip> create(
		ID3D11Device*			pDevice_,			//!< �f�o�C�X
		ID3D11DeviceContext*	pDeviceContext_,	//!< �f�o�C�X�R���e�L�X�g
		D3D11_VIEWPORT          viewPort_[],		//!< �r���[�|�[�g
		LPCWSTR					shaderName_,		//!< �V�F�[�_�[�v���O����
		LPCWSTR					textureName_,			//!< PNG�t�@�C��
		XMFLOAT2				size_,				//!< �X�v���C�g�̑傫��
		MapIndex				index_,				//!< �}�b�v�̈ʒu(x, y)
		std::vector<QuadrangleTexel>	texels);			//!< �e�N�Z���̔z��
	void init(
		ID3D11Device*			pDevice_,			//!< �f�o�C�X
		ID3D11DeviceContext*	pDeviceContext_,	//!< �f�o�C�X�R���e�L�X�g
		D3D11_VIEWPORT          viewPort_[],		//!< �r���[�|�[�g
		LPCWSTR					shaderName_,			//!< �V�F�[�_�[�v���O����
		LPCWSTR					textureName_,			//!< PNG�t�@�C��
		XMFLOAT2				size_,				//!< �X�v���C�g�̑傫��
		MapIndex				index_,				//!< �}�b�v�̈ʒu(x, y)
		std::vector<QuadrangleTexel>	texels);			//!< �e�N�Z���̔z��
	CMapChip();
	~CMapChip();
	MapIndex getIndex()				{ return m_index;	}
	void setIndex(MapIndex index_)	{
		m_index = index_;
		setPosFromIndex(index_);
	}
	void setPosFromIndex(MapIndex index_, XMFLOAT2 size_ = { 32.0f, 32.0f });
	// ���O
	void setName(string name_) { m_objectName = name_; }
	string getName()const { return m_objectName; }
};