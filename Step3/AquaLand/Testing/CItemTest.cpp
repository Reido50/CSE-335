#include "pch.h"
#include "CppUnitTest.h"

#include "Item.h"
#include "Aquarium.h"

#include<string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

/// Fish filename
const std::wstring FishBetaImageName = L"images/beta.png";

namespace Testing
{
	/** Mock class for testing CItem */
	class CItemMock : public CItem
	{
	public:
		/** Constructor
		 * \param aquarium The aquarium this is a meber of */
		CItemMock(CAquarium *aquarium) : 
			CItem(aquarium, FishBetaImageName){}

		/** Draw the item
		 * \param graphics The graphics context to draw on */
		virtual void Draw(Gdiplus::Graphics* graphics) {}
	};

	TEST_CLASS(CItemTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCItemConstruct)
		{
			// Construct an item to test
			CAquarium aquarium;
			CItemMock item(&aquarium);
		}

		TEST_METHOD(TestCITemGettersSetters)
		{
			// Construct an item to test
			CAquarium aquarium;
			CItemMock item(&aquarium);

			// Test initial values
			Assert::AreEqual(0, item.GetX(), 0);
			Assert::AreEqual(0, item.GetY(), 0);

			// Test SetLocation, GetX, and GetY
			item.SetLocation(10.5, 17.2);
			Assert::AreEqual(10.5, item.GetX(), 0.0001);
			Assert::AreEqual(17.2, item.GetY(), 0.0001);

			// Test a second with different values
			item.SetLocation(-72, -107);
			Assert::AreEqual(-72, item.GetX(), 0.0001);
			Assert::AreEqual(-107, item.GetY(), 0.0001);
		}

		TEST_METHOD(TestCItemBetaHitTest)
		{
			// Create a fish to test
			CAquarium aquarium;
			CItemMock item(&aquarium);

			// Give it a location
			// Always make the numbers different, in case they are mixed up
			item.SetLocation(100, 200);

			// Center of the fish should be a true
			Assert::IsTrue(item.HitTest(100, 200));

			// Left of the Fish
			Assert::IsFalse(item.HitTest(10, 200));

			// Right of the Fish
			Assert::IsFalse(item.HitTest(200, 200));

			// Above the fish
			Assert::IsFalse(item.HitTest(100, 0));

			// Below the fish
			Assert::IsFalse(item.HitTest(100, 300));

			// Of fish transparent pixel
			Assert::IsFalse(item.HitTest(100 - 125 / 2 + 17, 200 - 117 / 2 + 16));
		}

	};
}