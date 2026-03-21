#include "uginaCamera.h"
#include "uginaApplication.h"
#include "uginaTransform.h"
#include "uginaGameObject.h"
extern ugina::Application api;
namespace ugina
{
	Camera::Camera()
		:Component(enums::eComponentType::Camera)
		, mDistance(Vector2::Zero)
		, mResolution(Vector2::Zero)
		, mLookPosition(Vector2::Zero)
		, mTarget(nullptr)
	{
	}
	Camera::~Camera()
	{
	}
	void Camera::Initialize()
	{
		mResolution.x = api.GetWidth();
		mResolution.y = api.Getheight();
	}
	void Camera::Update()
	{

		//현재 바라보는 타겟이 존재하면 타겟의 포지션으로 카메라가 바라보는 지점(mLookPosition) 설정
		if (mTarget)
		{
			Transform* tr = mTarget->GetComponent<Transform>();
			mLookPosition = tr->GetPosition();
		}
		//바라보는 타겟이 존재하지 않다면 현재 카메라의 위치를 바라보는 지점으로 
		else
		{
			Transform* cameraTr = GetOwner()->GetComponent<Transform>();
			mLookPosition = cameraTr->GetPosition();
		}		
		//카메라가 이동한 거리(카메라의 좌상단) = 카메라가 바라보는 위치(타겟포지션 or 카메라의포지션) - 카메라 해상도의 절반(중앙)
		mDistance = mLookPosition - (mResolution / 2.0f);

	}
	void Camera::LateUpdate()
	{
	}
	void Camera::Render(HDC hdc)
	{
	}
}