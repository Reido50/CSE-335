#include "pch.h"
#include "CppUnitTest.h"
#include "Drawable.h"
#include <string>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	class CDrawableMock : public CDrawable
	{
	public:
		CDrawableMock(const std::wstring& name) : CDrawable(name) {}
		virtual void Draw(Gdiplus::Graphics* graphics) {}
		virtual bool HitTest(Gdiplus::Point pos) { return false; }
	};

	TEST_CLASS(CDrawableTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCDrawableConstructName)
		{
			// Create a drawable named "SpartyHead"
			// Make sure the getter and constructor work as intended
			CDrawableMock drawable(L"SpartyHead");
			Assert::AreEqual(drawable.GetName(), std::wstring(L"SpartyHead"));
		}

		TEST_METHOD(TestCDrawablePosition)
		{
			// Create a drawable
			// Make sure the default value for mPosition is (0,0)
			CDrawableMock drawable(L"SpartyHead");
			Gdiplus::Point testPoint1(0, 0);
			Assert::AreEqual(drawable.GetPosition().X, testPoint1.X);
			Assert::AreEqual(drawable.GetPosition().Y, testPoint1.Y);

			// Test getter and setter for mPosition
			drawable.SetPosition(Gdiplus::Point(123, 456));
			Gdiplus::Point testPoint2(123, 456);
			Assert::AreEqual(drawable.GetPosition().X, testPoint2.X);
			Assert::AreEqual(drawable.GetPosition().Y, testPoint2.Y);
		}

		TEST_METHOD(TestCDrawableRotation)
		{
			// Create a drawable
			// Make sure the default value for mRotation is 0
			CDrawableMock drawable(L"SpartyHead");
			Assert::AreEqual(drawable.GetRotation(), 0.0, 0.00001);

			// Test getter and setter for mRotation
			drawable.SetRotation(1.23);
			Assert::AreEqual(drawable.GetRotation(), 1.23, 0.00001);
		}

		TEST_METHOD(TestCDrawableAssociation)
		{
			CDrawableMock body(L"Body");
			auto arm = std::make_shared<CDrawableMock>(L"Arm");
			auto leg = std::make_shared<CDrawableMock>(L"Leg");

			Assert::IsNull(arm->GetParent());
			Assert::IsNull(leg->GetParent());

			body.AddChild(arm);
			body.AddChild(leg);

			Assert::IsTrue(arm->GetParent() == &body);
			Assert::IsTrue(leg->GetParent() == &body);
		}

	};
}