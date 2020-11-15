#include "pch.h"
#include "CppUnitTest.h"
#include "Balloon.h"
#include "TowerGame.h"
#include "TileRoad.h"
#include <memory>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CBalloonTest)
	{
	public:
		
		TEST_METHOD(TestConstructor)
		{
			// Create a tower game with 1 balloon in it
			CTowerGame towerGame;
			auto balloon = make_shared<CBalloon>(&towerGame, 5, 6, 1);
			towerGame.AddItem(balloon);

			// Position and Speed set correctly
			Assert::AreEqual(5, balloon->GetPosition(), 0.0001);

			Assert::AreEqual(6, balloon->GetSpeed(), 0.0001);

			// Test balloon's position is set correctly
			balloon->SetLocation(100, 100);
			Assert::IsTrue(balloon->HitTest(100, 100));
		}

		TEST_METHOD(TestPlaceAtStart)
		{
			// Make a game
			CTowerGame towerGame;

			// Make a starting roadtile 
			auto roadTile = make_shared<CTileRoad>(&towerGame);
			roadTile->SetLocation(500, 500);
			roadTile->SetIsStart(true);
			roadTile->SetType(L"EW");
			towerGame.AddItem(roadTile);

			// Make a balloon and add it to the game
			auto balloon = make_shared<CBalloon>(&towerGame, 0, 128, 1);
			towerGame.AddBalloon(balloon);

			// Test if balloon appeared at the start
			towerGame.Update(0.01);
			Assert::IsTrue(balloon->HitTest(500, 500));
		}
	};
}
