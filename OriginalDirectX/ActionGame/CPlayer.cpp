
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
	supre::init(pDevice_, pDeviceContext_, viewPort_, shaderName_, textureName_, size_, index_, texels);
	m_partCol.foot.size = { getSize().x / 2.0f, 2.0f };
	m_partCol.head.size = { getSize().x / 2.0f, 2.0f };
	m_partCol.right.size = { 2.0f, getSize().y / 2.0f };
	m_partCol.left.size = { 2.0f, getSize().y / 2.0f };
	recomposeColPos();
	m_debugRect.push_back(CPicture::create(pDevice_, pDeviceContext_, viewPort_, shaderName_, Tex_Dark, m_partCol.foot.pos, m_partCol.foot.size, texels));
	m_debugRect.push_back(CPicture::create(pDevice_, pDeviceContext_, viewPort_, shaderName_, Tex_Dark, m_partCol.right.pos, m_partCol.right.size, texels));
	m_debugRect.push_back(CPicture::create(pDevice_, pDeviceContext_, viewPort_, shaderName_, Tex_Dark, m_partCol.left.pos, m_partCol.left.size, texels));
	m_debugRect.push_back(CPicture::create(pDevice_, pDeviceContext_, viewPort_, shaderName_, Tex_Dark, m_partCol.head.pos, m_partCol.head.size, texels));
}

// ���E�ړ�
void CPlayer::moveHorizone(int x_)
{
	m_speed.x = x_ * 2;
}

// �㉺�ړ�
void CPlayer::moveVertical(int y_)
{
	m_speed.y = y_ * 2;
}

// �����œn���ꂽ�l�Œn�ʂɗ����Ă��邩���肵�A�I�t�Z�b�g����
// �����@�F�߂荞��ł���l
void CPlayer::checkAndOffset(XMFLOAT4 check_)
{
	offsetPos(check_);
}
