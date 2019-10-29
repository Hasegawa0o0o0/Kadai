/**
* @file CSpaceship.cpp
* @brief �X�y�[�X�V�b�v�i���ۃN���X�j
* @author �D�ˁ@�엲
* @date ���t�i2017.02.14�j
*/

#include "stdafx.h"
#include "CSpaceship.h"	

CSpaceship::CSpaceship()
{
}


CSpaceship::~CSpaceship()
{
}

/**
* @fn void CSpaceship::init(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, XMFLOAT4 position_, XMFLOAT2 size_, std::vector<QuadrangleTexel> texels)
* @brief �C���X�^���X��������
* @param pDevice_			�f�o�C�X
* @param pDeviceContext_	�f�o�C�X�R���e�L�X�g
* @param viewPort_[]		�r���[�|�[�g
* @param shaderName_		�V�F�[�_�[�v���O����
* @param position_			�E�B���h�E�̈ʒu
* @param size_				�X�v���C�g�̑傫��
* @param texels			�e�N�Z���̔z��
* @param bulletTexelIndex_		�e�ۂ̃e�N�Z���̃C���f�b�N�X�i�G�Ƌ��L�j
* @return					����
*/
void CSpaceship::init(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, XMFLOAT4 position_, XMFLOAT2 size_, std::vector<QuadrangleTexel> texels, int bulletTexelIndex_)
{
	m_hp = kMaxHP;
	super::init(pDevice_, pDeviceContext_, viewPort_, shaderName_, position_, size_, texels);	//!< �X�[�p�[�N���X�̃��\�b�h�����s
	m_bulletTexelIndex = bulletTexelIndex_;	//!<  Player or Enemy
	
	m_pExplosion = CExplosion::create(pDevice_, pDeviceContext_, viewPort_, HLSL_PlaneHLSL,
		{ 0.0f, 0.0f, 0.0f, 0.0f },	//!< �ʒu
		kExplosionSize,				//!< �T�C�Y
		kTexelExplosions,
		kExplosionTexelPauseFrames);	//!< �e�N�X�`���̐؂�ւ���^�C�~���O�i�t���[�����j

	for (size_t i = 0; i < _countof(m_pBullets); i++)
	{
		m_pBullets[i] = shared_ptr<CQuadPolygon>(new CQuadPolygon());
	}
	enumBullets (
		[=](std::shared_ptr<CQuadPolygon> bullet_, size_t index_) -> BOOL {
		bullet_->init (
			pDevice_, pDeviceContext_, viewPort_, shaderName_,
			computeBulletPos(index_),
			kBulletSize,
			kTexelBullets
		);
		bullet_->setState (eWaiting);		
		bullet_->setScale (1.0f);
		bullet_->setMoveQuantity(2.5);
		return TRUE; //!< �񋓂𑱍s
	});

	// �e�N�Z��
	m_pBulletTex = CTexture::create(pDevice_, Tex_Bullet);	//!< �e�N�Z��
	m_pExplosionTex = CTexture::create(pDevice_, Tex_Explosion);	//!< �e�N�Z��
}

/**
* @fn void CSpaceship::render(XMFLOAT4X4	matView_, XMFLOAT4X4 matProj_, size_t texelIndex_, XMFLOAT4 diffuse_)
* @brief �����_�����O
* @param matView_	�r���[�s��
* @param matProj_	�v���W�F�N�V�����s��
* @param texelIndex_	�e�N�Z���E�C���f�b�N�X
* @param v4Diffuse_	�f�B�t���[�Y
* @return			����
*/
void CSpaceship::render(XMFLOAT4X4 matView_, XMFLOAT4X4 matProj_, std::function<void(ID3D11DeviceContext* pDeviceContext_)> callbackTextureProc_, size_t texelIndex_, XMFLOAT4 v4Diffuse_)
{
	enumBullets (	
		[=](std::shared_ptr<CQuadPolygon> bullet_, size_t index_) -> BOOL {
		bullet_->outOfWindow() ? bullet_->reset(computeBulletPos(index_)) : NULL;
		if (bullet_->getState() == eMoving)
		{
			FLOAT dir = bullet_->getForwardDirection();
			bullet_->offsetPos (
				ComputePosByDirectionZ (
					{
						0.0f,						// x
						bullet_->getMoveQuantity(),	// y
						0.0f,						// z
						0.0f						// w
					},
					dir
				));
			bullet_->render (matView_, matProj_,
				[&](ID3D11DeviceContext* pDeviceContext_) -> void {
				m_pBulletTex->setup(pDeviceContext_);
			}, m_bulletTexelIndex);
		}
		else {
			bullet_->reset(computeBulletPos(index_));
		}
		return TRUE;	//!< �񋓂𑱍s
	});

	if (m_hp < kMaxHP)
	{
		super::render(matView_, matProj_, callbackTextureProc_, texelIndex_, {1, 0, 0, 0});	//!< �X�[�p�[�N���X�̃��\�b�h�����s
	}
	else {
		super::render(matView_, matProj_, callbackTextureProc_, texelIndex_);				//!< �X�[�p�[�N���X�̃��\�b�h�����s
	}
	m_pExplosion->setPos(getPos());
	m_pExplosion->render(matView_, matProj_,
		[&](ID3D11DeviceContext* pDeviceContext_) -> void {
		m_pExplosionTex->setup(pDeviceContext_);
	});
}

