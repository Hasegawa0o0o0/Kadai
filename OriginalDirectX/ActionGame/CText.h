/**
* @file CText.h
* @brief �e�L�X�g�\���̂��߂̃N���X
* @author ���J��@�E��
* @date ���t�i2018.11.19�j
*/
#pragma once

#include "stdafx.h"
#include "DotEat.h"
#include "CPicture.h"

class CText
{
	vector<char> m_vTextChr;
	vector<shared_ptr<CPicture>> m_vText;
public:
	CText();
	~CText();
	static std::shared_ptr<CText> create(
		ID3D11Device*			pDevice_,			//!< �f�o�C�X
		ID3D11DeviceContext*	pDeviceContext_,	//!< �f�o�C�X�R���e�L�X�g
		D3D11_VIEWPORT          viewPort_[],		//!< �r���[�|�[�g
		LPCWSTR					shaderName_,		//!< �V�F�[�_�[�v���O����
		LPCWSTR					textureName_,			//!< PNG�t�@�C��
		XMFLOAT4				pos_,				// ���߂̈ʒu
		XMFLOAT2				size_,				//!< �X�v���C�g�̑傫��
		std::vector<QuadrangleTexel>	texels,			//!< �e�N�Z���̔z��
		char					str_[]);			// �����e�L�X�g
	void init(
		ID3D11Device*			pDevice_,			//!< �f�o�C�X
		ID3D11DeviceContext*	pDeviceContext_,	//!< �f�o�C�X�R���e�L�X�g
		D3D11_VIEWPORT          viewPort_[],		//!< �r���[�|�[�g
		LPCWSTR					shaderName_,			//!< �V�F�[�_�[�v���O����
		LPCWSTR					textureName_,			//!< PNG�t�@�C��
		XMFLOAT4				pos_,				// ���߂̈ʒu
		XMFLOAT2				size_,				//!< �X�v���C�g�̑傫��
		std::vector<QuadrangleTexel>	texels,			//!< �e�N�Z���̔z��
		char					str_[]);			// �����e�L�X�g
	void setText(const char str[]);
	void setText(const int n);
	string getText();
	void resetTest();
	void clearText();
	void setBeginPos(XMFLOAT4 pos_);
	XMFLOAT4 getBeginPos();
	void conversionC2I(vector<int>& vi_, vector<char> str_);
	void render(XMFLOAT4X4	matView_, XMFLOAT4X4 matProj_, vector<shared_ptr<CTexture>> vTexture_);
	void release();
};

