/**
* @file CSingleSprite.cpp
* @brief �e�ہE�N���X
* @author �D�ˁ@�엲
* @date ���t�i2018.07.23�j
*/
#include "stdafx.h"
#include "CSingleSprite.h"

//!< �y�N���X�ϐ��z
ID3D11SamplerState*			CSingleSprite::g_pSampleLinear	= NULL;			//!< �y�N���X�ϐ��z�e�N�X�`���[�̃T���v���[
ID3D11ShaderResourceView*	CSingleSprite::g_pTexture		= NULL;			//!< �y�N���X�ϐ��z�e�N�X�`���[

/**
* @fn std::unique_ptr<CSingleSprite> CSingleSprite::create(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, LPCWSTR textureName_, XMFLOAT4 position_, XMFLOAT2 size_, std::vector<UVCoord> uvArray_)
* @brief �C���X�^���X�𐶐��������� �y�N���X���\�b�h�z
* @param pDevice_			�f�o�C�X
* @param pDeviceContext_	�f�o�C�X�R���e�L�X�g
* @param viewPort_[]		�r���[�|�[�g
* @param shaderName_			�V�F�[�_�[�v���O����
* @param textureName_		�摜�t�@�C��
* @param position_			�E�B���h�E�̈ʒu
* @param size_				�X�v���C�g�̑傫��
* @param uvArray_			������UV�z��
* @return					CSingleSprite�̃��j�[�N�|�C���^
*/
std::unique_ptr<CSingleSprite> CSingleSprite::create(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, LPCWSTR textureName_, XMFLOAT4 position_, XMFLOAT2 size_, std::vector<UVCoord>	uvArray_)
{
	std::unique_ptr<CSingleSprite> object = unique_ptr<CSingleSprite>(new CSingleSprite());
	object->init(pDevice_, pDeviceContext_, viewPort_, shaderName_, textureName_, position_, size_, uvArray_);
	return object;
}


CSingleSprite::CSingleSprite()
{
}


CSingleSprite::~CSingleSprite()
{
}

/**
* @fn void CSingleSprite::init(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, LPCWSTR textureName_, XMFLOAT4 position_, XMFLOAT2 size_, std::vector<UVCoord> uvArray_)
* @brief �C���X�^���X��������
* @param pDevice_			�f�o�C�X
* @param pDeviceContext_	�f�o�C�X�R���e�L�X�g
* @param viewPort_[]		�r���[�|�[�g
* @param shaderName_			�V�F�[�_�[�v���O����
* @param textureName_		�摜�t�@�C��
* @param position_			�E�B���h�E�̈ʒu
* @param size_				�X�v���C�g�̑傫��
* @param uvArray_			������UV�z��
* @return					����
*/
void CSingleSprite::init(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, LPCWSTR textureName_, XMFLOAT4 position_, XMFLOAT2 size_, std::vector<UVCoord>	uvArray_)
{
	super::init(pDevice_, pDeviceContext_, viewPort_, shaderName_, position_, size_, uvArray_);
	/**
	* �e�N�X�`���[�쐬(�T���v���[���܂�) DirectXTex <WindowsSDK 10>
	*/
	createSamplerAndTexture(pDevice_, textureName_);
}

/**
* @fn void CSingleSprite::createTexture (LPCWSTR textureName_)
* @brief �e�N�X�`�����t�@�C�����琶��
* @param pDevice_			�f�o�C�X
* @param textureName_		�摜�t�@�C��
* @return					����
*/
void CSingleSprite::createSamplerAndTexture(ID3D11Device*pDevice_, LPCWSTR textureName_)
{

	if ((textureName_ == NULL) || (g_pTexture))	//!< �y�N���X�ϐ��z
	{
		return;
	}

	/**
	* �e�N�X�`���[�p�T���v���[�쐬
	*/
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));

	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC; //!< D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 2;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.BorderColor[0] = 0.0f;
	samplerDesc.BorderColor[1] = 0.0f;
	samplerDesc.BorderColor[2] = 0.0f;
	samplerDesc.BorderColor[3] = 0.0f;
	samplerDesc.MinLOD = -FLT_MAX;
	samplerDesc.MaxLOD = FLT_MAX;

	pDevice_->CreateSamplerState(&samplerDesc, &g_pSampleLinear);
	/**
	* �y�N���X�ϐ��z
	* �e�N�X�`���[�쐬 DirectXTex <WindowsSDK 10>
	*/
	if (FAILED(CreateWICTextureFromFile(pDevice_, textureName_, NULL, &g_pTexture)))
	{
		//!< �y�N���X�ϐ��z �e�N�X�`���t�@�C������t������
		TCHAR   str[256];
		wsprintf(str, L"CSingleSprite::init <CreateWICTextureFromFile>�e�N�X�`���[�쐬���s %s", textureName_);
		throw str;
	}
}

