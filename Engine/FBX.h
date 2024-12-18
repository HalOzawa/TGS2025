#pragma once
#include "Direct3D.h"
#include <fbxsdk.h>
#include <DirectXMath.h>
#include "Texture.h"
#include "Transform.h"
#include <vector>
#include <filesystem>
#include "Texture.h"

//#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")

class FbxParts;

//レイキャスト用構造体
struct RayCastData
{
	XMFLOAT3 start;  //レイ発射位置
	XMFLOAT3 dir;    //レイの向きベクトル
	float    dist;   //衝突点までの距離
	BOOL     hit;    //レイが当たったか
	XMFLOAT3 normal; //法線

	RayCastData() { dist = 9999.0f; }
};

class FBX
{
	friend class FbxParts;
	std::vector<FbxParts*>	parts_;

	struct MATERIAL
	{
		Texture* pTexture;
		XMFLOAT4 diffuse;
	};

	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP; //ワールドビュープロジェクション
		XMMATRIX	matNormal;   //法線ベクトルの変換用
		XMFLOAT4	diffuseColor;
		int		isTextured;
	};

	//頂点情報
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
		XMVECTOR normal; //ノーマル追加（法線ベクトル）
	};

	ID3D11Buffer* pVertexBuffer_; //頂点バッファ用メモリ 
	ID3D11Buffer** pIndexBuffer_; //インデックスバッファ用メモリ
	ID3D11Buffer* pConstantBuffer_; //コンスタントバッファ用メモリ
	std::vector<MATERIAL> pMaterialList_; //マテリアルの配列
	std::vector<int> indexCount_;//マテリアルごとのインデックス数

	int vertexCount_;	//頂点数
	int polygonCount_;	//ポリゴン数
	int materialCount_; //マテリアル数

	void InitVertex(fbxsdk::FbxMesh* mesh);
	void InitIndex(fbxsdk::FbxMesh* mesh);
	void InitConstantBuffer();
	void InitMaterial(fbxsdk::FbxNode* pNode);
public:
	FBX();
	HRESULT Load(std::string fileName);
	void    Draw(Transform& transform);
	void    RayCast(RayCastData* data);
	void    Release();
};

