#include "pch.h"
#include "CppUnitTest.h"
#include "TowerGame.h"
#include "TowerEight.h"
#include "TowerCustom.h"
#include "TowerBomb.h"
#include "TowerRing.h"
#include <memory>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CTowerTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestTowerConstructor)

			{
				// Create a tower game with all towers in it
				CTowerGame towerGame;
				auto tower8 = make_shared<CTowerEight>(&towerGame);
				tower8->SetLocation(100, 200);
				towerGame.AddItem(tower8);

				auto towerbomb = make_shared<CTowerBomb>(&towerGame);
				towerGame.AddItem(towerbomb);

				auto towerring = make_shared<CTowerRing>(&towerGame);
				towerGame.AddItem(towerring);

				auto towercustom = make_shared<CTowerCustom>(&towerGame);
				towerGame.AddItem(towercustom);

				// Test tower's position is set correctly
				Assert::IsTrue(tower8->HitTest(100, 200));
				Assert::IsFalse(tower8->HitTest(200, 100));

		}
	};
}