/**
* @fn void CSingleSprite::render(XMFLOAT4X4	matView_, XMFLOAT4X4 matProj_, size_t uvIndex_, XMFLOAT4 diffuse_)
* @brief �����_�����O
* @param matView_	�r���[�s��
* @param matProj_	�v���W�F�N�V�����s��
* @param uvIndex_	�e�N�X�`���z��̈ʒu
* @param diffuse_	�f�B�t���[�Y
* @return			����
*/
void CSingleSprite::render(XMFLOAT4X4	matView_, XMFLOAT4X4 matProj_, size_t uvIndex_, XMFLOAT4 diffuse_)
{
	if (!m_active)
	{
		return;
	}
	if (m_damaged)
	{
		m_fadeOutFrames--;
	}
	if (m_fadeOutFrames <= 0)
	{
		m_active = FALSE;
		return;
	}
	computeMatrixFromPos();

	//! �V�F�[�_�[�@�萔�o�b�t�@
	D3D11_MAPPED_SUBRESOURCE pData;
	if (SUCCEEDED(m_pDeviceContext->Map(
		m_pConstantBuffer,			//!< �}�b�v���郊�\�[�X
		0, 							//!< �T�u���\�[�X�̃C���f�b�N�X�ԍ�
		D3D11_MAP_WRITE_DISCARD,	//!< �������݃A�N�Z�X
		0,
		&pData)))					//!< �f�[�^�̏������ݐ�|�C���^
	{
		ShaderGlobal_0 sg;
		XMStoreFloat4x4(&sg.matWVP, XMLoadFloat4x4(&m_mFinalWorld) * XMLoadFloat4x4(&matView_) * XMLoadFloat4x4(&matProj_));
		XMStoreFloat4x4(&sg.matWVP, XMMatrixTranspose(XMLoadFloat4x4(&sg.matWVP)));
		sg.diffuse = diffuse_;
		memcpy_s(pData.pData, pData.RowPitch, (void*)&sg, sizeof(ShaderGlobal_0));

		m_pDeviceContext->Unmap(m_pConstantBuffer, 0);
	}
	m_pDeviceContext->IASetInputLayout(m_pInputLayout);									//!< ���_�C���v�b�g���C�A�E�g���Z�b�g
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);	//!< �v���~�e�B�u�E�g�|���W�[���Z�b�g
	UINT stride = sizeof(VertexWithTex<XMFLOAT3>);
	UINT offset = 0;
	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVBArray[uvIndex_], &stride, &offset);//!< �o�[�e�b�N�X�o�b�t�@�[���Z�b�g
	m_pDeviceContext->VSSetShader(m_pVertexShader, NULL, 0);							//!< �g�p����V�F�[�_�[�̓o�^�@�ieffect�́h�e�N�j�b�N�h�ɑ����j
	m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);					//!< VS�ɒ萔�o�b�t�@��ݒ�
	m_pDeviceContext->RSSetViewports(1, m_viewPort);									//!< RS�Ƀr���[�|�[�g��ݒ�
	m_pDeviceContext->PSSetShader(m_pPixelShader, NULL, 0);								//!< PS�Ƀs�N�Z���E�V�F�[�_��ݒ�
	m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);					//!< PS�ɒ萔�o�b�t�@��ݒ�
																						//! �T���v���[�ƃe�N�X�`���[�̐ݒ�
	setSamplerAndTexture();
	m_pDeviceContext->Draw(4, 0);														//!<  �v���~�e�B�u�������_�����O
}

/**
* @fn BOOL CSingleSprite::setSamplerAndTexture()
* @brief		�e�N�X�`�����N���X�ϐ��Ƃ��ċ��L����
* @param		����
* @return		����
*/
void CSingleSprite::setSamplerAndTexture()
{
	m_pDeviceContext->PSSetSamplers(0, 1, &g_pSampleLinear);							//!< �y�N���X�ϐ��zPS�ɃT���v���[��ݒ�
	m_pDeviceContext->PSSetShaderResources(												//!< �y�N���X�ϐ��z�e�N�X�`���[���V�F�[�_�[�ɓn��
		0, //!< �ݒ肷��ŏ��̃X���b�g�ԍ�
		1, //!< �ݒ肷��V�F�[�_�E���\�[�X�E�r���[�̐�
		&g_pTexture);	//!< �ݒ肷��V�F�[�_�E���\�[�X�E�r���[�̔z��
}

/**
* @fn void CSingleSprite::release(void)
* @brief �����[�X
* @param	����
* @return	����
*/
void CSingleSprite::release(void)
{
	/**
	*  �K�����������̂Ƌt�̏��ԂŃ����[�X
	*/
	SAFE_RELEASE(g_pTexture);
	SAFE_RELEASE(g_pSampleLinear);
	super::release();
}
