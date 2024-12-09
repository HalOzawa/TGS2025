#include "Stage.h"
#include "Model.h"

Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage"),hModel_(-1)
{
}

Stage::~Stage()
{
}

void Stage::Initialize()
{
	hModel_ = Model::Load("Assets/Ground.fbx");
	assert(hModel_ >= 0);
}

void Stage::Update()
{
}

void Stage::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Stage::Release()
{
}
