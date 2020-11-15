#include "pch.h"
#include "CppUnitTest.h"
#include "TowerGame.h"
#include "TowerEight.h"
#include "TowerCustom.h"
#include "TowerBomb.h"
#include "TowerRing.h"
#include "Tile.h"
#include "TileBuilding.h"
#include "TileGrass.h"
#include "TileRoad.h"
#include "TileTrees.h"
#include "Item.h"
#include <memory>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	class CTestVisitor : public CItemVisitor
	{
	public:
		virtual void VisitRoad(CTileRoad* road) { mNumRoads++; }
		virtual void VisitBuilding(CTileBuilding* building) { mNumBuildings++; }
		virtual void VisitGrass(CTileGrass* grass) { mNumGrass++; }
		virtual void VisitTrees(CTileTrees* trees) { mNumTrees++; }
		virtual void VisitBalloon(CBalloon* balloon) { mNumNonTiles++; }
		virtual void VisitTowerEight(CTowerEight* towereight) { mNumNonTiles++; }
		virtual void VisitTowerRing(CTowerRing* towerring) { mNumNonTiles++; }
		virtual void VisitTowerBomb(CTowerBomb* towerbomb) { mNumNonTiles++; }
		virtual void VisitTowerCustom(CTowerCustom* towercustom) { mNumNonTiles++; }

		int mNumRoads = 0;
		int mNumBuildings = 0;
		int mNumTrees = 0;
		int mNumGrass = 0;
		int mNumNonTiles = 0;
	};

	TEST_CLASS(CTowerGameTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCTowerGameHitTest)
		{
			CTowerGame towerGame;

			Assert::IsTrue(towerGame.HitTest(100, 200) == nullptr,
				L"Testing empty game");

			shared_ptr<CTowerEight> tower8 = make_shared<CTowerEight>(&towerGame);
			tower8->SetLocation(100, 200);
			towerGame.AddItem(tower8);

			Assert::IsTrue(towerGame.HitTest(100, 200) == tower8,
				L"Testing tower8 at 100, 200");

			/// Testing spot of populated Game with no items
			Assert::IsTrue(towerGame.HitTest(0, 0) == nullptr,
				L"Testing spot in game with no items");
		}
		TEST_METHOD(TestCItemVisitor)
		{
			// Construct a city object
			CTowerGame game;

			// Add some tiles of each time
			auto tile1 = make_shared<CTileRoad>(&game);
			auto tile2 = make_shared<CTileBuilding>(&game);
			auto tile3 = make_shared<CTileGrass>(&game);
			auto tile4 = make_shared<CTileTrees>(&game);
			auto balloon = make_shared<CBalloon>(&game, 1, 1, 1);
			auto towereight = make_shared<CTowerEight>(&game);
			auto towerring = make_shared<CTowerRing>(&game);
			auto towercustom = make_shared<CTowerCustom>(&game);
			auto towerbomb = make_shared<CTowerBomb>(&game);

			game.AddItem(tile1);
			game.AddItem(tile2);
			game.AddItem(tile3);
			game.AddItem(tile4);
			game.AddItem(balloon);
			game.AddItem(towereight);
			game.AddItem(towerring);
			game.AddItem(towerbomb);
			game.AddItem(towercustom);

			CTestVisitor visitor;
			game.Accept(&visitor);
			Assert::AreEqual(1, visitor.mNumRoads,
				L"Visitor number of roads");
			Assert::AreEqual(1, visitor.mNumBuildings,
				L"Visitor number of buildings");
			Assert::AreEqual(1, visitor.mNumTrees,
				L"Visitor number of trees");
			Assert::AreEqual(1, visitor.mNumGrass,
				L"Visitor number of grass");
			Assert::AreEqual(5, visitor.mNumNonTiles,
				L"Visitor number of non Tiles");

		}

	};
}