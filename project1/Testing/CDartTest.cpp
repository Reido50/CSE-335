#include "pch.h"
#include "CppUnitTest.h"
#include "Dart.h"
#include "TowerGame.h"
#include <memory>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CDartTest)
	{
	public:
		
		TEST_METHOD(TestConstructor)
		{
			// Create a tower game with 1 dart in it
			CTowerGame towerGame;
			auto towerEight = make_shared<CTowerEight>(&towerGame);

			auto dart = make_shared<CDart>(&towerGame, towerEight.get(), 10.9, 9.8, 8.7);
			towerGame.AddItem(dart);

			// Speed, Angle, DistanceFromTower set correctly
			Assert::AreEqual(10.9, dart->GetSpeed(), 0.0001);

			Assert::AreEqual(9.8, dart->GetAngle(), 0.0001);

			Assert::AreEqual(8.7, dart->GetDistanceFromTower(), 0.0001);

			// Test dart's position is set correctly
			dart->SetLocation(100, 100);
			Assert::IsTrue(dart->HitTest(100, 100));
		}
	};
}
