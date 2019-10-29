/**
* @file CQuadPolygon.h
* @brief �|���S���E�N���X
* @author �D�ˁ@�엲
* @date ���t�i2018.07.27�j
*/
#pragma once

#include "stdafx.h"
#include "Common3DType.h"

// p
struct ColSet
{
	XMFLOAT4 pos;
	XMFLOAT2 size;
};

struct PartiallyCol
{
	ColSet head;
	ColSet right;
	ColSet left;
	ColSet foot;
};

/*! @class CQuadPolygon
@brief  �|���S���E�N���X
*/

class CQuadPolygon
{
protected:
	// Direct3D
	ID3D11DeviceContext * m_pDeviceContext = NULL;	//!< �f�o�C�X�E�R���e�L�X�g
	D3D11_VIEWPORT			m_viewPort[1];			//!< �r���[�|�[�g
	ID3DBlob *					m_pBlobVS = NULL;	//!< �u���u�Ƃ̓V�F�[�_�[�̉�݂����Ȃ���
	ID3D11VertexShader*	m_pVertexShader = NULL;		//!< effect�ł͂Ȃ��A�ʂɒ��_�V�F�[�_
	ID3D11InputLayout*		m_pInputLayout = NULL;	//!< ���̓��C�A�E�g
	ID3D11PixelShader*	m_pPixelShader = NULL;		//!< effect�ł͂Ȃ��A�ʂɃs�N�Z���V�F�[�_�[
	std::vector<ID3D11Buffer*>	m_pVertexBuffer;	//!< ���_�o�b�t�@
	ID3D11Buffer*		m_pConstantBuffer = NULL;	//!< �A�v�������V�F�[�_�[�˂��� �f�B�t���[�Y��n�����߂̒萔�o�b�t�@

	// Direct3D�ȊO
	XMFLOAT2					m_VBLeftTop		= { 0.0f, 0.0f };	//!< ���_�o�b�t�@�@��`�@����
	XMFLOAT2					m_VBRightBottom	= { 0.0f, 0.0f };	//!< ���_�o�b�t�@�@��`�@�E��
	XMFLOAT2					m_VBSize		= { 0.0f, 0.0f };	//!< ���_�o�b�t�@�@�T�C�Y
	XMFLOAT2					m_originalSize	= { 0.0f, 0.0f };	//!< ���̃T�C�Y

	Position<XMFLOAT4>	m_position;						//!< �p��<�ʒu ���� �X�P�[�� >
	XMFLOAT4			m_speed;						// �X�s�[�h
	FLOAT				m_gravityScale = 0.0f;			// �d��
	FLOAT				m_forwardDirectionOfBullet;		//!< �e�ۂ̔��ˎ��̐i�s����
	XMFLOAT4X4		m_mFinalWorld;		//!< �ŏI�I�ȃ��[���h�s��i���̎p���Ń����_�����O����j
	XMFLOAT4X4		m_matTran;			//!< ���s�ړ��s��
	XMFLOAT4X4		m_matPitch;			//!< ��]�s��@�s�b�`
	XMFLOAT4X4		m_matYaw;			//!< ��]�s��@���[
	XMFLOAT4X4		m_matRoll;			//!< ��]�s��@���[��
	XMFLOAT4X4		m_matScale;			//!< �X�P�[���s��
	size_t			m_animIndex = 0;	//!< �A�j���[�V�����̃e�N�Z���̔z��i0�`3�j
	BOOL			m_active = TRUE;	//!< ������
	eObjectState	m_state = eWaiting;	//!< �ړ� / �ҋ@
	FLOAT			m_moveQuantity;		//!< �ړ���
	BOOL			m_damaged = FALSE;
	int				m_fadeOutFrames = 600;

