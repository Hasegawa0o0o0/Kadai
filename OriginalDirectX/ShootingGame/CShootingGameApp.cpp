/**
 * @file CShootingGameApp.cpp
 * @brief �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
 * @author �D�ˁ@�엲
 * @date ���t�i2017.02.14�j
 */

#include "stdafx.h"
#include "CShootingGameApp.h"


CShootingGameApp::CShootingGameApp()
{
}


CShootingGameApp::~CShootingGameApp()
{
}

/**
 * @fn void CShootingGameApp::initCameraInfo()
 * @brief �J�����̐ݒ�
 * @param	����
 * @return	����
 */
void CShootingGameApp::initCameraInfo()
{
	m_vEyePt	= XMFLOAT3{ 0.0f, 0.0f,  -582.0f };	//!< �J�����i���_�j�ʒu
	m_vLookatPt	= XMFLOAT3{ 0.0f, 0.0f,     0.0f };	//!< �����ʒu
	m_vUpVec	= XMFLOAT3{ 0.0f, 1.0f,     0.0f };	//!< ����ʒu
	m_angle		= (FLOAT)XM_PI / 4;					//!< ����p
	m_aspect	= ASPECT;							//!< �A�X�y�N�g��
	m_near		= 0.1f;								//!< �O���N���b�v
	m_far		= 1000.0f;							//!< ����N���b�v
}

/**
* @fn bool CShootingGameApp::createSprites(void)
* @brief �X�v���C�g�̐���
* @param	����
* @return	�����E���s
*/
bool CShootingGameApp::createSprites(void)
{
	//eScrollMode scrollMode = eHorizontal;	//!< �X�N���[���������
	eScrollMode scrollMode = eVirtical;		//!< �X�N���[���������
	super::createSprites(); //!< �X�[�p�[�N���X�̃��\�b�h�����s
	try {

		/**
		* �I�[�v�j���O�̃^�C�g���𐶐�
		*/
		vector <QuadrangleTexel>  singleTexels = {
			QuadrangleTexel{ { 0, 1.0f },{ 0, 0.0f },{ 1, 1.0f },{ 1, 0.0f } }	//!< �e�N�Z���̔z�񂪈�̔z��
		};
		m_pTitle = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, Tex_Title,
			{ 0.0f, 0.0f, 0.0f, 0.0f },	//!< �X�v���C�g�̈ʒu
			kSpriteScreenkSize,			//!< �X�v���C�g�̃T�C�Y
			singleTexels);				//!< �e�N�Z���̔z��
		m_pGameOver = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, Tex_GameOver,
			{ 0.0f, 0.0f, 0.0f, 0.0f },	//!< �X�v���C�g�̈ʒu
			kSpriteScreenkSize,			//!< �X�v���C�g�̃T�C�Y
			singleTexels);				//!< �e�N�Z���̔z��


		/**
		* �w�i�̃^�C�g���𐶐�
		*/
		m_pBack = CScroll::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_Background, Tex_Back,
			{ 0.0f, 0.0f, 0.0f, 0.0f },		//!< �X�v���C�g�̈ʒu
			kSpriteScreenkSize,				//!< �X�v���C�g�̃T�C�Y
			singleTexels,					//!< �e�N�Z���̔z��
			scrollMode);
		m_pMiddle = CScroll::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_Background, Tex_Middle,
			{ 0.0f, 0.0f, 0.0f, 0.0f },		//!< �X�v���C�g�̈ʒu
			kSpriteScreenkSize,				//!< �X�v���C�g�̃T�C�Y
			singleTexels,					//!< �e�N�Z���̔z��
			scrollMode);
		m_pFront = CScroll::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_Background, Tex_Front,
			{ 0.0f, 0.0f, 0.0f, 0.0f },		//!< �X�v���C�g�̈ʒu
			kSpriteScreenkSize,				//!< �X�v���C�g�̃T�C�Y
			singleTexels,					//!< �e�N�Z���̔z��
			scrollMode);

		createSpaceship();	// �v���[���ƓG�̐���
		return true;
	}
	catch (LPCWSTR str)
	{
		MessageBox(0, str, NULL, MB_OK);
		return false;
	}
}

