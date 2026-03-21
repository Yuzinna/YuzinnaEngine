#include "yuzinnaCatScript.h"
#include "yuzinnaGameObject.h"
#include "yuzinnaTime.h"
#include "yuzinnaAnimator.h"
#include "yuzinnaObject.h"
#include "yuzinnaInput.h"
#include "mftransform.h"
namespace yuzinna
{
	CatScript::CatScript()
		:mState(CatScript::eState::SitDown)
		, mAnimator(nullptr)
		, mTime(0.0f)
		, mDeathTime(0.0f)
		, mDest(Vector2::Zero)
		, mRadian(0.0f)
	{
	}
	CatScript::~CatScript()
	{
	}
	void CatScript::Initialize()
	{
	}
	void CatScript::Update()
	{
		mDeathTime += Time::DeltaTime();
		if (mDeathTime > 6.0f)
		{
			//object::Destroy(getOwner());
		}
		if (mAnimator == nullptr)
		{
			mAnimator = GetOwner()->GetComponent<Animator>();
		}
		switch (mState)
		{
		case yuzinna::CatScript::eState::SitDown:
			sitDown();
			break;
		case yuzinna::CatScript::eState::Walk:
			move();
			break;
		case yuzinna::CatScript::eState::Sleep:
			break;
		case yuzinna::CatScript::eState::LayDown:
			break;
		case yuzinna::CatScript::eState::Attack:
			break;
		case yuzinna::CatScript::eState::Count:
			break;
		default:
			break;
		}
	}
	void CatScript::LateUpdate()
	{
	}
	void CatScript::Render(HDC hdc)
	{
	}
	void CatScript::sitDown()
	{
		mTime += Time::DeltaTime();
		//경과한 시간이 3초가 넘으면..
		//if (mTime > 3.0f)
		//{
		//	//상태를 걷기로 변환한다
		//	mState = CatScript::eState::Walk;
		//	//방향은 동서남북 4방향
		//	int direction = (rand() % 4);
		//	mDirection = (eDirection)direction;
		//	PlayWalAnimationByDirection(mDirection);
		//	//시간 초기화
		//	mTime = 0.0f;
		//}
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		//Transform* plTr = mPlayer->GetComponent<Transform>();
		//Vector2 dest = mDest - plTr->GetPosition();
		//pos += dest.normalize() * (100.0f * Time::DeltaTime());

		//mRadian += 5.0f * Time::DeltaTime();
		//pos += Vector2(1.0f, 2.0f * cosf(mRadian)) * (100.0f * Time::DeltaTime());

		//Transform* plTr = mPlayer->GetComponent<Transform>();
		//Vector2 dest = mDest - plTr->GetPosition();
		//dest.normalize();

		//float rotDegree = Vector2::Dot(dest, Vector2::Right); //cos세타
		//rotDegree = acosf(rotDegree);

		//rotDegree = ConvertDegree(rotDegree);

		//pos += dest * (100.0f * Time::DeltaTime());

		//tr->SetPosition(pos);

	}
	void CatScript::move()
	{
		mTime += Time::DeltaTime();
		if (mTime > 2.0f)
		{
			int isLayDown = rand() % 2;
			if (isLayDown)
			{
				mState = eState::LayDown;
				mAnimator->PlayAnimation(L"LayDown", false);
			}
			else
			{
				mState = eState::SitDown;
				mAnimator->PlayAnimation(L"SitDown", false);
			}
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();
		translate(tr);
	}
	void CatScript::laydDown()
	{
	}
	void CatScript::PlayWalAnimationByDirection(eDirection dir)
	{
		switch (dir)
		{
		case yuzinna::CatScript::eDirection::Left:
			mAnimator->PlayAnimation(L"LeftWalk", true);
			break;
		case yuzinna::CatScript::eDirection::Right:
			mAnimator->PlayAnimation(L"RightWalk", true);
			break;
		case yuzinna::CatScript::eDirection::Down:
			mAnimator->PlayAnimation(L"DownWalk", true);
			break;
		case yuzinna::CatScript::eDirection::Up:
			mAnimator->PlayAnimation(L"UpWalk", true);
			break;
		case yuzinna::CatScript::eDirection::End:
			break;
		default:
			assert(false);
			break;
		}
	}
	void CatScript::translate(Transform* tr)
	{

		Vector2 pos = tr->GetPosition();
		switch (mDirection)
		{
		case yuzinna::CatScript::eDirection::Left:
			pos.x -= 100.0f * Time::DeltaTime();
			break;
		case yuzinna::CatScript::eDirection::Right:
			pos.x += 100.0f * Time::DeltaTime();
			break;
		case yuzinna::CatScript::eDirection::Down:
			pos.y += 100.0f * Time::DeltaTime();
			break;
		case yuzinna::CatScript::eDirection::Up:
			pos.y -= 100.0f * Time::DeltaTime();
			break;
		case yuzinna::CatScript::eDirection::End:
			break;
		default:
			assert(false);
			break;
		}
		tr->SetPosition(pos);
	}
}