	// init �̏ڍ�
	void createVertexShader(ID3D11Device* pDevice_, LPCWSTR shaderName_);
	void createVertexInputLayout(ID3D11Device* pDevice_);
	void createPixelShader(ID3D11Device* pDevice_, LPCWSTR shaderName_);
	void createVertexBuffer(ID3D11Device* pDevice_, XMFLOAT2 size_, std::vector<QuadrangleTexel>	texels);
	void createConstBuffer(ID3D11Device* pDevice_);

public:
	static std::unique_ptr<CQuadPolygon> create(
		ID3D11Device*			pDevice_,		//!< �f�o�C�X
		ID3D11DeviceContext*	pDeviceContext_,//!< �f�o�C�X�R���e�L�X�g
		D3D11_VIEWPORT			viewPort_[],	//!< �r���[�|�[�g
		LPCWSTR					shaderName_,	//!< �V�F�[�_�[�v���O����
		XMFLOAT4				position_,		//!< �E�B���h�E�̈ʒu
		XMFLOAT2				size_,			//!< �X�v���C�g�̑傫��
		std::vector<QuadrangleTexel>	texels);		//!< �e�N�Z���̔z��
	CQuadPolygon();
	~CQuadPolygon();
	virtual void init(
		ID3D11Device*			pDevice_,		//!< �f�o�C�X
		ID3D11DeviceContext*	pDeviceContext_,//!< �f�o�C�X�R���e�L�X�g
		D3D11_VIEWPORT			viewPort_[],	//!< �r���[�|�[�g
		LPCWSTR					shaderName_,	//!< �V�F�[�_�[�v���O����
		XMFLOAT4				position_,		//!< �E�B���h�E�̈ʒu
		XMFLOAT2				size_,			//!< �X�v���C�g�̑傫��
		std::vector<QuadrangleTexel>	texels);		//!< �e�N�Z���̔z��
	/**
	* �A�N�V����
	*/
	virtual void render(
		XMFLOAT4X4 matView_,
		XMFLOAT4X4 matProj_,
		std::function<void(ID3D11DeviceContext* pDeviceContext_)> callbackTextureProc_,
		size_t texelIndex_ = 0,
		XMFLOAT4 diffuse_ = { 0, 0, 0, 0 });
	virtual BOOL collision(XMFLOAT4 rivalPos_, FLOAT range_);
	virtual BOOL collision(XMFLOAT4 pos1_, XMFLOAT4 pos2_, FLOAT range_);
	virtual BOOL collision(XMFLOAT4 rivalPos_, FLOAT range_, eCheckAxis check_);
	virtual BOOL collision(FLOAT pos1_, FLOAT pos2_, FLOAT range_);
	virtual BOOL collisionRect(XMFLOAT4 rivalPos_, XMFLOAT2 size_);
	virtual BOOL collisionRect(XMFLOAT4 pos1_, XMFLOAT4 pos2_, XMFLOAT2 size_);
	virtual FLOAT colDifference(XMFLOAT4 pos_, XMFLOAT2 size_, eCheckAxis check_);
	void computeMatrixFromPos(void);
	void release();
	void reset(XMFLOAT4 pos_) {
		setActive(TRUE);
		setState(eWaiting);
		setPos(pos_);
	}
	/**
	* ���
	*/
	BOOL isInvalid()
	{
		if (outOfWindow() || !m_active)
		{
			return TRUE;
		}
		return FALSE;
	}
	BOOL outOfWindow(void) {
		FLOAT left		= m_position.pos.x - m_VBSize.x / 2;
		FLOAT right		= m_position.pos.x + m_VBSize.x / 2;
		FLOAT top		= m_position.pos.y + m_VBSize.y / 2;
		FLOAT bottom	= m_position.pos.y - m_VBSize.y / 2;

		if ((left < WINDOW_LEFT) || (right > WINDOW_RIGHT) || (top > WINDOW_TOP) || (bottom < WINDOW_BOTTOM))
		{
			return TRUE;
		}
		return FALSE;
	}
	/**
	* �v���p�e�B�@�A�N�Z�X
	*/
	BOOL getActive(void)				{ return m_active; }
	void setActive(BOOL cond_)			{ m_active = cond_; }
	eObjectState getState()				{ return m_state; }
	void setState(eObjectState state_)	{ m_state = state_; }
	void setDamaged(BOOL damaged_)		{ m_damaged = damaged_; }
	void setScale(FLOAT scale_) {
		m_position.scale = scale_;
		m_VBSize.x = m_originalSize.x * scale_;
		m_VBSize.y = m_originalSize.y * scale_;
	};
	XMFLOAT2 getSize()					{ return m_VBSize; }
	XMFLOAT4 getPos()			{ return m_position.pos; }
	void setPos(XMFLOAT4 pos_)	{ m_position.pos = pos_; }
	void offsetPos(XMFLOAT4 pos_)	{ m_position.offset(pos_); }
	void offsetPosInNormalRange(XMFLOAT4 pos_) {
		offsetPos(pos_);
		if (outOfWindow()) {
			offsetPos({ -pos_.x, -pos_.y, -pos_.z, pos_.w });
		}
	};
	void setSpeed(XMFLOAT4 spd_) { m_speed = spd_; }
	XMFLOAT4 getSpeed()const { return m_speed; }

	void setAngle(XMFLOAT3 degrees_)	{ m_position.setAngle(degrees_); }//!<  �y�����z
	FLOAT getAngleZ()					{ return m_position.roll; }
	void setAngleZ(FLOAT degree_)		{ m_position.roll = degree_; }
	void addAngle(XMFLOAT3 alpha_)		{
		m_position.setAngle({
			m_position.pitch += alpha_.x,
			m_position.yaw += alpha_.y,
			m_position.roll += alpha_.z
			});
	}
	void addAngleZ(FLOAT alpha_) {
		m_position.roll += alpha_;
		m_position.normalize();
	};
	FLOAT getForwardDirection()				{ return m_forwardDirectionOfBullet; }
	void setForwardDirection(FLOAT value_)	{ m_forwardDirectionOfBullet = value_; }

	size_t getNumOfVBs()				{ return m_pVertexBuffer.size(); }
	void setMoveQuantity(FLOAT alpha_)	{ m_moveQuantity = alpha_; }
	FLOAT getMoveQuantity(void)			{ return m_moveQuantity; }
};