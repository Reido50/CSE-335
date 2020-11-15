#include "pch.h"
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include "CppUnitTest.h"
#include "Aquarium.h"
#include "FishBeta.h"
#include "FishStinky.h"
#include "FishSparty.h"
#include "DecorCastle.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CAquariumTest)
	{
	public:

		/**
		* Create a path to a place to put temporary files
		*/
		wstring TempPath()
		{
			// Create a path to temporary files
			wchar_t path_nts[MAX_PATH];
			GetTempPath(MAX_PATH, path_nts);

			// Convert null terminated string to wstring
			return wstring(path_nts);
		}

		/**
		* Read a file into a wstring and return it.
		* \param filename Name of the file to read
		* \return File contents
		*/
		wstring ReadFile(const wstring& filename)
		{
			ifstream t(filename);
			wstring str((istreambuf_iterator<char>(t)),
				istreambuf_iterator<char>());

			return str;
		}

		/**
		* Test to ensure an aquarium .aqua file is empty
		*/
		void TestEmpty(wstring filename)
		{
			Logger::WriteMessage(filename.c_str());

			wstring xml = ReadFile(filename);
			Logger::WriteMessage(xml.c_str());

			Assert::IsTrue(regex_search(xml, wregex(L"<\\?xml.*\\?>")));
			Assert::IsTrue(regex_search(xml, wregex(L"<aqua/>")));
		}

		/**
		* Populate an aquarium with three beta fish
		*/
		void PopulateThreeBetas(CAquarium* aquarium)
		{
			auto fish1 = make_shared<CFishBeta>(aquarium);
			fish1->SetLocation(100, 200);
			fish1->SetSpeedX(10);
			fish1->SetSpeedY(11);
			aquarium->Add(fish1);

			auto fish2 = make_shared<CFishBeta>(aquarium);
			fish2->SetLocation(400, 400);
			fish2->SetSpeedX(12);
			fish2->SetSpeedY(13);
			aquarium->Add(fish2);

			auto fish3 = make_shared<CFishBeta>(aquarium);
			fish3->SetLocation(600, 100);
			fish3->SetSpeedX(14);
			fish3->SetSpeedY(15);
			aquarium->Add(fish3);
		}

		/**
		* Populate an aquarium with all the item types
		*/
		void PopulateAllTypes(CAquarium* aquarium)
		{
			auto beta = make_shared<CFishBeta>(aquarium);
			beta->SetLocation(100, 200);
			beta->SetSpeedX(10);
			beta->SetSpeedY(11);
			aquarium->Add(beta);

			auto stinky = make_shared<CFishStinky>(aquarium);
			stinky->SetLocation(400, 400);
			stinky->SetSpeedX(12);
			stinky->SetSpeedY(13);
			aquarium->Add(stinky);

			auto sparty = make_shared<CFishSparty>(aquarium);
			sparty->SetLocation(600, 100);
			sparty->SetSpeedX(14);
			sparty->SetSpeedY(15);
			aquarium->Add(sparty);

			auto castle = make_shared<CDecorCastle>(aquarium);
			castle->SetLocation(300, 600);
			aquarium->Add(castle);
		}

		/**
		* Test the saving of an aquarium with 3 beta fish 
		*/
		void TestThreeBetas(wstring filename)
		{
			Logger::WriteMessage(filename.c_str());

			wstring xml = ReadFile(filename);
			Logger::WriteMessage(xml.c_str());

			// Ensure three items
			Assert::IsTrue(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*</aqua>")));

			// Ensure the positions and speeds are correct
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"100\" y=\"200\" speedx=\"10\" speedy=\"11\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"400\" y=\"400\" speedx=\"12\" speedy=\"13\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"600\" y=\"100\" speedx=\"14\" speedy=\"15\"")));
			
			// Ensure the types are correct
			Assert::IsTrue(regex_search(xml,
				wregex(L"<aqua><item.* type=\"beta\"/><item.* type=\"beta\"/><item.* type=\"beta\"/></aqua>")));
		}

		/**
		* Test the saving of an aquarium with all item types
		*/
		void TestAllTypes(wstring filename)
		{
			Logger::WriteMessage(filename.c_str());

			wstring xml = ReadFile(filename);
			Logger::WriteMessage(xml.c_str());

			// Ensure four items
			Assert::IsTrue(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*<item.*</aqua>")));

			// Ensure the positions are correct
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"100\" y=\"200\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"400\" y=\"400\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"600\" y=\"100\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"300\" y=\"600\"")));

			// Ensure the types are correct
			Assert::IsTrue(regex_search(xml,
				wregex(L"<aqua><item.* type=\"beta\"/><item.* type=\"stinky\"/><item.* type=\"sparty\"/><item.* type=\"castle\"/></aqua>")));
		}

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

		TEST_METHOD(TestCAquariumSave)
		{
			// Create a path to temporary files
			wstring path = TempPath();

			// Create aquarium
			CAquarium aquarium, aquarium2;

			//
			// First test, saving an empty aquarium
			//
			wstring file1 = path + L"test1.aqua";
			aquarium.Save(file1);

			TestEmpty(file1);

			aquarium2.Load(file1);
			aquarium2.Save(file1);
			TestEmpty(file1);

			// 
			// Now populate the aquarium
			//

			PopulateThreeBetas(&aquarium);

			wstring file2 = path + L"test2.aqua";
			aquarium.Save(file2);
			TestThreeBetas(file2);

			aquarium2.Load(file2);
			aquarium2.Save(file2);
			TestThreeBetas(file2);

			//
			// Test all types
			//
			CAquarium aquarium3;
			PopulateAllTypes(&aquarium3);

			wstring file3 = path + L"test3.aqua";
			aquarium3.Save(file3);
			TestAllTypes(file3);

			aquarium2.Load(file3);
			aquarium2.Save(file3);
			TestAllTypes(file3);

			//
			// Test clearing the items
			//
			aquarium3.Clear();

			wstring file4 = path + L"test4.aqua";
			aquarium3.Save(file4);
			TestEmpty(file4);
		}
	};
}