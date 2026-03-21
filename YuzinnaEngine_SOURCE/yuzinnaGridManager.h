#pragma once
#include "CommonInclude.h"
#include "yuzinnaGameObject.h"

namespace yuzinna
{
	enum class eBabaProperty
	{
		NONE = 0,
		YOU,    // ?닿? 議곗쥌??
		PUSH,   // 諛 ???덉쓬
		STOP,   // 留됲옒
		WIN,    // ?우쑝硫??밸━
		SINK,   // ?우쑝硫?媛숈씠 ?щ씪吏?
		PULL,   // ?밴만 ???덉쓬
		END
	};

	class GridManager
	{
	public:
		// ?꾩옱 ?ъ쓽 ?뱀젙 ?꾩튂(GridIndex)???덈뒗 紐⑤뱺 ?ㅻ툕?앺듃瑜?媛?몄샃?덈떎.
		static std::vector<GameObject*> GetObjectsAt(math::Vector2 gridIndex);

		// ?뱀젙 ?꾩튂???뱀젙 ?띿꽦(STOP, PUSH ????媛吏??ㅻ툕?앺듃媛 ?덈뒗吏 ?뺤씤?⑸땲??
		static bool HasProperty(math::Vector2 gridIndex, eBabaProperty property);

		// ?뱀젙 ?꾩튂???덈뒗 臾쇱껜??以??뱀젙 ?띿꽦??媛吏?臾쇱껜留?怨⑤씪?낅땲??
		static std::vector<GameObject*> GetObjectsWithProperty(math::Vector2 gridIndex, eBabaProperty property);

		// 寃⑹옄 ?대룞???쒕룄?⑸땲??(?ш??곸쑝濡?誘몃뒗 濡쒖쭅 ?ы븿).
		static bool TryMove(GameObject* obj, math::Vector2 direction);

	private:
		// ?ㅼ젣 ?대룞???섑뻾?섍퀬 ?붾㈃ 醫뚰몴(Transform)瑜??낅뜲?댄듃?⑸땲??
		static void moveObject(GameObject* obj, math::Vector2 nextGridPos);
	};
}
