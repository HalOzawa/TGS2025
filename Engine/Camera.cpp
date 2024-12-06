#include "Camera.h"
#include "Direct3D.h"


namespace Camera
{
	//変数
	XMFLOAT3 position_;	//カメラの位置（視点）
	XMFLOAT3 target_;	//見る位置（焦点）
	XMMATRIX viewMatrix_;	//ビュー行列
	XMMATRIX projMatrix_;	//プロジェクション行列
	XMMATRIX billBoard_;
}


void Camera::Initialize()
{
	position_ = XMFLOAT3(0, 3, -10);	//カメラの位置
	target_ = XMFLOAT3(0, 0, 0);	//カメラの焦点

	//プロジェクション行列
	projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)Direct3D::WINDOW_WIDTH / (FLOAT)Direct3D::WINDOW_HEIGHT, 0.1f, 100.0f);
}

void Camera::Initialize(XMVECTOR _position, XMVECTOR _target)
{
	//position_ = _position;	//カメラの位置
	//target_ = _target;	//カメラの焦点

	//プロジェクション行列
	projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)Direct3D::WINDOW_WIDTH / (FLOAT)Direct3D::WINDOW_HEIGHT, 0.1f, 100.0f);
}

void Camera::Update()
{
	//ビュー行列の作成
	viewMatrix_ = XMMatrixLookAtLH(XMVectorSet(position_.x, position_.y, position_.z,0 ),
		       XMVectorSet(target_.x, target_.y, target_.z, 0), XMVectorSet(0, 1, 0, 0));

	//ビルボード行列
	billBoard_ = XMMatrixLookAtLH(XMVectorSet(0, 0, 0, 0), XMLoadFloat3(&target_) - XMLoadFloat3(&position_), XMVectorSet(0, 1, 0, 0));
	billBoard_ = XMMatrixInverse(nullptr, billBoard_);
}

void Camera::SetPosition(XMFLOAT3 position)
{
	position_ = position;
}

void Camera::SetTarget(XMFLOAT3 target)
{
	target_ = target;
}

XMFLOAT3 Camera::GetPosition()
{
	return position_;
}

XMFLOAT3 Camera::GetTarget()
{
	return target_;
}

XMMATRIX Camera::GetViewMatrix()
{
	return viewMatrix_;
}

XMMATRIX Camera::GetProjectionMatrix()
{
	return projMatrix_;
}

XMMATRIX Camera::GetBillboardMatrix()
{
	return billBoard_;
}
