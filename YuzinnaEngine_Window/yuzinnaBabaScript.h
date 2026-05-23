#pragma once
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaScript.h"

namespace yuzinna
{
	class BabaScript : public Script
	{
	public:
		BabaScript();
		~BabaScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC hdc) override;

		int GetVersion() { return mVersion; }
		void SetVersion(int version) { mVersion = version; }

	private:
		int mVersion;
		float mWinTimer;
		bool mbWin;
	};

}
