#include "pch.h"
#include "CppUnitTest.h"
#include "Actor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CActorTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCActorConstructName)
		{
			// Create an actor named "Sparty"
			// Make sure the getter and constructor work as intended
			CActor actor(L"Sparty");
			Assert::AreEqual(actor.GetName(), std::wstring(L"Sparty"));
		}

		TEST_METHOD(TestCActorEnabled)
		{
			// Create an actor
			// Make sure the default value for mEnabled is true
			CActor actor(L"Sparty");
			Assert::AreEqual(actor.IsEnabled(), true);

			// Test setter and getter for mEnabled
			actor.SetEnabled(false);
			Assert::AreEqual(actor.IsEnabled(), false);
			actor.SetEnabled(true);
			Assert::AreEqual(actor.IsEnabled(), true);
		}

		TEST_METHOD(TestCActorClickable)
		{
			// Create an actor
			// Make sure the default value for mClickable is true
			CActor actor(L"Sparty");
			Assert::AreEqual(actor.IsClickable(), true);

			// Test setter and getter for mClickable
			actor.SetClickable(false);
			Assert::AreEqual(actor.IsClickable(), false);
			actor.SetClickable(true);
			Assert::AreEqual(actor.IsClickable(), true);
		}

		TEST_METHOD(TestCActorPosition)
		{
			// Create an actor
			// Make sure the default value for mPosition is (0,0)
			CActor actor(L"Sparty");
			Gdiplus::Point testPoint1(0, 0);
			Assert::AreEqual(actor.GetPosition().X, testPoint1.X);
			Assert::AreEqual(actor.GetPosition().Y, testPoint1.Y);

			// Test setter and getter for mPosition
			actor.SetPosition(Gdiplus::Point(123, 456));
			Gdiplus::Point testPoint2(123, 456);
			Assert::AreEqual(actor.GetPosition().X, testPoint2.X);
			Assert::AreEqual(actor.GetPosition().Y, testPoint2.Y);
		}

	};
}