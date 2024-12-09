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

//���C�L���X�g�p�\����
struct RayCastData
{
	XMFLOAT3 start;  //���C���ˈʒu
	XMFLOAT3 dir;    //���C�̌����x�N�g��
	float    dist;   //�Փ˓_�܂ł̋���
	BOOL     hit;    //���C������������
	XMFLOAT3 normal; //�@��

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
		XMMATRIX	matWVP; //���[���h�r���[�v���W�F�N�V����
		XMMATRIX	matNormal;   //�@���x�N�g���̕ϊ��p
		XMFLOAT4	diffuseColor;
		int		isTextured;
	};

	//���_���
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
		XMVECTOR normal; //�m�[�}���ǉ��i�@���x�N�g���j
	};

	ID3D11Buffer* pVertexBuffer_; //���_�o�b�t�@�p������ 
	ID3D11Buffer** pIndexBuffer_; //�C���f�b�N�X�o�b�t�@�p������
	ID3D11Buffer* pConstantBuffer_; //�R���X�^���g�o�b�t�@�p������
	std::vector<MATERIAL> pMaterialList_; //�}�e���A���̔z��
	std::vector<int> indexCount_;//�}�e���A�����Ƃ̃C���f�b�N�X��

	int vertexCount_;	//���_��
	int polygonCount_;	//�|���S����
	int materialCount_; //�}�e���A����

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