/**
 * @fn bool CShootingGameApp::createSpaceship(void)
 * @brief �X�v���C�g�̐���
 * @param	����
 * @return	�����E���s
 */
bool CShootingGameApp::createSpaceship(void)
{
	enumEnemys(
		[&](std::shared_ptr<CEnemy> enemy_, size_t index_) -> BOOL {
		SAFE_release(enemy_);
		return TRUE; //!< �񋓂𑱍s											
	});
	SAFE_release(m_pPlayer);

	m_pPlayer = CPlayer::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, /*Tex_Spaceship,*/
		{ 0.0f, -180.0f, 0.0f, 0.0f },	//!< �X�v���C�g�̈ʒu
		kCharSpriteSize,				//!< �X�v���C�g�̃T�C�Y
		kTexelPlayerBulletIndex);			//!< �e�N�Z���̔z��̃C���f�b�N�X�i�A�j���[�V�����̂��߁j
	m_pPlayer->setState(eMoving);
	m_pPlayer->setScale(1.0f);

	m_activeEnemys = 0;
	XMFLOAT4 enemyPos = { -130.0f , 301.0f , 0.0f, 0.0f };		//!<  �y�X�e�b�v4�z�G
	for (size_t i = 0; i < _countof(m_pEnemys); i++)
	{
		m_pEnemys[i] = CEnemy::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, /*Tex_Spaceship,*/
			enemyPos,				//!< �ʒu
			kCharSpriteSize,		//!< �T�C�Y
			kTexelEnemyBulletIndex);	//!< �o���b�g�e�N�Z���̔z��C���f�b�N�X
		m_pEnemys[i]->setState(eMoving);
		enemyPos.x += m_pEnemys[i]->getSize().x + 45.0f;
	}
	m_pPlayerTex = CTexture::create(m_pDevice, Tex_Spaceship);	//!< �e�N�Z��
	m_pEnemyTex = CTexture::create(m_pDevice, Tex_Spaceship);	//!< �e�N�Z��

	return true;
}

/**
 * @fn void CShootingGameApp::doOpenning()
 * @brief �I�[�v�j���O
 * @param	����
 * @return	����
 */
void CShootingGameApp::doOpenning ()
{
	m_gameStatus = ePlaying;

	m_pTitle->setAngle({ 0.0000f, 0.0000f, 0.0000f });
	if (m_pDirectInput->isKeyPressed(DIK_X)) {
		m_gameStatus = ePlaying;
	}
}

/**
 * @fn void CShootingGameApp::doPlaying()
 * @brief �v���[��
 * @param	����
 * @return	����
 */
void CShootingGameApp::doPlaying ()
{
	// �y�X�e�b�v4�z
	/**
	* �L�����N�^�[�̃A�j���[�V����
	*/
	m_frameCounter++;
	m_frameCounter = m_frameCounter > 65536 ? 0 : m_frameCounter;

	m_pPlayer->stepAnimation(m_frameCounter % kTexelIntervalFrames == 0);
	enumEnemys(
		[&](std::shared_ptr<CEnemy> enemy_, size_t index_) -> BOOL {
		enemy_->stepAnimation(m_frameCounter % kTexelIntervalFrames == 0);
		return TRUE; //!< �񋓂𑱍s
	});
	m_pBack->scroll(-0.2f);
	m_pMiddle->scroll(-0.4f);
	m_pFront->scroll(-0.8f);
	/**
	* �v���[���[�̐���
	*/
	if (m_pDirectInput->isKeyPressed(DIK_LEFT))		m_pPlayer->offsetPosInNormalRange({ -kPlayerQuantity,  0.00f, 0.0f, 0.0f });
	if (m_pDirectInput->isKeyPressed(DIK_RIGHT))	m_pPlayer->offsetPosInNormalRange({  kPlayerQuantity,  0.00f, 0.0f, 0.0f });
	if (m_pDirectInput->isKeyPressed(DIK_UP))		m_pPlayer->offsetPosInNormalRange({ 0.0f,  kPlayerQuantity, 0.0f, 0.0f });
	if (m_pDirectInput->isKeyPressed(DIK_DOWN))		m_pPlayer->offsetPosInNormalRange({ 0.0f, -kPlayerQuantity, 0.0f, 0.0f });

	if (m_pDirectInput->isKeyPressed(DIK_V))		m_pPlayer->addAngleZ( 5.0);
	if (m_pDirectInput->isKeyPressed(DIK_N))		m_pPlayer->addAngleZ(-5.0);
	if (m_pDirectInput->isPressedOnce(DIK_B))		m_pPlayer->shot();

	if (m_pDirectInput->isLeftButtonClicked())		m_pPlayer->shot();

	/**
	* �y�X�e�b�v5�z�G�̑���
	*/
	m_activeEnemys = 0;
	enumEnemys(
		[&](std::shared_ptr<CEnemy> enemy_, size_t index_) -> BOOL {
		prepareFrame(enemy_, index_);
		return TRUE; //!< �񋓂𑱍s
	});
	if (m_activeEnemys <= 0)
	{
		m_gameStatus = eGameClear;
	}
}

