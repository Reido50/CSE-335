#include <memory>
#include "pch.h"
#include "CppUnitTest.h"
#include "Aquarium.h"
#include "FishBeta.h"
#include "FishAngler.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CAquariumTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCAquariumConstruct)
		{
			CAquarium aquarium;
		}

		TEST_METHOD(TestCAquariumHitTest)
		{
			CAquarium aquarium;

			// Fish has not been clicked on and the test returns nullptr
			Assert::IsTrue(aquarium.HitTest(100, 200) == nullptr,
				L"Testing empty aquarium");

			shared_ptr<CFishBeta> fish1 = make_shared<CFishBeta>(&aquarium);
			fish1->SetLocation(100, 200);
			aquarium.Add(fish1);

			// Fish has been clicked and the test returns the correct ptr
			Assert::IsTrue(aquarium.HitTest(100, 200) == fish1,
				L"Testing fish at 100, 200");

			// Two fish are stacked on top of each other.
			// Must return the ptr to the fish on top
			auto fish2 = make_shared<CFishBeta>(&aquarium);
			fish2->SetLocation(100, 200);
			aquarium.Add(fish2);
			Assert::IsTrue(aquarium.HitTest(100, 200) == fish2, L"Testing for the top fish at 100, 200");

			// Fish exist in the aquarium but a click was not on one
			// Should return nullptr
			Assert::IsTrue(aquarium.HitTest(100, 10) == nullptr, L"Testing a miss");
		}

		TEST_METHOD(TestCAquariumMoveToFront)
		{	
			// Make an aquarium with 2 fish stacked on top of each other
			// fish2 should be in front of fish1
			CAquarium aquarium;
			auto fish1 = make_shared<CFishBeta>(&aquarium);
			fish1->SetLocation(200, 200);
			aquarium.Add(fish1);
			auto fish2 = make_shared<CFishBeta>(&aquarium);
			fish2->SetLocation(200, 200);
			aquarium.Add(fish2);

			// Make sure fish2 is getting hit because it is in front
			Assert::IsTrue(aquarium.HitTest(200, 200) == fish2, L"Testing the fish in front will be hit");

			// Move fish1 to the front and check if it is getting 
			// hit before fish2
			aquarium.MoveToFront(fish1);
			Assert::IsTrue(aquarium.HitTest(200, 200) == fish1, 
				L"Testing the fish moved to the front will be hit");

			// Move fish2 to the front and check if it is getting
			// hit before fish1
			// The reverse of the previous test
			aquarium.MoveToFront(fish2);
			Assert::IsTrue(aquarium.HitTest(200, 200) == fish2,
				L"Testing the fish moved to the front will be hit");
		}

		TEST_METHOD(TestCAquariumCatchTest)
		{
			CAquarium aquarium;
			auto beta = make_shared<CFishBeta>(&aquarium);
			beta->SetLocation(200, 200);
			aquarium.Add(beta);
			auto angler = make_shared<CFishAngler>(&aquarium);
			angler->SetLocation(400, 200);
			aquarium.Add(angler);

			Assert::IsTrue(aquarium.CatchTest(angler->GetX(), angler->GetY()) == nullptr,
				L"Testing the beta is out of the angler's range");

			angler->SetLocation(350, 200);

			Assert::IsTrue(aquarium.CatchTest(angler->GetX(), angler->GetY()) == beta,
				L"Testing the beta gets caught correctly");
		}
	};
}