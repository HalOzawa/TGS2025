#pragma once
#include "Engine/GameObject.h"
class TestScene :
    public GameObject
{
    public:
        //コンストラクタ
        //引数：parent  親オブジェクト（SceneManager）
        TestScene(GameObject * parent);
        void Initialize() override;
        void Update() override;
        void Draw() override;
        void Release() override;
};