/**
* @fn void CSpaceship::shot(std::vector<FLOAT> courses_)
* @brief �e�ۂ̃V���b�g
* @param	courses_	���˕���
* @return					����
*/
void CSpaceship::shot(std::vector<FLOAT> courses_)
{
	if (isInvalid() || countEmptyBullets() < courses_.size())
	{
		return;
	}
	for each (FLOAT course in courses_)
	{
		enumBullets(
			[&](std::shared_ptr<CQuadPolygon> bullet_, size_t index_) -> BOOL {
			if (bullet_->getState() == eWaiting)
			{
				bullet_->setState(eMoving);
				bullet_->setForwardDirection(course + getAngleZ());
				return FALSE; //!< �񋓂𒆒f
			}
			return TRUE; //!< �񋓂𑱍s												
		});
	}
}

/**
* @fn BOOL CSpaceship::collisionBullet(XMFLOAT4 rivalPos_, FLOAT range_)
* @brief �Փ�
* @param	rivalPos_	�ʒu
* @param	range_	�Փ˂͈̔�
* @return			����
*/
BOOL CSpaceship::collisionBullet(XMFLOAT4 rivalPos_, FLOAT range_)
{
	BOOL hit = FALSE;
	enumBullets(
		[&](std::shared_ptr<CQuadPolygon> bullet_, size_t index_) -> BOOL {
		if (bullet_->getState() == eMoving)
		{
			if (bullet_->collision(rivalPos_, bullet_->getPos(), range_))
			{
				hit = TRUE;
				bullet_->reset(computeBulletPos(index_));
				return TRUE; //!< �񋓂𑱍s
			}
		}
		return TRUE; //!< �񋓂𑱍s
	});
	return hit;
}

/**
* @fn void CSpaceship::resetAllBullets()
* @brief ���ׂĂ̒e�ۂ�������Ԃɂ���
* @param	����
* @return	����
*/
void CSpaceship::resetAllBullets()
{
	enumBullets(
		[&](std::shared_ptr<CQuadPolygon> bullet_, size_t index_) -> BOOL {
		bullet_->reset(computeBulletPos(index_));
		return TRUE; //!< �񋓂𑱍s
	});	
}

/**
* @fn void CSpaceship::enumBullets(std::function<BOOL(std::shared_ptr<CQuadPolygon>, size_t)> callbackEnumeProc_)
* @brief �e�ۂ̗�
* @param	callbackEnumeProc_	�R�[���o�b�N<�����_��>
* @return	����
*/
void CSpaceship::enumBullets(std::function<BOOL(std::shared_ptr<CQuadPolygon>, size_t)> callbackEnumeProc_)
{
	for (size_t i = 0; i < _countof (m_pBullets); i++)
	{
		if (m_pBullets[i] != NULL)
		{
			if (callbackEnumeProc_ (m_pBullets[i], i) == FALSE)
			{
				break; //!< �񋓂𒆒f
			}
		}
	}
}

/**
* @fn void CSpaceship::release()
* @brief �����[�X
* @param	����
* @return	����
*/
void CSpaceship::release()
{
	m_pExplosion->release();
	m_pBulletTex->release();
	m_pExplosionTex->release();
	enumBullets(
		[&](std::shared_ptr<CQuadPolygon> bullet_, size_t index_) -> BOOL {
		SAFE_release(bullet_);
		return TRUE; //!< �񋓂𑱍s												
	});
	super::release();	//!< �X�[�p�[�N���X�̃��\�b�h�����s
}