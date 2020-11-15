#include "pch.h"
#include "CppUnitTest.h"
#include "XmlLoader.h"
#include "TowerGame.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(XmlLoaderTest)
	{
	public:
		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}

		TEST_METHOD(TestLoad)
		{
			CTowerGame towerGame;
			CXmlLoader loader = CXmlLoader(&towerGame);

			// Validating file was opened
			bool result = loader.Load(L"../levels/level0.xml");
			Assert::IsTrue(result);

			auto size = towerGame.GetSize();
		}
	};
}