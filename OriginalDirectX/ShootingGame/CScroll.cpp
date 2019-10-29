/**
 * @file CScroll.cpp
 * @brief �X�N���[���N���X
 * @author �D�ˁ@�엲
 * @date ���t�i2017.02.14�j
 */

#include "stdafx.h"
#include "CScroll.h"

/**
 * @fn void CScroll::create(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, LPCWSTR textureName_, XMFLOAT4 position_, XMFLOAT2 size_, std::vector<QuadrangleTexel> texels)
 * @brief �C���X�^���X���擾 �y�N���X���\�b�h�z
 * @param pDevice_			�f�o�C�X
 * @param pDeviceContext_	�f�o�C�X�R���e�L�X�g
 * @param viewPort_[]		�r���[�|�[�g
 * @param shaderName_			�V�F�[�_�[�v���O����
 * @param textureName	PNG�t�@�C��_
 * @param position_			�E�B���h�E�̈ʒu
 * @param size_				�X�v���C�g�̑傫��
 * @param texels			�e�N�Z���̔z��
 * @param scrollMode_		�X�N���[���̕����i�c/���j
 * @return					CScroll�̃��j�[�N�|�C���^
 */
std::unique_ptr<CScroll> CScroll::create(
	ID3D11Device*			pDevice_,
	ID3D11DeviceContext*	pDeviceContext_,
	D3D11_VIEWPORT			viewPort_[],
	LPCWSTR					shaderName_,
	LPCWSTR					textureName_,
	XMFLOAT4				position_,
	XMFLOAT2				size_,
	std::vector<QuadrangleTexel>	texels,
	eScrollMode				scrollMode_)
{
	std::unique_ptr<CScroll> object = unique_ptr<CScroll>(new CScroll());
	object->init(pDevice_, pDeviceContext_, viewPort_, shaderName_, textureName_, position_, size_, texels, scrollMode_);
	return object;
}

/**
 * @fn void CScroll::init(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, LPCWSTR textureName_, XMFLOAT4 position_, XMFLOAT2 size_, std::vector<QuadrangleTexel> texels)
 * @brief �C���X�^���X��������
 * @param pDevice_			�f�o�C�X
 * @param pDeviceContext_	�f�o�C�X�R���e�L�X�g
 * @param viewPort_[]		�r���[�|�[�g
 * @param shaderName_		�V�F�[�_�[�v���O����
 * @param textureName	PNG�t�@�C��_
 * @param position_			�E�B���h�E�̈ʒu
 * @param size_				�X�v���C�g�̑傫��
 * @param texels			�e�N�Z���̔z��
 * @param scrollMode_		�X�N���[���̕����i�c/���j
 * @return					����
 */
void CScroll::init(
	ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[],
	LPCWSTR shaderName_,
	LPCWSTR textureName_,
	XMFLOAT4 position_,
	XMFLOAT2 size_,
	std::vector<QuadrangleTexel> texels,
	eScrollMode scrollMode_)
{
	m_scrollMode = scrollMode_;
	if (m_scrollMode == eHorizontal)
	{
		m_posLeftTop = { size_.x / 2 ,  -0 };
		m_posRightBottom = { -size_.x / 2 , 240 };
	}
	else {
		m_posLeftTop = { 0.0 ,  size_.y / 2 };
		m_posRightBottom = { 0.0 , -size_.y / 2 };
	}

	/**
	 *�X�v���C�g�̍쐬
	 */
	m_sprite1 = CPicture::create(pDevice_, pDeviceContext_, viewPort_, shaderName_, textureName_, position_, { size_.x, size_.y /*+ 2*/ }, texels);
	m_sprite2 = CPicture::create(pDevice_, pDeviceContext_, viewPort_, shaderName_, textureName_, position_, { size_.x, size_.y /*+ 2*/ }, texels);

	/**
	 *�X�v���C�g�̈ʒu��������
	 */
	m_sprite1->setPos({ 0.0,  m_posLeftTop.y, 0.0f, 0.0f });
	m_sprite2->setPos({ 0.0,  m_posRightBottom.y, 0.0f, 0.0f });
}

CScroll::CScroll()
{
}

CScroll::~CScroll()
{
}

/**
* @fn void CScroll::horizontalScroll(float value_)
* @brief �X�N���[��
* @param value_	�X�N���[����
* @return		����
*/
void CScroll::scroll(float value_)
{
	if (m_scrollMode == eHorizontal)
	{
		horizontalScroll(value_);
	}
	else {
		verticalScroll(value_);
	}
}

/**
* @fn void CScroll::horizontalScroll(float value_)
* @brief �X�N���[��
* @param value_	�X�N���[����
* @return		����
*/
void CScroll::horizontalScroll(float value_)
{
	/**
	* �w�肳�ꂽ�������X�N���[��
	*/
	m_posLeftTop.x += value_;
	m_posRightBottom.x += value_;

	/**
	* ��ʂ͈̔͊O�Ȃ�ŏ��̈ʒu�ɂ���
	*/
	m_posLeftTop.x = (
		m_posLeftTop.x < -m_sprite1->getSize().x + 2 ? m_sprite1->getSize().x : m_posLeftTop.x);
	m_posRightBottom.x = (m_posRightBottom.x < -m_sprite2->getSize().x + 2 ? m_sprite2->getSize().x : m_posRightBottom.x);

	/**
	* �ʒu�����肷��
	*/
	m_sprite1->setPos({ m_posLeftTop.x, m_sprite1->getPos().y, m_sprite1->getPos().z, m_sprite1->getPos().w });
	m_sprite2->setPos({ m_posRightBottom.x, m_sprite1->getPos().y, m_sprite1->getPos().z, m_sprite1->getPos().w });
}

/**
 * @fn void CScroll::verticalScroll(float value_)
 * @brief �X�N���[��
 * @param value_	�X�N���[����
 * @return		����
 */
void CScroll::verticalScroll(float value_)
{
	/**
	 * �w�肳�ꂽ�������X�N���[��
	 */
	m_posLeftTop.y += value_;
	m_posRightBottom.y += value_;

	/**
	 * ��ʂ͈̔͊O�Ȃ�ŏ��̈ʒu�ɂ���
	 */
	m_posLeftTop.y = (m_posLeftTop.y < -m_sprite1->getSize ().y + 2 ? m_sprite1->getSize ().y : m_posLeftTop.y);
	m_posRightBottom.y = (m_posRightBottom.y < -m_sprite2->getSize ().y + 2 ? m_sprite2->getSize ().y : m_posRightBottom.y);

	/**
	 * �ʒu�����肷��
	 */
	m_sprite1->setPos({ m_sprite1->getPos().x, m_posLeftTop.y, m_sprite1->getPos().z, m_sprite1->getPos().w });
	m_sprite2->setPos({ m_sprite1->getPos().x, m_posRightBottom.y, m_sprite1->getPos().z, m_sprite1->getPos().w });
}

/**
 * @fn void CScroll::render(XMFLOAT4X4 matView_, XMFLOAT4X4 matProj_)
 * @brief �����_�����O
 * @param matView_	�r���[�s��
 * @param matProj_	�v���W�F�N�V�����s��
 * @return     ����
 */
void CScroll::render(XMFLOAT4X4 matView_, XMFLOAT4X4 matProj_)
{
	m_sprite1->render(matView_, matProj_);
	m_sprite2->render(matView_, matProj_);
}

/**
 * @fn void CScroll::release()
 * @brief �����[�X
 * @param	����
 * @return   ����
 */
//�����[�X
void CScroll::release()
{
	m_sprite1->release();
	m_sprite2->release();
}