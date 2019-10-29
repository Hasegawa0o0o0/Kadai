#pragma once

#include "stdafx.h"
#include "CMapChip.h"
#include "MediaResource.h"

typedef enum eGravityDirection {
	eGDown = 0,
	eGLeft = 1,
	eGRight = 2,
	eGUp = 3,
	eGNone
}eGravityDirection;


class CPlayer : public CMapChip {
	typedef CMapChip supre;

	PartiallyCol m_partCol						= {};		// �����I�ȏՓ˔���
	FLOAT m_jumpPower							= 0.0f;		// �W�����v�̏���
	const FLOAT kGravityScaleMax				= 3.0f;		// �d�͂̍ő�l
	BOOL m_isGround								= FALSE;	// �n�ʂɗ����Ă��邩
	eGravityDirection m_gravityDirection		= eGNone;	// �d�͂���������
	int m_rattlingFrame							= 0;		// �n�ʂɗ��������k����t���[����
	int m_shakeSign								= 1;		// �h�炷�Ƃ��̕���
	vector<unique_ptr<CPicture>> m_debugRect;				// �f�o�b�O�p�������
public:
	static std::unique_ptr<CPlayer> create(
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
	// �d�͉��Z
	void gravityProc();
	// �����蔻��������̈ʒu�ɍ��킹��
	void recomposeColPos()
	{
		m_partCol.foot.pos = { getPos().x, getPos().y - getSize().y / 2.0f,
			0.0f, 0.0f };
		m_partCol.head.pos = { getPos().x, getPos().y + getSize().y / 2.0f,
			0.0f, 0.0f };
		m_partCol.right.pos = { getPos().x + getSize().x / 2.0f, getPos().y,
			0.0f,0.0f };
		m_partCol.left.pos = { getPos().x - getSize().x / 2.0f, getPos().y,
			0.0f,0.0f };
	}
	// �W�����v
	void jump();
	// ���ړ�(�d�͂��㉺�̂ǂ��炩�̎�)
	void moveHorizone(int x_);
	// �c�ړ�(�d�͂����E�̂ǂ��炩�̎�)
	void moveVertical(int y_);
	// �����œn���ꂽ�l�Œn�ʂɗ����Ă��邩���肵�A�I�t�Z�b�g����
	void checkAndOffset(XMFLOAT4 check_);
	// �Ă΂�Ă���ԗh�炷
	void shake();
	// �k����t���[�������J�E���g����
	void CountUpRattlingFrame() {
		++m_rattlingFrame;
		if (m_rattlingFrame > 90)	++m_rattlingFrame;
		if (m_rattlingFrame > 150)	++m_rattlingFrame;
	}
	int getRattlingFrame()const { return m_rattlingFrame; }
	PartiallyCol getPartCol()const { return m_partCol; }
	void setGround(BOOL isGrd_) { m_isGround = isGrd_; }
	BOOL getGround()const { return m_isGround; }
	void setGravityDirection(eGravityDirection dir_) { m_gravityDirection = dir_;	m_animIndex = dir_; }
	eGravityDirection getGravityDirection() { return m_gravityDirection; }
	int getAnimIndex()const { return m_animIndex; }
	void debugRectRender(XMFLOAT4X4 matView_, XMFLOAT4X4 matProj_, shared_ptr<CTexture> texture_)
	{
		vector<unique_ptr<CPicture>>::iterator itr = m_debugRect.begin();
		for (int i = 0; i < (int)m_debugRect.size(); ++i)
		{
			switch (i)
			{
			case 0:
				itr[i]->setPos(m_partCol.foot.pos);
				break;
			case 1:
				itr[i]->setPos(m_partCol.right.pos);
				break;
			case 2:
				itr[i]->setPos(m_partCol.left.pos);
				break;
			case 3:
				itr[i]->setPos(m_partCol.head.pos);
				break;
			default:
				break;
			}
			itr[i]->render(matView_, matProj_, texture_);
		}
	}
};