/**
* @fn void CShootingGameApp::prepareFrame (shared_ptr<CEnemy> pEnemy_, int i)
* @brief �G�L�����N�^�̂̑���
* @param	pEnemy_		�G
* @param	i			����
* @return				����
*/
void CShootingGameApp::prepareFrame(shared_ptr<CEnemy> pEnemy_, int i)
{
	/**
	* �������ɓG�̒e�ƃv���[���Ƃ̏Փ˂��`�F�b�N����.
	*/
	if (pEnemy_->collisionBullet(m_pPlayer->getPos(), (kCharSpriteSize.x / 2 + kBulletSize.x / 2)))
	{
		if (m_pPlayer->receiveDamage())
		{
			m_pPlayer->explode();
			m_pPlayer->setActive(FALSE);
			m_pPlayer->setDamaged(TRUE);
		}
	}

	/**
	* �������ɒe�ƒe�̏Փ�
	*/
	pEnemy_->enumBullets(
		[=](std::shared_ptr<CQuadPolygon> enemyBullet_, size_t index_) -> BOOL {
			if (enemyBullet_->getState() == eMoving)
			{
				if (m_pPlayer->collisionBullet(enemyBullet_->getPos(), (kCharSpriteSize.x / 2 + kBulletSize.x / 2)))
				{
					enemyBullet_->reset(pEnemy_->computeBulletPos(index_));
				}
			}
		return TRUE; //!< �񋓂𑱍s												
		}
	);

	/**
	* �G���������Ă���
	*/
	if (pEnemy_->getActive())
	{
		pEnemy_->offsetPos(ComputePosByDirectionZ({ 0.0f, -kEnemyQuantity, 0.0f, 0.0f }, 0.0f));
		pEnemy_->shotOpt(m_frameCounter % kIntervalShot == 0);
		if (pEnemy_->getPos().y < WINDOW_BOTTOM)
		{
			pEnemy_->setPos({pEnemy_->getPos().x, 301.0f, 0.0f, 0.0});
		}

		/**
		* �v���[���[�ɓG�Ƃ̏Փ˂��`�F�b�N������.
		*/
		if (m_pPlayer->getActive())
		{
			if (m_pPlayer->collisionBullet(pEnemy_->getPos(), (kCharSpriteSize.x / 2 + kBulletSize.x / 2)))
			{
				if (pEnemy_->receiveDamage())
				{
					pEnemy_->explode();
					pEnemy_->setActive(FALSE);
					pEnemy_->setDamaged(TRUE);
				}
			}
		}

		/**
		* �G�Ƀv���[���[�Ƃ̏Փ˂��`�F�b�N������.
		*/
		if (pEnemy_->collision(m_pPlayer->getPos(), (kCharSpriteSize.x / 2 + kBulletSize.x / 2)))
		{
			if (m_pPlayer->receiveDamage())
			{
				m_pPlayer->explode();
				m_pPlayer->setActive(FALSE);
				m_pPlayer->setDamaged(TRUE);
			}
		}
	}
	
	/**
	* �v���[���[�̔���������������Q�[���I�[�o�[.
	*/
	if (m_pPlayer->isExplosionCompleted())
	{
		m_gameStatus = eGameOver;
	}
	if (pEnemy_->getActive())
	{
		m_activeEnemys++;
	}
}

