

#include "pch.h"
#include "CppUnitTest.h"
#include "TowerGame.h"
#include "Tile.h"
#include "TileBuilding.h"
#include "TileGrass.h"
#include "TileRoad.h"
#include "TileTrees.h"
#include <memory>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CTileTest)
	{
	public:
		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}

		TEST_METHOD(TestRoadConstructor)
		{
			//// Create a tower game
			CTowerGame towerGame;

			auto roadTile = make_shared<CTileRoad>(&towerGame);
			roadTile->SetLocation(100, 500);
			towerGame.AddItem(roadTile);
			Assert::IsTrue(roadTile->HitTest(100, 500));
		}

		TEST_METHOD(TestBuildingConstructor)
		{
			//// Create a tower game
			CTowerGame towerGame;

			auto buildingTile = make_shared<CTileBuilding>(&towerGame);
			buildingTile->SetLocation(200, 500);
			towerGame.AddItem(buildingTile);
			Assert::IsTrue(buildingTile->HitTest(200, 500));
		}

		TEST_METHOD(TestGrassConstructor)
		{
			//// Create a tower game
			CTowerGame towerGame;

			auto grassTile = make_shared<CTileGrass>(&towerGame);
			grassTile->SetLocation(300, 500);
			towerGame.AddItem(grassTile);
			Assert::IsTrue(grassTile->HitTest(300, 500));
		}

		TEST_METHOD(TestTreesConstructor)
		{
			//// Create a tower game
			CTowerGame towerGame;

			auto treeTile = make_shared<CTileTrees>(&towerGame);
			treeTile->SetLocation(400, 500);
			towerGame.AddItem(treeTile);
			Assert::IsTrue(treeTile->HitTest(400, 500));
		}
	};
}
