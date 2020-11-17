#include "pch.h"
#include "CppUnitTest.h"
#include "AnimChannelAngle.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CAnimChannelAngleTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCAnimChannelAngleConstruct)
		{
			CAnimChannelAngle channel;
		}

		TEST_METHOD(TestCAnimChannelAngleName)
		{
			CAnimChannelAngle channel;

			// Test setter and getter of mName
			channel.SetName(L"TestName");
			Assert::AreEqual(channel.GetName().c_str(), L"TestName");

			// Test setter and getter of mName a second time
			channel.SetName(L"SecondTest!");
			Assert::AreEqual(channel.GetName().c_str(), L"SecondTest!");
		}

	};
}