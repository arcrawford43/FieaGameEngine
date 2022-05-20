#include "pch.h"
#include "ToStringSpecialization.h"
#include "GameTime.h"
#include "GameState.h"
#include "Event.h"
#include "EventQueue.h"
#include "EventSupportStructs.h"
#include "GameObject.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTests;
using namespace std;
using namespace std::string_literals;
using namespace std::chrono;
using namespace std::chrono_literals;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(EventTests)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#if defined(_DEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&_startMemState);
#endif
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
#if defined(_DEBUG)
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &_startMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
#endif
		}

		TEST_METHOD(RTTITest)
		{
			Foo foo(1);
			Event<Foo> event(foo);

			RTTI* rtti = &event;
			Assert::IsFalse(rtti->Is(Foo::TypeIdClass()));
			Assert::IsTrue(rtti->Is(Event<Foo>::TypeIdClass()));
			Assert::IsTrue(rtti->Is(EventPublisher::TypeIdClass()));
			Assert::IsTrue(rtti->Is(rtti->TypeIdInstance()));

			Foo* f = rtti->As<Foo>();
			Assert::IsNull(f);

			Event<Foo>* e = rtti->As<Event<Foo>>();
			Assert::IsNotNull(e);
			Assert::AreEqual(&event, e);

			EventPublisher* ep = rtti->As<EventPublisher>();
			Assert::IsNotNull(ep);
			Assert::AreEqual(static_cast<EventPublisher*>(&event), ep);

		}



		TEST_METHOD(EventQueueEnqueue)
		{
			GameTime gameTime;
			Foo foo(2);
			shared_ptr<FooSubscriber> fooSubscriber = make_shared<FooSubscriber>();
			EventQueue eventQueue;

			shared_ptr<Event<Foo>> event = make_shared<Event<Foo>>(foo);
			Assert::AreEqual(event->Message(), foo);

			Assert::AreEqual(size_t(0), eventQueue.Size());
			eventQueue.Enqueue(event, gameTime);
			Assert::AreEqual(size_t(1), eventQueue.Size());

			Event<Foo>::Subscribe(fooSubscriber);
			Event<Foo>::HandleChangeList();
			gameTime.SetCurrentTime(high_resolution_clock::time_point(1s));
			Assert::IsFalse(fooSubscriber->WasNotified);
			eventQueue.Update(gameTime);

			fooSubscriber->WasNotified = false;
			eventQueue.Update(gameTime);
			Assert::IsFalse(fooSubscriber->WasNotified);
			Assert::AreEqual(size_t(0), eventQueue.Size());

			gameTime.SetCurrentTime(high_resolution_clock::time_point());
			eventQueue.Enqueue(event, gameTime, 1s);
			gameTime.SetCurrentTime(high_resolution_clock::time_point(500ms));
			eventQueue.Update(gameTime);
			Assert::IsFalse(fooSubscriber->WasNotified);
			gameTime.SetCurrentTime(high_resolution_clock::time_point(1s));
			eventQueue.Update(gameTime);
			Assert::IsFalse(fooSubscriber->WasNotified);
			gameTime.SetCurrentTime(high_resolution_clock::time_point(2s));
			eventQueue.Update(gameTime);
			Assert::IsTrue(fooSubscriber->WasNotified);

			Assert::IsTrue(eventQueue.IsEmpty());
			Event<Foo>::UnsubscribeAll();
			Event<Foo>::HandleChangeList();

		}

		TEST_METHOD(EventQueueMultipleEvents)
		{
			shared_ptr<FooSubscriber> fooSubscriber = make_shared<FooSubscriber>();
			Event<Foo>::Subscribe(fooSubscriber);
			Event<Foo>::HandleChangeList();

			shared_ptr<Event<Foo>> event1 = make_shared<Event<Foo>>(Foo{ 0 });
			shared_ptr<Event<Foo>> event2 = make_shared<Event<Foo>>(Foo{ 0 });
			shared_ptr<Event<Foo>> event3 = make_shared<Event<Foo>>(Foo{ 0 });
			shared_ptr<Event<Foo>> event4 = make_shared<Event<Foo>>(Foo{ 0 });

			GameTime gameTime;
			EventQueue eventQueue;
			eventQueue.Enqueue(event1, gameTime, milliseconds(750));
			eventQueue.Enqueue(event2, gameTime);
			eventQueue.Enqueue(event3, gameTime);
			eventQueue.Enqueue(event4, gameTime, seconds(1));
			gameTime.SetCurrentTime(high_resolution_clock::time_point(500ms));
			eventQueue.Update(gameTime);
			Assert::AreEqual(size_t(2), fooSubscriber->Count);

			gameTime.SetCurrentTime(high_resolution_clock::time_point(1500ms));
			eventQueue.Update(gameTime);
			Assert::AreEqual(size_t(4), fooSubscriber->Count);

			Assert::IsTrue(eventQueue.IsEmpty());
			Event<Foo>::UnsubscribeAll();
			Event<Foo>::HandleChangeList();
		}

		TEST_METHOD(CopySemantics)
		{
			{
				Event<Foo> event(Foo {69});
				Event<Foo> anotherEvent(event);
				Assert::AreNotSame(event.Message(), anotherEvent.Message());
				Assert::AreEqual(event.Message(), anotherEvent.Message());
			}
			{
				Event<Foo> event(Foo {69});
				Event<Foo> anotherEvent(Foo{ 70 });
				anotherEvent = event;
				Assert::AreNotSame(event.Message(), anotherEvent.Message());
				Assert::AreEqual(event.Message(), anotherEvent.Message());
			}
		}

		TEST_METHOD(MoveSemantics)
		{
			{
				Event<Foo> event(Foo {1});
				Event<Foo> anotherEvent(move(event));
#pragma warning(push)
#pragma warning(disable:26800)
				Assert::IsFalse(&event.Message() == &anotherEvent.Message());
#pragma warning(pop)
			}
			{
				Event<Foo> event(Foo {1});
				Event<Foo> anotherEvent(Foo{ 2 });
				anotherEvent = move(event);
#pragma warning(push)
#pragma warning(disable:26800)
				Assert::IsFalse(&event.Message() == &anotherEvent.Message());
#pragma warning(pop)
			}
		}

		TEST_METHOD(EventQueueClear)
		{
			GameTime gameTime;
			EventQueue eventQueue;
			Assert::AreEqual(size_t(0), eventQueue.Size());

			const size_t eventCount = 4;
			for (size_t i = 0; i < eventCount; ++i)
			{
				eventQueue.Enqueue(make_shared<Event<Foo>>(Foo{ 69 }), gameTime);
			}

			Assert::AreEqual(eventCount, eventQueue.Size());
			eventQueue.Clear();
			Assert::AreEqual(size_t(0), eventQueue.Size());
		}
		
		TEST_METHOD(EventClearEvent)
		{
			GameTime gameTime;

			Foo f;
			shared_ptr<EventClearSubscriber> subscriber = make_shared<EventClearSubscriber>();
			FooSubscriber fooSubscriber1;
			shared_ptr<FooSubscriber> fooSubscriber = make_shared<FooSubscriber>();

			std::shared_ptr<Event<FooSubscriber>> eef = std::make_shared<Event<FooSubscriber>>(fooSubscriber1);
			std::shared_ptr<Event<Foo>> e = std::make_shared<Event<Foo>>(f);

			GameState::QueueEvents.Enqueue(eef, gameTime);
			GameState::QueueEvents.Enqueue(e, gameTime);

			Event<FooSubscriber>::Subscribe(subscriber);
			Event<Foo>::Subscribe(subscriber);

			Event<FooSubscriber>::HandleChangeList();
			Event<Foo>::HandleChangeList();
			GameState::QueueEvents.Update(gameTime);

			gameTime.SetCurrentTime(std::chrono::high_resolution_clock::time_point(1s));
			Assert::AreEqual((std::size_t)0, subscriber->Count);
			Assert::AreEqual(GameState::QueueEvents.Size(), (std::size_t)2);

			GameState::QueueEvents.Update(gameTime);
			Assert::AreEqual(GameState::QueueEvents.Size(), (std::size_t)0);
			Assert::AreEqual(2_z, subscriber->Count);
			GameState::QueueEvents.Update(gameTime);
			Assert::AreEqual(GameState::QueueEvents.Size(), (std::size_t)0);

			Event<FooSubscriber>::UnsubscribeAll();
			Event<Foo>::UnsubscribeAll();
			Event<FooSubscriber>::HandleChangeList();
			Event<Foo>::HandleChangeList();
		}
		TEST_METHOD(EventAddEvent)
		{
			GameTime gameTime;
			shared_ptr<EventEnqueueSubscriber> subscriber = make_shared<EventEnqueueSubscriber>();
			shared_ptr<FooSubscriber> fooSubscriber = make_shared<FooSubscriber>();
			std::shared_ptr<Event<FooSubscriber>> event1 = std::make_shared<Event<FooSubscriber>>(*fooSubscriber);
			GameState::QueueEvents.Enqueue(event1, gameTime);
			Event<FooSubscriber>::Subscribe(subscriber);
			Event<FooSubscriber>::HandleChangeList();
			gameTime.SetCurrentTime(std::chrono::high_resolution_clock::time_point(1s));
			Assert::AreEqual(std::size_t(0), subscriber->Count);
			GameState::QueueEvents.Update(gameTime);
			Assert::AreEqual(GameState::QueueEvents.Size(), std::size_t(1));
			Event<FooSubscriber>::HandleChangeList();
			Assert::AreEqual(std::size_t(1), subscriber->Count);
			Assert::AreEqual(GameState::QueueEvents.Size(), std::size_t(1));
			GameState::QueueEvents.Update(gameTime);
			Event<FooSubscriber>::HandleChangeList();
			Assert::AreEqual(std::size_t(2), subscriber->Count);
			Assert::AreEqual(GameState::QueueEvents.Size(), std::size_t(1));
			GameState::QueueEvents.Clear();
			Event<FooSubscriber>::UnsubscribeAll();
			Event<FooSubscriber>::HandleChangeList();
		}

		TEST_METHOD(ClearQueue)
		{
			GameTime time;
			EventQueue queue;
			Assert::AreEqual(size_t(0), queue.Size());

			for (int i = 0; i < 4; ++i)
			{
				queue.Enqueue(std::make_shared<Event<Foo>>(Foo{}), time);
			}
			queue.Update(time);
			Assert::AreEqual(size_t(4), queue.Size());

			queue.Clear();
			queue.Update(time);
			Assert::AreEqual(size_t(0), queue.Size());
			Assert::IsTrue(queue.IsEmpty());

			Event<Foo>::UnsubscribeAll();
		}

	private:
		static _CrtMemState _startMemState;
	};
	_CrtMemState EventTests::_startMemState;
}