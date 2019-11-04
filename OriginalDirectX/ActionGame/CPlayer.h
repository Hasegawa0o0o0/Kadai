#pragma once

#include "stdafx.h"
#include "CMapChip.h"
#include "CFootprint.h"
#include "MediaResource.h"

typedef enum eSpriteDirection {
	eSpriteRight = 0,
	eSpriteDownRight = 7,
	eSpriteDown = 7 * 2,
	eSpriteDownLeft = 7 * 3,
	eSpriteLeft = 7 * 4,
	eSpriteUpLeft = 7 * 5,
	eSpriteUp = 7 * 6,
	eSpriteUpRight = 7 * 7,
	eSpriteNone
}eGravityDirection;


class CPlayer : public CMapChip {
	typedef CMapChip super;

	PartiallyCol m_partCol						= {};			// �����I�ȏՓ˔���
	eSpriteDirection m_spriteDirection			= eSpriteNone;	// �X�v���C�g�̃L�����N�^�[�������Ă������
	int m_animMoveSpriteIndex					= 0;			// �\�����Ă���ړ��X�v���C�g
	const int kAnimMoveSpriteIndexMax			= 7;			// �ړ��X�v���C�g�̍ő�C���f�b�N�X
	int m_animFrame								= 0;			// �A�j���[�V����������܂ł̃t���[����
	const int kAnimFrameMax						= 4;			// �A�j���[�V����������t���[����
	int m_footprintSign							= 1;			// ���Ղ𐶐����邽�߂̕���
	int m_footprintActivateCnt					= 0;			// ���Ղ��A�N�e�B�u�ɂ���܂ł̃J�E���g��
	const int kFootprintActivateCntMax			= 4;			// ���Ղ��A�N�e�B�u�ɂ���J�E���g��
	XMFLOAT4 m_previousPosition					= {};			// 1�t���[���O�̈ʒu
	vector<shared_ptr<CFootprint>> m_footprintList;				// ���Ղ̃��X�g
	vector<unique_ptr<CPicture>> m_debugRect;					// �f�o�b�O�p�������
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
	// �ړ�
	void move(XMFLOAT4 speed_);
	// �����œn���ꂽ�l�Œn�ʂɗ����Ă��邩���肵�A�I�t�Z�b�g����
	void checkAndOffset(XMFLOAT4 check_);
	// ���Ղ���A�N�e�B�u�ɂ���
	void activateFootprint();
	PartiallyCol getPartCol()const { return m_partCol; }
	int getAnimIndex()const { return m_animIndex; }
	virtual void render(XMFLOAT4X4 matView_, XMFLOAT4X4 matProj_, vector<shared_ptr<CTexture>> vTexture_, size_t texelIndex_ = 0, XMFLOAT4 diffuse_ = { 0, 0, 0, 0 });
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
