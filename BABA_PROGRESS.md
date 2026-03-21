# UginaEngine - Baba Is You 모작 프로젝트 진행 상황

이 문서는 AI(Gemini CLI)와 함께 진행한 '바바 이즈 유' 모작 프로젝트의 아키텍처와 구현 상세를 기록한 문서입니다.

## 1. 프로젝트 아키텍처 (Architecture)
- **엔진 독립성 유지:** 모든 게임 전용 로직은 `UginaEngine_Window`(게임 로직) 프로젝트 내에 구현되었습니다.
- **컴포넌트 기반 설계:** `uginaScript`를 상속받은 전용 컴포넌트들을 통해 '바바'의 특수 로직을 처리합니다.

## 2. 핵심 구현 클래스 (Core Classes)
### [UginaEngine_SOURCE] - 엔진 확장
1. **`Animation` & `Animator`**: 
   - `CreateAnimation` 함수에 `vertical` 파라미터를 추가하여 세로 방향 스프라이트 시트를 지원합니다.
   - 이를 통해 바바 특유의 꿈틀거리는(Wobble) 효과를 구현할 수 있게 되었습니다.

### [UginaEngine_Window] - 게임 로직
1. **`BabaGridComponent`**: 객체의 격자 좌표, 이름, 속성을 관리합니다.
2. **`BabaGridManager`**: 이동, 규칙 파싱, 규칙 적용, Undo 시스템을 총괄합니다.
   - `ParseRules`: [NOUN] - [IS] - [PROPERTY/NOUN] 문장을 격자에서 찾아 규칙을 생성합니다.
   - `ApplyRules`: 파싱된 규칙을 기반으로 모든 객체의 속성을 실시간으로 갱신합니다.
3. **`BabaPlayerScript`**:
   - `W, S, A, D` 키 입력을 처리합니다.
   - 이동 시마다 애니메이션 인덱스(`_0`~`_3`)를 순환시켜 움직이는 애니메이션 효과를 줍니다.
4. **`BabaWordComponent`**: 객체를 단어 블록으로 식별하며, `WordType`에 따라 카테고리를 자동 반환합니다.

## 3. 리소스 및 애니메이션 설정 (Assets)
- **바바 리소스**: `babaDown.png`, `babaLeft.png`, `babaRight.png`, `babaUp.png` (96x72, 개별 24x24) 연동 완료.
- **꿈틀거림 효과**: 한 방향당 4개의 애니메이션 시트를 생성하고, 각 시트는 세로로 3프레임의 꿈틀거림을 포함합니다.
- **스케일**: 24x24 리소스를 48x48 격자 크기에 맞게 2.0f 스케일로 적용했습니다.

## 4. 현재 진행 상태 (Current Status)
- `BabaScene`에 `BABA` 플레이어와 `BABA`, `IS`, `YOU` 단어 블록이 배치되었습니다.
- 단어 블록들은 화면 확인을 위해 임시로 `Player.bmp` 이미지를 사용 중입니다.
- **이슈**: `W, S, A, D` 입력 시 애니메이션 인덱스는 바뀌는 것으로 보이나, 실제 캐릭터 이동이 발생하지 않고 있습니다.

## 5. 다음 할 일 (Next Steps)
1. **이동 불가 원인 분석**:
   - `ParseRules`가 `BABA IS YOU`를 정상적으로 인식하여 `YOU` 속성을 부여하는지 검증.
   - `BabaGridManager::TryMove` 내부의 좌표 업데이트 로직 확인.
2. **단어 블록 리소스 교체**: 실제 글자 이미지를 로드하여 맵에 표시.
3. **벽(Wall) 및 바위(Rock) 배치**: `STOP`, `PUSH` 속성 테스트.
4. **승리 조건**: `WIN` 속성 처리 및 레벨 클리어 시스템 구축.

---
*마지막 업데이트: 2026-03-20 (Wobble 애니메이션 및 단어 블록 배치 추가)*
