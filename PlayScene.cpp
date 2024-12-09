#include "PlayScene.h"
#include "Engine/Fbx.h"
#include "Player.h"
#include "Stage.h"
#include "Enemy.h"

PlayScene::PlayScene(GameObject* parent)
{
}

void PlayScene::Initialize()
{
	Instantiate<Stage>(this);
	Instantiate<Player>(this);
	//Instantiate<Enemy>(this);
}

void PlayScene::Update()
{
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{

}
