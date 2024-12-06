#include "Player.h"
#include "Engine/Fbx.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Model.h"

//カメラの制御
enum CAM_TYPE
{
	FIXED_TYPE, //固定
	TPS_TYPE,   //3人称
	FPS_TYPE,   //1人称
	MAX_TYPE    //番兵
};

Player::Player(GameObject* parent)
	:GameObject(parent,"Player"), hModel_(-1), speed_(0.05),
	 front_({0,0,1,0}), camState_(CAM_TYPE::FIXED_TYPE)
{
}

Player::~Player()
{

}

void Player::Initialize()
{
	hModel_ = Model::Load("Assets/Oden.fbx");
	this->transform_.scale_.x = 0.5;
	this->transform_.scale_.y = 0.5;
	this->transform_.scale_.z = 0.5;
	this->transform_.position_.y = -1.5;
	//assert(hModel_ >= 0);
	//Instantiate<Player>(this);
}

void Player::Update()
{
	XMMATRIX rotY = XMMatrixIdentity(); //行列の1単位行列
	XMVECTOR move{ 0,0,0,0 };
	XMVECTOR rotVec{ 0,0,0,0 };
	float dir = 0;
	//移動
	if (Input::IsKey(DIK_W))
	{
		dir = +1.0;
	}
	if (Input::IsKey(DIK_S))
	{
		dir = -1.0;
	}
	if (Input::IsKey(DIK_A))
	{
		this->transform_.rotate_.y -= 1;
	}
	if (Input::IsKey(DIK_D))
	{
		this->transform_.rotate_.y += 1;
	}

	//回転行列を求める
	rotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	rotVec = XMVector3TransformCoord(front_, rotY);
	move = speed_ * rotVec;
	XMVECTOR pos = XMLoadFloat3(&(transform_.position_));
	pos = pos + dir * move;
	XMStoreFloat3(&(transform_.position_), pos);

	if (Input::IsKeyDown(DIK_Z))
	{
		camState_++;
		if (camState_ == CAM_TYPE::MAX_TYPE)
			camState_ = CAM_TYPE::FIXED_TYPE;
	}

	switch (camState_)
	{
	case CAM_TYPE::FIXED_TYPE:
	{
		Camera::SetPosition(XMFLOAT3(0, 20, -20));
		Camera::SetTarget(XMFLOAT3(0, 0, 0));
		break;
	}
	case CAM_TYPE::TPS_TYPE:
	{
		Camera::SetTarget(transform_.position_);
		XMVECTOR vEye{ 0,5,-10,0 };
		vEye = XMVector3TransformCoord(vEye, rotY);
		XMFLOAT3 camPos;
		XMStoreFloat3(&camPos, pos + vEye);
		Camera::SetPosition(camPos);
		break;
	}
	case CAM_TYPE::FPS_TYPE:
	{
		Camera::SetPosition(transform_.position_);
		XMFLOAT3 camTarget;
		XMStoreFloat3(&camTarget, pos + move);
		Camera::SetTarget(camTarget);
		break;
	}
	default:
		break;
	}
}

void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}
void Player::Release()
{

}
