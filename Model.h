#pragma once
#include <string>
#include "Engine/Fbx.h"

namespace Model
{
	struct ModelData
	{
		FBX* pFbx_;
		Transform transform_;
		std::string filename_;
		ModelData():pFbx_(nullptr),filename_(""){}
	};
	//モデルの一覧を保存する配列（ヴェクタかリスト？）
	int Load(std::string filename);
	void SetTransform(int hModel, Transform transform);
	void Draw(int hModel);
	//レイキャスト（レイを飛ばして当たり判定）　※未実装
	//引数：handle	判定したいモデルの番号
	//引数：data	必要なものをまとめたデータ
	void RayCast(int handle, RayCastData* data);
	void Release();
}

