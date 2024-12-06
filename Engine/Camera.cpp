#include "Camera.h"
#include "Direct3D.h"


namespace Camera
{
	//�ϐ�
	XMFLOAT3 position_;	//�J�����̈ʒu�i���_�j
	XMFLOAT3 target_;	//����ʒu�i�œ_�j
	XMMATRIX viewMatrix_;	//�r���[�s��
	XMMATRIX projMatrix_;	//�v���W�F�N�V�����s��
	XMMATRIX billBoard_;
}


void Camera::Initialize()
{
	position_ = XMFLOAT3(0, 3, -10);	//�J�����̈ʒu
	target_ = XMFLOAT3(0, 0, 0);	//�J�����̏œ_

	//�v���W�F�N�V�����s��
	projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)Direct3D::WINDOW_WIDTH / (FLOAT)Direct3D::WINDOW_HEIGHT, 0.1f, 100.0f);
}

void Camera::Initialize(XMVECTOR _position, XMVECTOR _target)
{
	//position_ = _position;	//�J�����̈ʒu
	//target_ = _target;	//�J�����̏œ_

	//�v���W�F�N�V�����s��
	projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)Direct3D::WINDOW_WIDTH / (FLOAT)Direct3D::WINDOW_HEIGHT, 0.1f, 100.0f);
}

void Camera::Update()
{
	//�r���[�s��̍쐬
	viewMatrix_ = XMMatrixLookAtLH(XMVectorSet(position_.x, position_.y, position_.z,0 ),
		       XMVectorSet(target_.x, target_.y, target_.z, 0), XMVectorSet(0, 1, 0, 0));

	//�r���{�[�h�s��
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
