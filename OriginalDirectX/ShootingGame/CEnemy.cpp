/**
 * @file CEnemy.cpp
 * @brief �G
 * @author �D�ˁ@�엲
 * @date ���t�i2017.02.14�j
 */

#include "stdafx.h"
#include "CEnemy.h"

/**
 * @fn std::unique_ptr<CEnemy> CEnemy::create(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, XMFLOAT4 position_, XMFLOAT2 size_, std::vector<QuadrangleTexel> texels)
 * @brief �C���X�^���X�𐶐��������� �y�N���X���\�b�h�z
 * @param pDevice_			�f�o�C�X
 * @param pDeviceContext_	�f�o�C�X�R���e�L�X�g
 * @param viewPort_[]		�r���[�|�[�g
 * @param shaderName_		�V�F�[�_�[�v���O����
 * @param position_			�E�B���h�E�̈ʒu
 * @param size_				�X�v���C�g�̑傫��
 * @param bulletTexelIndex_	�e�ۂ̃e�N�Z���̃C���f�b�N�X�i�v���[���[�Ƌ��L�j
 * @return					CEnemy�̃��j�[�N�|�C���^
 */
std::shared_ptr<CEnemy> CEnemy::create(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, XMFLOAT4 position_, XMFLOAT2 size_, int bulletTexelIndex_)
{
	std::shared_ptr<CEnemy> object = shared_ptr<CEnemy>(new CEnemy());
	object->init(pDevice_, pDeviceContext_, viewPort_, shaderName_, position_, size_, bulletTexelIndex_);
	return object;
}
/**
 * @fn void CEnemy::init(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, XMFLOAT4 position_, XMFLOAT2 size_, std::vector<QuadrangleTexel> texels)
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
void CEnemy::init(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, XMFLOAT4 position_, XMFLOAT2 size_, int bulletTexelIndex_)
{
	super::init(pDevice_, pDeviceContext_, viewPort_, shaderName_, position_, size_, kTexelEnemys, bulletTexelIndex_); //!< �X�[�p�[�N���X�̃��\�b�h�����s
	m_moveQuantity = -0.528f * 1.75f;
	enumBullets(
		[=](std::shared_ptr<CQuadPolygon> bullet_, size_t index_) -> BOOL {
		bullet_->setMoveQuantity(-2.5);
		return TRUE; //!< �񋓂𑱍s
	});
}

CEnemy::CEnemy()
{
}

CEnemy::~CEnemy()
{
}

/**
 * @fn BOOL CEnemy::stepAnimation (BOOL enable_)
 * @brief �A�j���[�V����
 * @param enable_	�A�j���[�V�����̗L����
 * @return			�p���E���~
 */
void CEnemy::stepAnimation (BOOL enable_)
{
	super::stepAnimation(enable_, kTexelEnemys); //!< �X�[�p�[�N���X�̃��\�b�h�����s
}

/**
 * @fn void CEnemy::render(XMFLOAT4X4	matView_, XMFLOAT4X4 matProj_)
 * @brief �����_�����O
 * @param matView_	�r���[�s��
 * @param matProj_	�v���W�F�N�V�����s��
 * @return			����
 */
void CEnemy::render(XMFLOAT4X4	matView_, XMFLOAT4X4 matProj_, std::function<void(ID3D11DeviceContext* pDeviceContext_)> callbackTextureProc_)
{
	if (!outOfWindow())
	{
		super::render(matView_, matProj_, callbackTextureProc_, m_animIndex); //!< �X�[�p�[�N���X�̃��\�b�h�����s
	}
}

/**
 * @fn void CEnemy::shot(void)
 * @brief �e�ۂ𔭎�
 * @param	����
 * @return	����
 */
void CEnemy::shot(void)
{
	std::vector<FLOAT> courses = { -20.0f, 0.0f, 20.0f };
	super::shot(courses); //!< �X�[�p�[�N���X�̃��\�b�h�����s
}