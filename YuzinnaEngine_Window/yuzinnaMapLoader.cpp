#include "yuzinnaMapLoader.h"
#include "yuzinnaObjectFactory.h"
#include <string>

namespace yuzinna
{
	void MapLoader::LoadMap(const std::vector<std::wstring>& mapData)
	{
		int height = (int)mapData.size();
		if (height == 0) return;
		int width = (int)mapData[0].size();

		// 주변에 벽이 있는지 확인하는 헬퍼 함수
		auto IsWall = [&](int x, int y) -> bool {
			if (x < 0 || x >= width || y < 0 || y >= height) return false;
			return mapData[y][x] == L'W';
		};

		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				wchar_t tile = mapData[y][x];
				math::Vector2 gridPos((float)x, (float)y);

				switch (tile)
				{
				// --- [Physical Objects] ---
				case L'B': // 바바 캐릭터
					ObjectFactory::CreateBaba(gridPos);
					break;

				case L'F': // 깃발 오브젝트
					ObjectFactory::CreateNounObject(L"Flag", L"Flag", gridPos);
					break;

				case L'R': // 바위 오브젝트
					ObjectFactory::CreateRock(gridPos);
					break;

				case L'K': // 열쇠 오브젝트
					ObjectFactory::CreateKey(gridPos);
					break;

				case L'S': // 해골 오브젝트
					ObjectFactory::CreateSkull(gridPos);
					break;

				case L'W': // 벽 (오토 타일링 적용)
				{
					auto IsWall = [&](int x, int y) -> bool {
						if (x < 0 || x >= width || y < 0 || y >= height) return false;
						return mapData[y][x] == L'W';
					};
					int bitmask = 0;
					if (IsWall(x, y - 1)) bitmask += 1;
					if (IsWall(x + 1, y)) bitmask += 2;
					if (IsWall(x, y + 1)) bitmask += 4;
					if (IsWall(x - 1, y)) bitmask += 8;

					std::wstring wallTexKey = L"Wall_" + std::to_wstring(bitmask);
					ObjectFactory::CreateNounObject(L"Wall", wallTexKey, gridPos);
				}
				break;

				case L'O': // 물 (오토 타일링 적용)
				{
					auto IsWater = [&](int x, int y) -> bool {
						if (x < 0 || x >= width || y < 0 || y >= height) return false;
						return mapData[y][x] == L'O';
					};
					int bitmask = 0;
					if (IsWater(x, y - 1)) bitmask += 1;
					if (IsWater(x + 1, y)) bitmask += 2;
					if (IsWater(x, y + 1)) bitmask += 4;
					if (IsWater(x - 1, y)) bitmask += 8;

					std::wstring waterTexKey = L"Water_" + std::to_wstring(bitmask);
					ObjectFactory::CreateWater(gridPos, waterTexKey);
				}
				break;

				// --- [Word Blocks] ---
				case L'b': // BABA 단어
					ObjectFactory::CreateWord(enums::eWordType::Baba, gridPos);
					break;

				case L'i': // IS 단어
					ObjectFactory::CreateWord(enums::eWordType::Is, gridPos);
					break;

				case L'y': // YOU 단어
					ObjectFactory::CreateWord(enums::eWordType::You, gridPos);
					break;

				case L'f': // FLAG 단어
					ObjectFactory::CreateWord(enums::eWordType::Flag, gridPos);
					break;

				case L'w': // WIN 단어
					ObjectFactory::CreateWord(enums::eWordType::Win, gridPos);
					break;

				case L's': // STOP 단어
					ObjectFactory::CreateWord(enums::eWordType::Stop, gridPos);
					break;

				case L'p': // PUSH 단어
					ObjectFactory::CreateWord(enums::eWordType::Push, gridPos);
					break;

				case L'a': // WALL 단어 (Wall -> a로 변경)
					ObjectFactory::CreateWord(enums::eWordType::Wall, gridPos);
					break;

				case L'r': // ROCK 단어
					ObjectFactory::CreateWord(enums::eWordType::Rock, gridPos);
					break;

				case L'k': // KEY 단어
					ObjectFactory::CreateWord(enums::eWordType::Key, gridPos);
					break;

				case L'u': // SKULL 단어
					ObjectFactory::CreateWord(enums::eWordType::Skull, gridPos);
					break;

				case L'v': // SINK 단어
					ObjectFactory::CreateWord(enums::eWordType::Sink, gridPos);
					break;

				case L't': // WATER 단어
					ObjectFactory::CreateWord(enums::eWordType::Water, gridPos);
					break;

				default:
					break;
				}
			}
		}
	}
}