// �e�L�X�gUV
static std::vector <QuadrangleTexel>  gTextTexel = {
	// 1~0
	QuadrangleTexel{ { k1_26 * 0, k1_3 * 1 },{ k1_26 * 0, k1_3 * 0 },{ k1_26 * 1, k1_3 * 1 },{ k1_26 * 1, k1_3 * 0 } },
	QuadrangleTexel{ { k1_26 * 1, k1_3 * 1 },{ k1_26 * 1, k1_3 * 0 },{ k1_26 * 2, k1_3 * 1 },{ k1_26 * 2, k1_3 * 0 } },
	QuadrangleTexel{ { k1_26 * 2, k1_3 * 1 },{ k1_26 * 2, k1_3 * 0 },{ k1_26 * 3, k1_3 * 1 },{ k1_26 * 3, k1_3 * 0 } },
	QuadrangleTexel{ { k1_26 * 3, k1_3 * 1 },{ k1_26 * 3, k1_3 * 0 },{ k1_26 * 4, k1_3 * 1 },{ k1_26 * 4, k1_3 * 0 } },
	QuadrangleTexel{ { k1_26 * 4, k1_3 * 1 },{ k1_26 * 4, k1_3 * 0 },{ k1_26 * 5, k1_3 * 1 },{ k1_26 * 5, k1_3 * 0 } },
	QuadrangleTexel{ { k1_26 * 5, k1_3 * 1 },{ k1_26 * 5, k1_3 * 0 },{ k1_26 * 6, k1_3 * 1 },{ k1_26 * 6, k1_3 * 0 } },
	QuadrangleTexel{ { k1_26 * 6, k1_3 * 1 },{ k1_26 * 6, k1_3 * 0 },{ k1_26 * 7, k1_3 * 1 },{ k1_26 * 7, k1_3 * 0 } },
	QuadrangleTexel{ { k1_26 * 7, k1_3 * 1 },{ k1_26 * 7, k1_3 * 0 },{ k1_26 * 8, k1_3 * 1 },{ k1_26 * 8, k1_3 * 0 } },
	QuadrangleTexel{ { k1_26 * 8, k1_3 * 1 },{ k1_26 * 8, k1_3 * 0 },{ k1_26 * 9, k1_3 * 1 },{ k1_26 * 9, k1_3 * 0 } },
	QuadrangleTexel{ { k1_26 * 9, k1_3 * 1 },{ k1_26 * 9, k1_3 * 0 },{ k1_26 * 10, k1_3 * 1 },{ k1_26 * 10, k1_3 * 0 } },
	// A~Z
	QuadrangleTexel{ { k1_26 * 0, k1_3 * 2 },{ k1_26 * 0, k1_3 * 1 },{ k1_26 * 1, k1_3 * 2 },{ k1_26 * 1, k1_3 * 1 } },
	QuadrangleTexel{ { k1_26 * 1, k1_3 * 2 },{ k1_26 * 1, k1_3 * 1 },{ k1_26 * 2, k1_3 * 2 },{ k1_26 * 2, k1_3 * 1 } },
	QuadrangleTexel{ { k1_26 * 2, k1_3 * 2 },{ k1_26 * 2, k1_3 * 1 },{ k1_26 * 3, k1_3 * 2 },{ k1_26 * 3, k1_3 * 1 } },
	QuadrangleTexel{ { k1_26 * 3, k1_3 * 2 },{ k1_26 * 3, k1_3 * 1 },{ k1_26 * 4, k1_3 * 2 },{ k1_26 * 4, k1_3 * 1 } },
	QuadrangleTexel{ { k1_26 * 4, k1_3 * 2 },{ k1_26 * 4, k1_3 * 1 },{ k1_26 * 5, k1_3 * 2 },{ k1_26 * 5, k1_3 * 1 } },
	QuadrangleTexel{ { k1_26 * 5, k1_3 * 2 },{ k1_26 * 5, k1_3 * 1 },{ k1_26 * 6, k1_3 * 2 },{ k1_26 * 6, k1_3 * 1 } },
	QuadrangleTexel{ { k1_26 * 6, k1_3 * 2 },{ k1_26 * 6, k1_3 * 1 },{ k1_26 * 7, k1_3 * 2 },{ k1_26 * 7, k1_3 * 1 } },
	QuadrangleTexel{ { k1_26 * 7, k1_3 * 2 },{ k1_26 * 7, k1_3 * 1 },{ k1_26 * 8, k1_3 * 2 },{ k1_26 * 8, k1_3 * 1 } },
	QuadrangleTexel{ { k1_26 * 8, k1_3 * 2 },{ k1_26 * 8, k1_3 * 1 },{ k1_26 * 9, k1_3 * 2 },{ k1_26 * 9, k1_3 * 1 } },
	QuadrangleTexel{ { k1_26 * 9, k1_3 * 2 },{ k1_26 * 9, k1_3 * 1 },{ k1_26 * 10, k1_3 * 2 },{ k1_26 * 10, k1_3 * 1 } },
	QuadrangleTexel{ { k1_26 * 10, k1_3 * 2 },{ k1_26 * 10, k1_3 * 1 },{ k1_26 * 11, k1_3 * 2 },{ k1_26 * 11, k1_3 * 1 } },
	QuadrangleTexel{ { k1_26 * 11, k1_3 * 2 },{ k1_26 * 11, k1_3 * 1 },{ k1_26 * 12, k1_3 * 2 },{ k1_26 * 12, k1_3 * 1 } },
	QuadrangleTexel{ { k1_26 * 12, k1_3 * 2 },{ k1_26 * 12, k1_3 * 1 },{ k1_26 * 13, k1_3 * 2 },{ k1_26 * 13, k1_3 * 1 } },
	QuadrangleTexel{ { k1_26 * 13, k1_3 * 2 },{ k1_26 * 13, k1_3 * 1 },{ k1_26 * 14, k1_3 * 2 },{ k1_26 * 14, k1_3 * 1 } },
	QuadrangleTexel{ { k1_26 * 14, k1_3 * 2 },{ k1_26 * 14, k1_3 * 1 },{ k1_26 * 15, k1_3 * 2 },{ k1_26 * 15, k1_3 * 1 } },
	QuadrangleTexel{ { k1_26 * 15, k1_3 * 2 },{ k1_26 * 15, k1_3 * 1 },{ k1_26 * 16, k1_3 * 2 },{ k1_26 * 16, k1_3 * 1 } },
	QuadrangleTexel{ { k1_26 * 16, k1_3 * 2 },{ k1_26 * 16, k1_3 * 1 },{ k1_26 * 17, k1_3 * 2 },{ k1_26 * 17, k1_3 * 1 } },
	QuadrangleTexel{ { k1_26 * 17, k1_3 * 2 },{ k1_26 * 17, k1_3 * 1 },{ k1_26 * 18, k1_3 * 2 },{ k1_26 * 18, k1_3 * 1 } },
	QuadrangleTexel{ { k1_26 * 18, k1_3 * 2 },{ k1_26 * 18, k1_3 * 1 },{ k1_26 * 19, k1_3 * 2 },{ k1_26 * 19, k1_3 * 1 } },
	QuadrangleTexel{ { k1_26 * 19, k1_3 * 2 },{ k1_26 * 19, k1_3 * 1 },{ k1_26 * 20, k1_3 * 2 },{ k1_26 * 20, k1_3 * 1 } },
	QuadrangleTexel{ { k1_26 * 20, k1_3 * 2 },{ k1_26 * 20, k1_3 * 1 },{ k1_26 * 21, k1_3 * 2 },{ k1_26 * 21, k1_3 * 1 } },
	QuadrangleTexel{ { k1_26 * 21, k1_3 * 2 },{ k1_26 * 21, k1_3 * 1 },{ k1_26 * 22, k1_3 * 2 },{ k1_26 * 22, k1_3 * 1 } },
	QuadrangleTexel{ { k1_26 * 22, k1_3 * 2 },{ k1_26 * 22, k1_3 * 1 },{ k1_26 * 23, k1_3 * 2 },{ k1_26 * 23, k1_3 * 1 } },
	QuadrangleTexel{ { k1_26 * 23, k1_3 * 2 },{ k1_26 * 23, k1_3 * 1 },{ k1_26 * 24, k1_3 * 2 },{ k1_26 * 24, k1_3 * 1 } },
	QuadrangleTexel{ { k1_26 * 24, k1_3 * 2 },{ k1_26 * 24, k1_3 * 1 },{ k1_26 * 25, k1_3 * 2 },{ k1_26 * 25, k1_3 * 1 } },
	QuadrangleTexel{ { k1_26 * 25, k1_3 * 2 },{ k1_26 * 25, k1_3 * 1 },{ k1_26 * 26, k1_3 * 2 },{ k1_26 * 26, k1_3 * 1 } },
	// a~z
	QuadrangleTexel{ { k1_26 * 0, k1_3 * 3 },{ k1_26 * 0, k1_3 * 2 },{ k1_26 * 1, k1_3 * 3 },{ k1_26 * 1, k1_3 * 2 } },
	QuadrangleTexel{ { k1_26 * 1, k1_3 * 3 },{ k1_26 * 1, k1_3 * 2 },{ k1_26 * 2, k1_3 * 3 },{ k1_26 * 2, k1_3 * 2 } },
	QuadrangleTexel{ { k1_26 * 2, k1_3 * 3 },{ k1_26 * 2, k1_3 * 2 },{ k1_26 * 3, k1_3 * 3 },{ k1_26 * 3, k1_3 * 2 } },
	QuadrangleTexel{ { k1_26 * 3, k1_3 * 3 },{ k1_26 * 3, k1_3 * 2 },{ k1_26 * 4, k1_3 * 3 },{ k1_26 * 4, k1_3 * 2 } },
	QuadrangleTexel{ { k1_26 * 4, k1_3 * 3 },{ k1_26 * 4, k1_3 * 2 },{ k1_26 * 5, k1_3 * 3 },{ k1_26 * 5, k1_3 * 2 } },
	QuadrangleTexel{ { k1_26 * 5, k1_3 * 3 },{ k1_26 * 5, k1_3 * 2 },{ k1_26 * 6, k1_3 * 3 },{ k1_26 * 6, k1_3 * 2 } },
	QuadrangleTexel{ { k1_26 * 6, k1_3 * 3 },{ k1_26 * 6, k1_3 * 2 },{ k1_26 * 7, k1_3 * 3 },{ k1_26 * 7, k1_3 * 2 } },
	QuadrangleTexel{ { k1_26 * 7, k1_3 * 3 },{ k1_26 * 7, k1_3 * 2 },{ k1_26 * 8, k1_3 * 3 },{ k1_26 * 8, k1_3 * 2 } },
	QuadrangleTexel{ { k1_26 * 8, k1_3 * 3 },{ k1_26 * 8, k1_3 * 2 },{ k1_26 * 9, k1_3 * 3 },{ k1_26 * 9, k1_3 * 2 } },
	QuadrangleTexel{ { k1_26 * 9, k1_3 * 3 },{ k1_26 * 9, k1_3 * 2 },{ k1_26 * 10, k1_3 * 3 },{ k1_26 * 10, k1_3 * 2 } },
	QuadrangleTexel{ { k1_26 * 10, k1_3 * 3 },{ k1_26 * 10, k1_3 * 2 },{ k1_26 * 11, k1_3 * 3 },{ k1_26 * 11, k1_3 * 2 } },
	QuadrangleTexel{ { k1_26 * 11, k1_3 * 3 },{ k1_26 * 11, k1_3 * 2 },{ k1_26 * 12, k1_3 * 3 },{ k1_26 * 12, k1_3 * 2 } },
	QuadrangleTexel{ { k1_26 * 12, k1_3 * 3 },{ k1_26 * 12, k1_3 * 2 },{ k1_26 * 13, k1_3 * 3 },{ k1_26 * 13, k1_3 * 2 } },
	QuadrangleTexel{ { k1_26 * 13, k1_3 * 3 },{ k1_26 * 13, k1_3 * 2 },{ k1_26 * 14, k1_3 * 3 },{ k1_26 * 14, k1_3 * 2 } },
	QuadrangleTexel{ { k1_26 * 14, k1_3 * 3 },{ k1_26 * 14, k1_3 * 2 },{ k1_26 * 15, k1_3 * 3 },{ k1_26 * 15, k1_3 * 2 } },
	QuadrangleTexel{ { k1_26 * 15, k1_3 * 3 },{ k1_26 * 15, k1_3 * 2 },{ k1_26 * 16, k1_3 * 3 },{ k1_26 * 16, k1_3 * 2 } },
	QuadrangleTexel{ { k1_26 * 16, k1_3 * 3 },{ k1_26 * 16, k1_3 * 2 },{ k1_26 * 17, k1_3 * 3 },{ k1_26 * 17, k1_3 * 2 } },
	QuadrangleTexel{ { k1_26 * 17, k1_3 * 3 },{ k1_26 * 17, k1_3 * 2 },{ k1_26 * 18, k1_3 * 3 },{ k1_26 * 18, k1_3 * 2 } },
	QuadrangleTexel{ { k1_26 * 18, k1_3 * 3 },{ k1_26 * 18, k1_3 * 2 },{ k1_26 * 19, k1_3 * 3 },{ k1_26 * 19, k1_3 * 2 } },
	QuadrangleTexel{ { k1_26 * 19, k1_3 * 3 },{ k1_26 * 19, k1_3 * 2 },{ k1_26 * 20, k1_3 * 3 },{ k1_26 * 20, k1_3 * 2 } },
	QuadrangleTexel{ { k1_26 * 20, k1_3 * 3 },{ k1_26 * 20, k1_3 * 2 },{ k1_26 * 21, k1_3 * 3 },{ k1_26 * 21, k1_3 * 2 } },
	QuadrangleTexel{ { k1_26 * 21, k1_3 * 3 },{ k1_26 * 21, k1_3 * 2 },{ k1_26 * 22, k1_3 * 3 },{ k1_26 * 22, k1_3 * 2 } },
	QuadrangleTexel{ { k1_26 * 22, k1_3 * 3 },{ k1_26 * 22, k1_3 * 2 },{ k1_26 * 23, k1_3 * 3 },{ k1_26 * 23, k1_3 * 2 } },
	QuadrangleTexel{ { k1_26 * 23, k1_3 * 3 },{ k1_26 * 23, k1_3 * 2 },{ k1_26 * 24, k1_3 * 3 },{ k1_26 * 24, k1_3 * 2 } },
	QuadrangleTexel{ { k1_26 * 24, k1_3 * 3 },{ k1_26 * 24, k1_3 * 2 },{ k1_26 * 25, k1_3 * 3 },{ k1_26 * 25, k1_3 * 2 } },
	QuadrangleTexel{ { k1_26 * 25, k1_3 * 3 },{ k1_26 * 25, k1_3 * 2 },{ k1_26 * 26, k1_3 * 3 },{ k1_26 * 26, k1_3 * 2 } },
	// �X�y�[�X
	QuadrangleTexel{ { k1_26 * 10, k1_3 * 1 },{ k1_26 * 10, k1_3 * 0 },{ k1_26 * 11, k1_3 * 1 },{ k1_26 * 11, k1_3 * 0 } },
};
