/**
 * @file CMapChip.cpp
 * @brief �}�b�v�`�b�v
 * @author �D�ˁ@�엲
 * @date ���t�i2017.10.13�j
 */
#include "stdafx.h"
#include "CMapChip.h"

/**
 * @fn std::unique_ptr<CMapChip> CMapChip::create(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, LPCWSTR textureName_,�@XMFLOAT4 position_, XMFLOAT2 size_, MapIndex index_, std::vector<QuadrangleTexel> texels)
 * @brief �C���X�^���X�𐶐��������� �y�N���X���\�b�h�z
 * @param pDevice_			�f�o�C�X
 * @param pDeviceContext_	�f�o�C�X�R���e�L�X�g
 * @param viewPort_[]		�r���[�|�[�g
 * @param shaderName_		�V�F�[�_�[�v���O����
 * @param textureName_		PNG�t�@�C��
 * @param position_			�E�B���h�E�̈ʒu
 * @param size_				�X�v���C�g�̑傫��
 * @param index_			�}�b�v�̈ʒu(x, y)
 * @param texels			�}�b�v�`�b�v�̃e�N�Z���̔z��
 * @return					CMapChip�̃��j�[�N�|�C���^
 */
std::unique_ptr<CMapChip> CMapChip::create(
	ID3D11Device* pDevice_,
	ID3D11DeviceContext* pDeviceContext_,
	D3D11_VIEWPORT viewPort_[],
	LPCWSTR shaderName_,
	LPCWSTR textureName_,
	XMFLOAT2 size_,
	MapIndex index_,
	std::vector<QuadrangleTexel> texels)
{
	std::unique_ptr<CMapChip> object = unique_ptr<CMapChip>(new CMapChip());
	object->init(pDevice_, pDeviceContext_, viewPort_, shaderName_, textureName_, size_, index_, texels);
	return object;
}

CMapChip::CMapChip()
{
}


CMapChip::~CMapChip()
{
}

/**
 * @fn void CMapChip::init(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, LPCWSTR textureName_,�@XMFLOAT4 position_, XMFLOAT2 size_,MapIndex index_, std::vector<QuadrangleTexel> texels)
 * @brief �C���X�^���X��������
 * @param pDevice_			�f�o�C�X
 * @param pDeviceContext_	�f�o�C�X�R���e�L�X�g
 * @param viewPort_[]		�r���[�|�[�g
 * @param shaderName_		�V�F�[�_�[�v���O����
 * @param textureName_		PNG�t�@�C��
 * @param index_			�}�b�v�̈ʒu(x, y)
 * @param texels			�e�N�Z���̔z��
 * @return					����
 */
void CMapChip::init(
	ID3D11Device* pDevice_,
	ID3D11DeviceContext* pDeviceContext_,
	D3D11_VIEWPORT viewPort_[],
	LPCWSTR shaderName_,
	LPCWSTR textureName_,
	XMFLOAT2 size_,
	MapIndex index_,
	std::vector<QuadrangleTexel> texels)
{
	setPosFromIndex(index_);
	super::init(pDevice_, pDeviceContext_, viewPort_, shaderName_, textureName_, m_position.pos, size_, texels); //!< �X�[�p�[�N���X�̃��\�b�h�����s
}

/**
 * @fn void CMapChip::setPosFromIndex(MapIndex index_, XMFLOAT2 size_)
 * @brief �}�b�v��̈ʒu��ݒ肷��
 * @param index_		�}�b�v�̈ʒu(x, y)
 * @param size_		�}�b�v�`�b�v�̑傫�����f�t�H���g�l��
 * @return			����
 */

void CMapChip::setPosFromIndex(MapIndex index_, XMFLOAT2 size_)
{
	m_index = index_;
	m_position.pos.x = (FLOAT)(index_.x * size_.x);
	m_position.pos.y = (FLOAT)(index_.y * size_.y);
	m_position.pos.z = 0.0f;
	m_position.pos.w = 0.0f;
}