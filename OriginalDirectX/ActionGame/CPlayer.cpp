
#include "stdafx.h"
#include "CPlayer.h"

unique_ptr<CPlayer> CPlayer::create(
	ID3D11Device*			pDevice_,			//!< �f�o�C�X
	ID3D11DeviceContext*	pDeviceContext_,	//!< �f�o�C�X�R���e�L�X�g
	D3D11_VIEWPORT          viewPort_[],		//!< �r���[�|�[�g
	LPCWSTR					shaderName_,		//!< �V�F�[�_�[�v���O����
	LPCWSTR					textureName_,		//!< PNG�t�@�C��
	XMFLOAT2				size_,				//!< �X�v���C�g�̑傫��
	MapIndex				index_,				//!< �}�b�v�̈ʒu(x, y)
	std::vector<QuadrangleTexel>	texels)		//!< �e�N�Z���̔z��
{
	unique_ptr<CPlayer> object = unique_ptr<CPlayer>(new CPlayer());
	object->init(pDevice_, pDeviceContext_, viewPort_, shaderName_, textureName_, size_, index_, texels);
	return object;
}

void CPlayer::init(
	ID3D11Device*			pDevice_,			//!< �f�o�C�X
	ID3D11DeviceContext*	pDeviceContext_,	//!< �f�o�C�X�R���e�L�X�g
	D3D11_VIEWPORT          viewPort_[],		//!< �r���[�|�[�g
	LPCWSTR					shaderName_,		//!< �V�F�[�_�[�v���O����
	LPCWSTR					textureName_,		//!< PNG�t�@�C��
	XMFLOAT2				size_,				//!< �X�v���C�g�̑傫��
	MapIndex				index_,				//!< �}�b�v�̈ʒu(x, y)
	std::vector<QuadrangleTexel>	texels)		//!< �e�N�Z���̔z��
{
	setName("Player");
	m_gravityScale = 0.2f;
	super::init(pDevice_, pDeviceContext_, viewPort_, shaderName_, textureName_, size_, index_, texels);
	m_partCol.foot.size = { getSize().x / 2.0f, 2.0f };
	m_partCol.head.size = { getSize().x / 2.0f, 2.0f };
	m_partCol.right.size = { 2.0f, getSize().y / 2.0f };
	m_partCol.left.size = { 2.0f, getSize().y / 2.0f };
	recomposeColPos();
	m_debugRect.push_back(CPicture::create(pDevice_, pDeviceContext_, viewPort_, shaderName_, Tex_Dark, m_partCol.foot.pos, m_partCol.foot.size, texels));
	m_debugRect.push_back(CPicture::create(pDevice_, pDeviceContext_, viewPort_, shaderName_, Tex_Dark, m_partCol.right.pos, m_partCol.right.size, texels));
	m_debugRect.push_back(CPicture::create(pDevice_, pDeviceContext_, viewPort_, shaderName_, Tex_Dark, m_partCol.left.pos, m_partCol.left.size, texels));
	m_debugRect.push_back(CPicture::create(pDevice_, pDeviceContext_, viewPort_, shaderName_, Tex_Dark, m_partCol.head.pos, m_partCol.head.size, texels));
	// 10�̑��Ղ𐶐����Ă���
	vector <QuadrangleTexel>  texel1_1 = {
		QuadrangleTexel{ { 0, 1.0f },{ 0, 0.0f },{ 1, 1.0f },{ 1, 0.0f } }
	};
	for (int i = 0; i < 10; ++i)
	{
		m_footprintList.push_back(CFootprint::create(pDevice_, pDeviceContext_, viewPort_, HLSL_BlendHLSL, Tex_Footprint, {}, kFootprintSize, texel1_1));
	}
}