/**
* @fn void CShootingGameApp::isActiveEnemys()
* @brief ���ׂĂ̓G���������Ă��邩
* @param	����
* @return	����
*/
BOOL CShootingGameApp::isActiveEnemys()
{
	return FALSE;
}

/**
 * @fn void CShootingGameApp::doGameClear()
 * @brief �Q�[���N���A
 * @param	����
 * @return	����
 */
void CShootingGameApp::doGameClear()
{
	MessageBox(0, L"GameClear", NULL, MB_OK);
	createSpaceship();
	m_gameStatus = eOpenning;
}

/**
 * @fn void CShootingGameApp::doGameOver()
 * @brief �Q�[���I�[�o�[
 * @param	����
 * @return	����
 */
void CShootingGameApp::doGameOver()
{
	//�f�o�b�O
	createSpaceship();
	m_gameStatus = eOpenning;
}

/**
 * @fn void CShootingGameApp::doEnding()
 * @brief �G���f�B���O
 * @param	����
 * @return	����
 */
void CShootingGameApp::doEnding()
{
}

/**
 * @fn void CShootingGameApp::renderSprites(XMFLOAT4X4 matView_, XMFLOAT4X4 matProj_)
 * @brief �����_�[
 * @param	matView_	�r���[�s��
 * @param	matProj_	�v���W�F�N�V�����s��
 * @return				����
 */
void CShootingGameApp::render(XMFLOAT4X4 matView_, XMFLOAT4X4 matProj_)
{
	switch (m_gameStatus)
	{
	case eOpenning:
		m_pTitle->render(matView_, matProj_);
		break;
	case ePlaying:
		// �����`�悷�鏇�Ԃƌ��ʂ��m�F���邱��
		enumEnemys(
			[&](std::shared_ptr<CEnemy> enemy_, size_t index_) -> BOOL {
			enemy_->render(matView_, matProj_,
				[&](ID3D11DeviceContext* pDeviceContext_) -> void {
				m_pEnemyTex->setup(pDeviceContext_);
			});
			return TRUE; //!< �񋓂𑱍s	
		});
		m_pPlayer->render(matView_, matProj_,
			[&](ID3D11DeviceContext* pDeviceContext_) -> void {
			m_pPlayerTex->setup(pDeviceContext_);
		});

		m_pFront->render(matView_, matProj_);
		m_pMiddle->render(matView_, matProj_);
		m_pBack->render(matView_, matProj_);
		break;
	case eGameOver:
		m_pGameOver->render(matView_, matProj_);
		break;
	default:
		break;
	}
}

/**
* @fn void CShootingGameApp::enumEnemys(std::function<BOOL(std::shared_ptr<CEnemy>, size_t)> callbackEnumeProc_)
* @brief �G��񋓂���
* @param	callbackEnumeProc_	�R�[���o�b�N<�����_��>
* @return	����
*/
void CShootingGameApp::enumEnemys(std::function<BOOL(std::shared_ptr<CEnemy>, size_t)> callbackEnumeProc_)
{
	for (size_t i = 0; i < _countof(m_pEnemys); i++)
	{
		if (m_pEnemys[i] != NULL)
		{
			if (callbackEnumeProc_(m_pEnemys[i], i) == FALSE)
			{
				break; //!< �񋓂𒆒f
			}
		}
	}
}

/**
* @fn void CShootingGameApp::release()
* @brief ���
* @param	����
* @return	����
*/
void CShootingGameApp::release()
{
	super::release();
	m_pTitle->release();
	m_pGameOver->release();
	m_pBack->release();
	m_pMiddle->release();
	m_pFront->release();
	m_pPlayer->release();
	enumEnemys(
		[&](std::shared_ptr<CEnemy> enemy_, size_t index_) -> BOOL {
		enemy_->release();
		return TRUE; //!< �񋓂𑱍s	
	});
	m_pPlayerTex->release();
	m_pEnemyTex->release();	
}