#include <memory>
#include "pch.h"
#include "CppUnitTest.h"
#include "PictureObserver.h"
#include "Picture.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	class CPictureObserverMock : public CPictureObserver
	{
	public:
		CPictureObserverMock() : CPictureObserver(){}
		virtual void UpdateObserver() override { mUpdated = true; }

		bool mUpdated = false;
	};

	TEST_CLASS(CPictureObserverTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCPictureObserverConstruct)
		{
			CPictureObserverMock observer;
		}

		TEST_METHOD(TestCPictureObserverOneObserver)
		{
			// Allocate a CPicture object
			shared_ptr<CPicture> picture = make_shared<CPicture>();

			// Create a mock observer object
			CPictureObserverMock observer;

			// And set it for the observer:
			observer.SetPicture(picture);

			picture->UpdateObservers();

			Assert::IsTrue(observer.mUpdated);
		}

		TEST_METHOD(TestCPictureObserverGetPicture)
		{
			// Create a picture with an observer
			shared_ptr<CPicture> picture = make_shared<CPicture>();
			CPictureObserverMock observer;
			observer.SetPicture(picture);

			Assert::IsFalse(nullptr == observer.GetPicture().get());
			Assert::IsTrue(picture.get() == observer.GetPicture().get());
		}

		TEST_METHOD(TestCPictureObserverMultipleObserver)
		{
			// Create a picture with two observers
			shared_ptr<CPicture> picture = make_shared<CPicture>();
			CPictureObserverMock observer1;
			observer1.SetPicture(picture);
			CPictureObserverMock observer2;
			observer2.SetPicture(picture);

			// Test updating multiple observers
			picture->UpdateObservers();

			Assert::IsTrue(observer1.mUpdated);
			Assert::IsTrue(observer2.mUpdated);
		}

		TEST_METHOD(TestCPictureObserverDestruction)
		{
			// Create a picture with an observer
			shared_ptr<CPicture> picture = make_shared<CPicture>();
			CPictureObserverMock observer1;
			observer1.SetPicture(picture);

			// Create and destroy an observer
			{
				CPictureObserverMock observer2;
				observer2.SetPicture(picture);
			}

			// Try to update the observers
			// Hopefully observer2 was removed from the list
			// of observers upon destruction and won't cause
			// a nullptr error
			picture->UpdateObservers();
		}
	};
}