#pragma once
#include "Engine/GameObject.h"

class Fbx;

class Player :
    public GameObject
{
    int hModel_;
    XMVECTOR front_;
    float speed_;
    int camState_;

public:
    //コンストラクタ
    Player(GameObject* parent);

    //デストラクタ
    ~Player();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};

