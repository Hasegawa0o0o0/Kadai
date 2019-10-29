/**
 * @file CPlayer.cpp
 * @brief �v���[���[
 * @author �D�ˁ@�엲
 * @date ���t�i2017.02.14�j
 */

#include "stdafx.h"
#include "CPlayer.h"

/**
 * @fn std::unique_ptr<CPlayer> CPlayer::create(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, XMFLOAT4 position_, XMFLOAT2 size_, std::vector<QuadrangleTexel> texels)
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
std::unique_ptr<CPlayer> CPlayer::create(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, XMFLOAT4 position_, XMFLOAT2 size_, int bulletTexelIndex_)
{
	std::unique_ptr<CPlayer> object = unique_ptr<CPlayer>(new CPlayer());
	object->init(pDevice_, pDeviceContext_, viewPort_, shaderName_, position_, size_, bulletTexelIndex_);
	return object;
}

/**
 * @fn void CPlayer::init(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, XMFLOAT4 position_, XMFLOAT2 size_, std::vector<QuadrangleTexel> texels)
 * @brief �C���X�^���X��������
 * @param pDevice_			�f�o�C�X
 * @param pDeviceContext_	�f�o�C�X�R���e�L�X�g
 * @param viewPort_[]		�r���[�|�[�g
 * @param shaderName_		�V�F�[�_�[�v���O����
 * @param position_			�E�B���h�E�̈ʒu
 * @param size_				�X�v���C�g�̑傫��
 * @param bulletTexelIndex_	�e�ۂ̃e�N�Z���̃C���f�b�N�X�i�v���[���[�Ƌ��L�j
 * @return					����
 */
void CPlayer::init( ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, XMFLOAT4 position_, XMFLOAT2 size_, int bulletTexelIndex_)
{
	super::init(pDevice_, pDeviceContext_, viewPort_, shaderName_, position_, size_, kTexelPlayers, bulletTexelIndex_); //!< �X�[�p�[�N���X�̃��\�b�h�����s
	m_moveQuantity = 0.528f * 1.75f;
	enumBullets(
		[=](std::shared_ptr<CQuadPolygon> bullet_, size_t index_) -> BOOL {
		bullet_->setMoveQuantity(2.5);
		return TRUE; //!< �񋓂𑱍s
	});
}

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

/**
 * @fn BOOL CPlayer::stepAnimation (BOOL enable_)
 * @brief �A�j���[�V����
 * @param enable_	�A�j���[�V�����̗L����
 * @return			�p���E���~
 */
void CPlayer::stepAnimation (BOOL enable_)
{
	super::stepAnimation(enable_, kTexelPlayers); //!< �X�[�p�[�N���X�̃��\�b�h�����s
}

/**
 * @fn void CPlayer::render(XMFLOAT4X4	matView_, XMFLOAT4X4 matProj_)
 * @brief �����_�����O
 * @param matView_	�r���[�s��
 * @param matProj_	�v���W�F�N�V�����s��
 * @return			����
 */
void CPlayer::render(XMFLOAT4X4 matView_, XMFLOAT4X4 matProj_, std::function<void(ID3D11DeviceContext* pDeviceContext_)> callbackTextureProc_)
{
	if (!outOfWindow())
	{
		if (m_damaged)
		{
			super::render(matView_, matProj_, callbackTextureProc_, m_animIndex, { 1, 0, 0, 0 }); //!< �X�[�p�[�N���X�̃��\�b�h�����s
		}
		else
		{
			super::render(matView_, matProj_, callbackTextureProc_, m_animIndex, { 0, 0, 0, 0 }); //!< �X�[�p�[�N���X�̃��\�b�h�����s
		}
	}
}

/**
 * @fn void CPlayer::shot(void)
 * @brief �e�ۂ𔭎�
 * @param	����
 * @return	����
 */
void CPlayer::shot(void)
{
	std::vector<BulletPlace> bulletsPlace = {	
		{ 0.0f, kBullet_Left },		//!< ��
		{ 0.0f, kBullet_Right }		//!< �E
	};

	if (isInvalid() || countEmptyBullets() < bulletsPlace.size())
	{
		return;
	}
	for each (BulletPlace obj in bulletsPlace)
	{	
		enumBullets([&](std::shared_ptr<CQuadPolygon> bullet_, size_t index_) -> BOOL {
			if ( (bullet_->getState() == eWaiting) && (bullet_->getPos().x < getPos().x) || 
				 (bullet_->getState() == eWaiting) && (bullet_->getPos().x > getPos().x) )
			{
				bullet_->setPos({ getPos().x + obj.pos, bullet_->getPos().y, bullet_->getPos().z, bullet_->getPos().w });
				bullet_->setState(eMoving);
				bullet_->setAngleZ(getAngleZ());
				bullet_->setForwardDirection(obj.dir + getAngleZ());
				return FALSE; //!< �񋓂𒆒f
			}
			return TRUE; //!< �񋓂𑱍s
		});
	}
}