// �ړ�
void CPlayer::move(XMFLOAT4 speed_)
{
	m_speed.x = speed_.x;
	m_speed.y = speed_.y;
	// �����X�v���C�g�̕����̐ݒ�
	if ((int)m_speed.x == 0 && m_speed.y > 0.0f)
	{
		m_spriteDirection = eSpriteUp;
	}
	else if (m_speed.x > 0.0f && m_speed.y > 0.0f)
	{
		m_spriteDirection = eSpriteUpRight;
	}
	else if (m_speed.x > 0.0f && (int)m_speed.y == 0)
	{
		m_spriteDirection = eSpriteRight;
	}
	else if (m_speed.x > 0.0f && m_speed.y < 0.0f)
	{
		m_spriteDirection = eSpriteDownRight;
	}
	else if ((int)m_speed.x == 0 && m_speed.y < 0.0f)
	{
		m_spriteDirection = eSpriteDown;
	}
	else if (m_speed.x < 0.0f && m_speed.y < 0.0f)
	{
		m_spriteDirection = eSpriteDownLeft;
	}
	else if (m_speed.x < 0.0f && (int)m_speed.y == 0)
	{
		m_spriteDirection = eSpriteLeft;
	}
	else if (m_speed.x < 0.0f && m_speed.y > 0.0f)
	{
		m_spriteDirection = eSpriteUpLeft;
	}
	m_animIndex = m_spriteDirection;
	// �����A�j���[�V��������
	if ((int)m_speed.x == 0 && (int)m_speed.y == 0)
	{
		m_animMoveSpriteIndex = 0;
		m_animFrame = 0;
	}
	// �����Ă���Ƃ��͕����A�j���[�V������������
	else
	{
		++m_animFrame;
		// �ݒ肵���t���[�������߂�����X�v���C�g��ς���
		if (m_animFrame > kAnimFrameMax)
		{
			++m_animMoveSpriteIndex;
			// �v�f�ԍ��O�ɍs���Ȃ��悤�ɐ�������
			if (m_animMoveSpriteIndex >= kAnimMoveSpriteIndexMax)
			{
				m_animMoveSpriteIndex = 1;
			}
			m_animFrame = 0;
		}
	}
	m_animIndex += m_animMoveSpriteIndex;
	// �ړ�
	m_previousPosition = m_position.pos;
	offsetPos(m_speed);
	// 1�t���[���O���瓮���Ă��邩�m�F����
	if (m_previousPosition.x != m_position.pos.x ||
		m_previousPosition.y != m_position.pos.y ||
		m_previousPosition.z != m_position.pos.z)
	{
		++m_footprintActivateCnt;
	}
	// �����Ă���t���[�������ݒ肵���t���[�����𒴂����瑫�Ղ�����
	if (m_footprintActivateCnt > kFootprintActivateCntMax)
	{
		activateFootprint();
		m_footprintActivateCnt = 0;
	}
	// �A�N�e�B�u�ȑ��Ղ̃A�b�v�f�[�g����
	vector<shared_ptr<CFootprint>>::iterator itr = m_footprintList.begin();
	for (itr; itr != m_footprintList.end(); ++itr)
	{
		if (itr->get()->getActive())
		{
			itr->get()->update();
		}
	}
}

// ���Ղ���A�N�e�B�u�ɂ���
void CPlayer::activateFootprint()
{
	vector<shared_ptr<CFootprint>>::iterator itr = m_footprintList.begin();
	for (itr; itr != m_footprintList.end(); ++itr)
	{
		if (!itr->get()->getActive())
		{
			itr->get()->activate(TRUE, m_position.pos);
			break;
		}
	}
}

// �����œn���ꂽ�l�Œn�ʂɗ����Ă��邩���肵�A�I�t�Z�b�g����
// �����@�F�߂荞��ł���l
void CPlayer::checkAndOffset(XMFLOAT4 check_)
{
	offsetPos(check_);
}

// �����_�����O
void CPlayer::render(XMFLOAT4X4 matView_, XMFLOAT4X4 matProj_, vector<shared_ptr<CTexture>> vTexture_, size_t texelIndex_, XMFLOAT4 diffuse_)
{
	super::render(matView_, matProj_, vTexture_[ePlayerTexture], texelIndex_, diffuse_);
	// �A�N�e�B�u�ȑ��Ղ������_�����O
	vector<shared_ptr<CFootprint>>::iterator itr = m_footprintList.begin();
	for (itr; itr != m_footprintList.end(); ++itr)
	{
		if (itr->get()->getActive())
		{
			itr->get()->render(matView_, matProj_, vTexture_[eFootprintTexture], 0, diffuse_);
		}
	}
}
