#include "yuzinnaCollisionManager.h"
#include "yuzinnaScene.h"
#include "yuzinnaSceneManager.h"
#include "yuzinnaTransform.h"
namespace yuzinna
{

	std::bitset<(UINT)eLayerType::Max> 
		CollisionManager::mCollisionLayerMatrix[(UINT)eLayerType::Max] = {};

	std::unordered_map<UINT64, bool> CollisionManager::mCollisionMap = {};
	void CollisionManager::Initialize()
	{
		int a = 1;
		int b = a << 1;
	}
	void CollisionManager::Update()
	{
		Scene* scene = SceneManager::GetActiveScene();
		for (UINT row = 0; row < (UINT)eLayerType::Max; row++)
		{
			for (UINT col = 0; col < (UINT)eLayerType::Max; col++)
			{
				if (mCollisionLayerMatrix[row][col] == true)
				{
					LayerCollision(scene, (eLayerType)row, (eLayerType)col);
				}
			}
		}
	}
	void CollisionManager::LateUpdate()
	{
	}
	void CollisionManager::Render(HDC hdc)
	{
	}
	void CollisionManager::Clear()
	{
		mCollisionMap.clear();
		mCollisionLayerMatrix->reset();
	}
	//레이어끼리 충돌할지 안할지 설정하는 함수
	//left : 충돌 체크할 레이어1
	//right : 충돌 체크할 레이어1
	//enable : 현재 두레이어는 충돌 체크를 할건지 아닌지 설정
	void CollisionManager::CollisionLayerCheck(eLayerType left, eLayerType right, bool enable)
	{
		//콜리전 마스크의 행과 열
		int row = 0;

		int col = 0;

		//작은값(enum값이 더 작은값)을 행으로 몰아넣기(중복을 없애기 위해)
		//0 0 0 0 0
		//x 0 0 0 0
		//x x 0 0 0
		//x x x 0 0
		//x x x x 0
		if (left <= right)
		{
			row = (UINT)left;
			col = (UINT)right;
		}
		else
		{
			row = (UINT)right;
			col = (UINT)left;
		}
		mCollisionLayerMatrix[row][col] = enable;
	}
	//레이어간의 충돌을 검사하는 함수
	void CollisionManager::LayerCollision(Scene* scene, eLayerType left, eLayerType right)
	{
		//특정 레이어의 내부에 있던 게임오브젝트 벡터를 복사하지 않고
		//원본 그대로 참조하여 가져오게 하기위함으로 벡터에 참조를 붙임
		const std::vector<GameObject*>& lefts = SceneManager::GetGameObjects(left);
		const std::vector<GameObject*>& rights = SceneManager::GetGameObjects(right);
		
		for (GameObject* left : lefts)
		{
			//활성화된 오브젝트들만 체크
			if (left->IsActive() == false)
			{
				continue;
			}
			Collider* leftCol = left->GetComponent<Collider>();
			//콜라이더가 존재하는지 체크
			if (leftCol == nullptr)
			{
				continue;
			}
			for (GameObject* right: rights)
			{
				if (right->IsActive() == false)
				{
					continue;
				}
				Collider* rightCol = right->GetComponent<Collider>();
				if (rightCol == nullptr)
				{
					continue;
				}
				//자기 자신의 충돌은 스킵
				if (left == right)
				{
					continue;
				}
				ColliderCollision(leftCol, rightCol);
			}
		}
	}
	void CollisionManager::ColliderCollision(Collider* left, Collider* right)
	{
		CollisionID id = {};
		id.left = left->GetID();
		id.right = right->GetID();
		auto iter = mCollisionMap.find(id.id);
		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(id.id, false));
			iter = mCollisionMap.find(id.id);
		}
		if (Intersect(left, right))
		{
			if (iter->second == false)
			{
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);
				iter->second = true;
			}
			else
			{
				left->OnCollisionStay(right);
				right->OnCollisionStay(left);
			}
		}
		else
		{
			if (iter->second == true)
			{
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);

				iter->second = false;
			}
		}
	}
	
	bool CollisionManager::Intersect(Collider* left, Collider* right)
	{
		Transform* leftTr = left->GetOwner()->GetComponent<Transform>();
		Transform* rightTr = right->GetOwner()->GetComponent<Transform>();

		Vector2 leftPos = leftTr->GetPosition() + left->GetOffset();
		Vector2 rightPos = rightTr->GetPosition() + right->GetOffset();

		Vector2 leftSize = left->GetSize() * 100.0f;
		Vector2 rightSize = right->GetSize() * 100.0f;

		////fabs는 실수의 절댓값을 리턴해주는 함수
		//if(fabs(leftPos.x - rightPos.x)<fabs(leftSize.x/2.0f + rightSize.x / 2.0f)
		//	&& fabs(leftPos.y - rightPos.y)<fabs(leftSize.y /2.0f +rightSize.y/ 2.0f))
		//{
		//	return true;
		//}
		enums::eColliderType leftType = left->GetColliderType();
		enums::eColliderType rightType = right->GetColliderType();

		if (leftType == enums::eColliderType::Rect2D&&rightType==enums::eColliderType::Rect2D)
		{
			if (fabs(leftPos.x - rightPos.x) < fabs(leftSize.x / 2.0f + rightSize.x / 2.0f)
				&& fabs(leftPos.y - rightPos.y) < fabs(leftSize.y / 2.0f + rightSize.y / 2.0f))
			{
				return true;
			}
		}
		if (leftType == enums::eColliderType::Circle2D && rightType == enums::eColliderType::Circle2D)
		{
			Vector2 leftCirclePos = leftPos + (leftSize / 2.0f);
			Vector2 rightCirclePos = rightPos + (rightSize / 2.0f);
			float distance = (leftCirclePos - rightCirclePos).length();
			if (distance <= (leftSize.x / 2.0f + rightSize.x / 2.0f))
			{
				return true;
			}
		}
		if ((leftType == enums::eColliderType::Circle2D && rightType == enums::eColliderType::Rect2D)
			|| (leftType == enums::eColliderType::Rect2D && rightType == enums::eColliderType::Circle2D))
		{
			//왼쪽콜라이더가 원
			if (leftType == enums::eColliderType::Circle2D)
			{
				//오브젝트의 중심좌표 +서클 콜라이더의 오프셋 
				//사각형의 최소 좌표 , 최대 좌표
				int clx = std::clamp(leftPos.x, rightPos.x -(rightSize.x/2),rightPos.x + (rightSize.x/2) );
				int cly = std::clamp(leftPos.y, rightPos.y -(rightSize.y/2),rightPos.y + (rightSize.y/2) );
				//원의 좌표에서 사각형에서 원의 중심까지 최대로 가까운 좌푯값의 차를 구함
				int distX = leftPos.x - clx;
				int distY = leftPos.y - cly;
				int one = distX * distX + distY * distY;
				int two = (leftSize.x / 2) * (leftSize.x / 2) + (leftSize.y / 2) * (leftSize.y / 2);
				
				//원의 반지름이 위에서 구한 좌푯값의 차이가 더 큰경우 충돌한것으로 판정
				if (one <= two)
				{
					return true;
				}
			}
			//오른쪽 콜라이더가 원
			else
			{
				int clx = std::clamp(rightPos.x, leftPos.x - (leftSize.x / 2), leftPos.x + (leftSize.x / 2));
				int cly = std::clamp(rightPos.y, leftPos.y - (leftSize.y / 2), leftPos.y + (leftSize.y / 2));
				int distX = rightPos.x - clx;
				int distY = rightPos.y - cly;
				//TODO
				if (distX * distX + distY * distY <= (rightSize.x / 2) * (rightSize.x / 2) + (rightSize.y / 2) * (rightSize.y / 2))
				{
					return true;
				}
			}
			
			
		}
	return false;
	}
}