/**
 * @file CCamera.cpp
 * @brief �J����
 * @author �D�ˁ@�엲
 * @date ���t�i2017.02.14�j
 */

#include "stdafx.h"
#include "CCamera.h"


CCamera::CCamera ()
{
}


CCamera::~CCamera ()
{
}

/**
 * @fn void CCamera::init(XMFLOAT3 vEyePt_, XMFLOAT3 vLookatPt_, XMFLOAT3 vUpVec_, FLOAT	angle_, FLOAT	aspect_, FLOAT	near_, FLOAT	far_)
 * @brief ������
 * @param vEyePt_		�J�����i���_�j�ʒu
 * @param vLookatPt_	�����ʒu
 * @param vUpVec_		����ʒu
 * @param angle_		����p
 * @param aspect_		�A�X�y�N�g��
 * @param near_			�O���N���b�v
 * @param far_			����N���b�v
 * @return				����
 */
void CCamera::init(XMFLOAT3 vEyePt_, XMFLOAT3 vLookatPt_, XMFLOAT3 vUpVec_, FLOAT	angle_, FLOAT	aspect_, FLOAT	near_, FLOAT	far_)
{
	m_vEyePt	= vEyePt_;		//!< �J�����i���_�j�ʒu
	m_vLookatPt	= vLookatPt_;	//!< �����ʒu
	m_vUpVec	= vUpVec_;		//!< ����ʒu
	m_angle		= angle_;		//!< ����p
	m_aspect	= aspect_;		//!< �A�X�y�N�g��
	m_near		= near_;		//!< �O���N���b�v
	m_far		= far_;			//!< ����N���b�v
	XMStoreFloat4x4(&m_matView, XMMatrixIdentity());
	XMStoreFloat4x4(&m_matProj, XMMatrixIdentity());
	update();
}

/**
 * @fn void CCamera::update()
 * @brief �r���[�g�����X�t�H�[���A�v���W�F�N�V�����g�����X�t�H�[���̍X�V
 * @param	����
 * @param	����
 * @return	����
 */
void CCamera::update()
{
	/**
	 * �r���[�g�����X�t�H�[���i���_���W�ϊ��j
	 */
	XMStoreFloat4x4(&m_matView, XMMatrixLookAtLH(
		XMLoadFloat3(&m_vEyePt),	//!< �J�����i���_�j�ʒu
		XMLoadFloat3(&m_vLookatPt),	//!< �����ʒu
		XMLoadFloat3(&m_vUpVec)));	//!< ����ʒu
	/**
	 * �v���W�F�N�V�����g�����X�t�H�[���i�ˉe�ϊ��j
	 */
	XMStoreFloat4x4(&m_matProj, XMMatrixPerspectiveFovLH(
		m_angle,	//!< ����p
		m_aspect,	//!< �A�X�y�N�g��
		m_near,		//!< �O���N���b�v
		m_far));	//!< ����N���b�v
}
