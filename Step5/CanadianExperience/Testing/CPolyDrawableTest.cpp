#include "pch.h"
#include "CppUnitTest.h"
#include "PolyDrawable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CPolyDrawableTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCPolyDrawableConstructName)
		{
			// Create a PolyDrawable with name "SpartyBody"
			// Test the getter inherited from Drawable
			CPolyDrawable poly(L"SpartyBody");
			Assert::AreEqual(poly.GetName(), std::wstring(L"SpartyBody"));
		}

		TEST_METHOD(TestCPolyDrawableColor)
		{
			// Create a PolyDrawable
			CPolyDrawable poly(L"SpartyBody");

			// Test default value of mColor
			Gdiplus::Color defaultColor = Gdiplus::Color::Black;
			Assert::AreEqual(poly.GetColor().GetValue(), defaultColor.GetValue());

			// Test setter and getter for mColor
			poly.SetColor(Gdiplus::Color::Green);
			Gdiplus::Color testColor1 = Gdiplus::Color::Green;
			Assert::AreEqual(poly.GetColor().GetValue(), testColor1.GetValue());
		}

	};
}