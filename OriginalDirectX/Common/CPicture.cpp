/**
* @file CPicture.cpp
* @brief テクセル付きのピクチャー・クラス
* @author 織戸　喜隆
* @date 日付（2017.02.14）
*/

#include "stdafx.h"
#include "CPicture.h"

/**
* @fn std::unique_ptr<CPicture> CPicture::create(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, LPCWSTR textureName_, XMFLOAT4 position_, XMFLOAT2 size_, std::vector<QuadrangleTexel> texels)
* @brief インスタンスを生成し初期化 【クラスメソッド】
* @param pDevice_			デバイス
* @param pDeviceContext_	デバイスコンテキスト
* @param viewPort_[]		ビューポート
* @param shaderName_		シェーダープログラム
* @param textureName_		PNGファイル
* @param position_			ウィンドウの位置
* @param size_				スプライトの大きさ
* @param texels			テクセルの配列
* @return					CPictureのユニークポインタ
*/
std::unique_ptr<CPicture> CPicture::create(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, LPCWSTR textureName_, XMFLOAT4 position_, XMFLOAT2 size_, std::vector<QuadrangleTexel>	texels)
{
	std::unique_ptr<CPicture> object = unique_ptr<CPicture>(new CPicture());
	object->init(pDevice_, pDeviceContext_, viewPort_, shaderName_, textureName_, position_, size_, texels);
	return object;
}

/**
* @fn void CPicture::init(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, LPCWSTR textureName_, XMFLOAT4 position_, XMFLOAT2 size_, std::vector<QuadrangleTexel> texels)
* @brief インスタンスを初期化
* @param pDevice_			デバイス
* @param pDeviceContext_	デバイスコンテキスト
* @param viewPort_[]		ビューポート
* @param shaderName_		シェーダープログラム
* @param textureName_		PNGファイル
* @param position_			ウィンドウの位置
* @param size_				スプライトの大きさ
* @param texels			テクセルの配列
* @return					無し
*/
void CPicture::init(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, LPCWSTR textureName_, XMFLOAT4 position_, XMFLOAT2 size_, std::vector<QuadrangleTexel>	texels)
{
	super::init(pDevice_, pDeviceContext_, viewPort_, shaderName_, position_, size_, texels);

	if (textureName_ != NULL)
	{
		/**
		* テクスチャー作成(サンプラーを含む) DirectXTex <WindowsSDK 10>
		*/
		//m_pPolygonTex = CTexture::create(pDevice_, textureName_);
	}
}

CPicture::CPicture()
{
}

CPicture::~CPicture()
{
}

/**
* @fn void CPicture::render(XMFLOAT4X4	matView_, XMFLOAT4X4 matProj_, size_t texelIndex_, XMFLOAT4 diffuse_)
* @brief レンダリング
* @param matView_	ビュー行列
* @param matProj_	プロジェクション行列
* @param texelIndex_	テクセル・インデックス
* @param diffuse_	ディフューズ
* @return			無し
*/
void CPicture::render(XMFLOAT4X4	matView_, XMFLOAT4X4 matProj_, shared_ptr<CTexture> texture_, size_t texelIndex_, XMFLOAT4 diffuse_)
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

	//! シェーダー　定数バッファ
	D3D11_MAPPED_SUBRESOURCE pData;
	if (SUCCEEDED(m_pDeviceContext->Map(
		m_pConstantBuffer,			//!< マップするリソース
		0, 							//!< サブリソースのインデックス番号
		D3D11_MAP_WRITE_DISCARD,	//!< 書き込みアクセス
		0,
		&pData)))					//!< データの書き込み先ポインタ
	{
		ShaderGlobal_0 sg;
		XMStoreFloat4x4(&sg.matWVP, XMLoadFloat4x4(&m_mFinalWorld) * XMLoadFloat4x4(&matView_) * XMLoadFloat4x4(&matProj_));
		XMStoreFloat4x4(&sg.matWVP, XMMatrixTranspose(XMLoadFloat4x4(&sg.matWVP)));
		sg.diffuse = diffuse_;
		memcpy_s(pData.pData, pData.RowPitch, (void*)&sg, sizeof(ShaderGlobal_0));

		m_pDeviceContext->Unmap(m_pConstantBuffer, 0);
	}
	m_pDeviceContext->IASetInputLayout(m_pInputLayout);									//!< 頂点インプットレイアウトをセット
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);	//!< プリミティブ・トポロジーをセット
	UINT stride = sizeof(VertexWithTex<XMFLOAT3>);
	UINT offset = 0;
	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer[texelIndex_], &stride, &offset);//!< 頂点バッファーをセット
	m_pDeviceContext->VSSetShader(m_pVertexShader, NULL, 0);							//!< 使用するシェーダーの登録　（effectの”テクニック”に相当）
	m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);					//!< VSに定数バッファを設定
	m_pDeviceContext->RSSetViewports(1, m_viewPort);									//!< RSにビューポートを設定
	m_pDeviceContext->PSSetShader(m_pPixelShader, NULL, 0);								//!< PSにピクセル・シェーダを設定
	m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);					//!< PSに定数バッファを設定
	//! サンプラーとテクスチャーの設定
	texture_->setup(m_pDeviceContext);
	m_pDeviceContext->Draw(4, 0);														//!<  プリミティブをレンダリング
}

/**
* @fn void CPicture::release()
* @brief リリース
* @param	無し
* @return	無し
*/
void CPicture::release()
{
	/**
	*  必ず生成したのと逆の順番でリリース
	*/
	super::release();
}