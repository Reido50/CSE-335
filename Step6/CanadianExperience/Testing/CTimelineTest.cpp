#include "pch.h"
#include "CppUnitTest.h"
#include "Timeline.h"
#include "AnimChannelAngle.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CTimelineTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCTimelineFrames)
		{
			CTimeline timeline;

			// Test default mNumFrames value
			Assert::AreEqual(timeline.GetNumFrames(), 300);

			// Test setting a new mNumFrames value
			timeline.SetNumFrames(123);
			Assert::AreEqual(timeline.GetNumFrames(), 123);

			// Test setting a new mNumFrames value a second time
			timeline.SetNumFrames(456);
			Assert::AreEqual(timeline.GetNumFrames(), 456);
		}

		TEST_METHOD(TestCTimelineFrameRate)
		{
			CTimeline timeline;

			// Test default mFrameRate value
			Assert::AreEqual(timeline.GetFrameRate(), 30);

			// Test setting a new mFrameRate value
			timeline.SetFrameRate(60);
			Assert::AreEqual(timeline.GetFrameRate(), 60);

			// Test setting a new mFrameRate value a second time
			timeline.SetFrameRate(144);
			Assert::AreEqual(timeline.GetFrameRate(), 144);
		}

		TEST_METHOD(TestCTimelineCurrentTime)
		{
			CTimeline timeline;

			// Test default mCurrentTime value
			Assert::AreEqual(timeline.GetCurrentTime(), 0.0);

			// Test setting a new mCurrentTime value
			timeline.SetCurrentTime(20);
			Assert::AreEqual(timeline.GetCurrentTime(), 20.0);

			// Test setting a new mCurrentTime value a second time
			timeline.SetCurrentTime(50);
			Assert::AreEqual(timeline.GetCurrentTime(), 50.0);
		}

		TEST_METHOD(TestCTimelineGetDuration)
		{
			CTimeline timeline;

			// Default value
			Assert::AreEqual(10, timeline.GetDuration(), 0.0001);

			// Changed duration
			timeline.SetFrameRate(375);
			Assert::AreEqual(300.0 / 375.0, timeline.GetDuration(), 0.0001);

			timeline.SetNumFrames(789);
			Assert::AreEqual(789.0 / 375.0, timeline.GetDuration(), 0.0001);
		}

		TEST_METHOD(TestCTimelineGetCurrentFrame)
		{
			CTimeline timeline;

			// Default value
			Assert::AreEqual(0, timeline.GetCurrentFrame());

			// Changed time
			timeline.SetCurrentTime(9.27);
			Assert::AreEqual(278, timeline.GetCurrentFrame());
		}

		TEST_METHOD(TestCTimelineAdd)
		{
			CTimeline timeline;
			CAnimChannelAngle channel;

			timeline.AddChannel(&channel);
			Assert::IsTrue(&timeline == channel.GetTimeline());
		}
	};
}