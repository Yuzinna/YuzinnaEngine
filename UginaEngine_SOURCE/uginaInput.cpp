#include "uginaInput.h"
#include "uginaApplication.h"

extern ugina::Application api;
namespace ugina
{
	//스태틱 변수는 cpp파일에서 정의 한다
	std::vector<Input::Key> Input::keys = {};
	//마우스좌표의 초기화 
	math::Vector2 Input::mMousePosition = math::Vector2::One;

	int ASCII[(UINT)eKeyCode::Count] = { 
		'A', 'B', 'C', 'D',
		'E', 'F', 'G', 'H',
		'I', 'J', 'K', 'L',
		'M', 'N', 'O', 'P',
		'Q', 'R', 'S', 'T',
		'U', 'V', 'W', 'X',
		'Y', 'Z',' '
		,VK_LBUTTON,VK_MBUTTON,VK_RBUTTON};

	void Input::Initialize()
	{
		createKeys();
	}
	void Input::Update()
	{
		updateKeys();
	}
	void Input::createKeys()
	{
		//내가 설정한 키코드의 갯수만큼 Keys vector를 기본값으로 초기화 해줌
		for (int i = 0; i < (int)eKeyCode::Count; i++)
		{
			//명시적인 Key구조체 초기화
			Key key = {};
			key.bPressed = false;
			key.code = (eKeyCode)i;
			key.state = keyState::None;

			keys.push_back(key);
		}
	}
	void Input::updateKeys()
	{
		// Keys vector 전체를 돌면서 눌렸는지 아닌지를 판정함
		std::for_each(keys.begin(), keys.end(),
			[](Key& key)->void { updateKey(key); });
	}
	void Input::updateKey(Input::Key& key)
	{

		//현재 이 윈도우가 포커스 되어있다면 키가 눌렸는지 안눌렸는지 체크한다
		if (GetFocus())
		{
			//눌렸을때는 키의상태를 눌리는 상태로 단계적으로 상승시킴
			if (isKeyDown(key.code))
			{
				updateKeyDown(key);
			}
			//때졌을때는 키의상태를 때지는 상태로 단계적으로 상승시킴
			else
			{
				updateKeyUp(key);
			}
			getMousePositionByWindow();
		}
		//포커스 되어있지 않다면, 전체 키들을 다 눌리지 않은 상태로 만든다
		else
		{
			clearKeys();
		}
		
	}
	bool Input::isKeyDown(eKeyCode code)
	{
		return GetAsyncKeyState(ASCII[(int)code]) & 0x8000;
	}


	void Input::updateKeyDown(Input::Key& key)
	{
		//이전에 눌렸던 상태라면 다음단계는 무조건 Pressed
		if (key.bPressed == true)
		{
			key.state = keyState::Pressed;
		}
		//이전에 안눌렸던 상태라면 다음단계는 무조건 Down
		else
		{
			key.state = keyState::Down;
		}
		//다음 업데이트 입장에선 현재키는 눌렸던 상태니까 바꿔주기
		key.bPressed = true;
	}
	void Input::updateKeyUp(Input::Key& key)
	{
		//이전에 눌렸던 상태라면 다음단계는 무조건 Up
		if (key.bPressed == true)
		{
			key.state = keyState::Up;
		}
		//이전에 안눌렸던 상태라면 다음단계는 무조건 None
		else
		{
			key.state = keyState::None;
		}
		//다음 업데이트 입장에선 현재키는 안눌렸던 상태니까 바꿔주기
		key.bPressed = false;
	}
	void Input::getMousePositionByWindow()
	{
		//마우스 좌표를 담을 임시 변수(구조체)
		POINT mousePos = {};
		//현재 모니터를 기준으로 한 마우스좌표
		GetCursorPos(&mousePos);
		//모니터를 기준으로 한 마우스좌표를 현재 현재윈도우를 기준으로 바꿔줌
		ScreenToClient(api.GetHwnd(),&mousePos);

		//임시 변수에 있던 값을 멤버변수에 넣어주기
		/*
		mMousePosition.x = mousePos.x;
		mMousePosition.y = mousePos.y;*/

		UINT width = api.GetWidth();
		UINT height = api.Getheight();

		mMousePosition.x = -1.0f;
		mMousePosition.y = -1.0f;

		if (mousePos.x > 0 && mousePos.x < width)
		{
			mMousePosition.x = mousePos.x;
		}
		if (mousePos.y > 0 && mousePos.y < height)
		{
			mMousePosition.y = mousePos.y;
		}

	}
	void Input::clearKeys()
	{
		for (Key& key : keys)
		{
			//아무튼 전에 방금 눌렸거나, 꾹눌린 상태라면 이제 막땐 상태로 바꿔줌
			if (key.state == keyState::Down || key.state == keyState::Pressed)
			{
				key.state = keyState::Up;
			}
			//막 땐 상태라면 이제 아무것도 아닌 상태로 바꿔줌
			else if (key.state == keyState::Up)
			{
				key.state = keyState::None;
			}
			// 이전에 눌렸는가에 대해 안눌렸다로 바꿔줌
			key.bPressed = false;
		}
	}
}

