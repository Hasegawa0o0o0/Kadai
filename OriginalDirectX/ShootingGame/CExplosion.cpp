/**
 * @file CExplosion.cpp
 * @brief ����
 * @author �D�ˁ@�엲
 * @date ���t�i2017.02.14�j
 */

#include "stdafx.h"
#include "CExplosion.h"

/**
 * @fn std::unique_ptr<CExplosion> CExplosion::create(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, XMFLOAT4 position_, XMFLOAT2 size_, std::vector<QuadrangleTexel> texels)
 * @brief �C���X�^���X�𐶐��������� �y�N���X���\�b�h�z
 * @param pDevice_			�f�o�C�X
 * @param pDeviceContext_	�f�o�C�X�R���e�L�X�g
 * @param viewPort_[]		�r���[�|�[�g
 * @param shaderName_		�V�F�[�_�[�v���O����
 * @param position_			�E�B���h�E�̈ʒu
 * @param size_				�X�v���C�g�̑傫��
 * @param bulletTexelIndex_	�e�ۂ̃e�N�Z���̃C���f�b�N�X�i�v���[���[�Ƌ��L�j
 * @return					CPlayer�̃��j�[�N�|�C���^
 */
std::shared_ptr<CExplosion> CExplosion::create(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, XMFLOAT4 position_, XMFLOAT2 size_, std::vector<QuadrangleTexel> texels, int framesOfWait_)
{
	std::shared_ptr<CExplosion> object = unique_ptr<CExplosion>(new CExplosion());
	object->init(pDevice_, pDeviceContext_, viewPort_, shaderName_, position_, size_, texels, framesOfWait_);
	return object;
}

/**
 * @fn void CExplosion::init(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, XMFLOAT4 position_, XMFLOAT2 size_, std::vector<QuadrangleTexel> texels)
 * @brief �C���X�^���X��������
 * @param pDevice_			�f�o�C�X
 * @param pDeviceContext_	�f�o�C�X�R���e�L�X�g
 * @param viewPort_[]		�r���[�|�[�g
 * @param shaderName_			�V�F�[�_�[�v���O����
 * @param position_			�E�B���h�E�̈ʒu
 * @param size_				�X�v���C�g�̑傫��
 * @param bulletTexelIndex_	�e�ۂ̃e�N�Z���̃C���f�b�N�X�i�v���[���[�Ƌ��L�j
 * @return					����
 */

void CExplosion::init(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, XMFLOAT4 position_, XMFLOAT2 size_, std::vector<QuadrangleTexel> texels, int framesOfWait_)
{
	super::init(pDevice_, pDeviceContext_, viewPort_, shaderName_, position_, size_, texels); //!< �X�[�p�[�N���X�̃��\�b�h�����s
	m_framesOfWait	= framesOfWait_;
	reset();
}

CExplosion::CExplosion()
{
}

CExplosion::~CExplosion()
{
}

/**
 * @fn void CExplosion::render(XMFLOAT4X4	matView_, XMFLOAT4X4 matProj_)
 * @brief �����_�����O
 * @param matView_	�r���[�s��
 * @param matProj_	�v���W�F�N�V�����s��
 * @param texelIndex_	�e�ۂ̏���
 * @return			����
 */
void CExplosion::render(XMFLOAT4X4	matView_, XMFLOAT4X4 matProj_, std::function<void(ID3D11DeviceContext* pDeviceContext_)> callbackTextureProc_, size_t texelIndex_)
{
	if (isInvalid() || m_started == FALSE)
	{
		return;
	}

	if (m_TexelIndex < m_pVertexBuffer.size())
	{
		super::render(matView_, matProj_, callbackTextureProc_, m_TexelIndex); //!< �X�[�p�[�N���X�̃��\�b�h�����s
		m_waitCounter++;
		if (m_waitCounter > m_framesOfWait)
		{
			m_waitCounter = 0;
			m_TexelIndex++;
		}
	} else {
		m_completed = TRUE;
	}
}

/**
 * @fn void CExplosion::reset()
 * @brief �e�ۂ�������Ԃɂ���
 * @param	����
 * @return	����
 */
void CExplosion::reset()
{
	m_started	= FALSE;
	m_TexelIndex		= 0;
	m_waitCounter	= 0;
}