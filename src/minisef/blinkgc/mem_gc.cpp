
#include "mem_gc.h"

#include "web/WebKit.h"
#include "platform/Platform.h"
#include "public/platform/WebThread.h"
#include "web/WebThreadImpl.h"
#include "platform/heap/heap.h"
#include "platform/heap/Visitor.h"
#include "platform/heap/Handle.h"

class Element : public blink::GarbageCollectedFinalized<Element> {
public:
	DECLARE_VIRTUAL_TRACE();

	Element()
	{

	}

	~Element()
	{
		OutputDebugStringA("~Element\n");
	}
};

DEFINE_TRACE(Element)
{
}

class Ungc : public blink::GarbageCollectedFinalized<Ungc> {
public:
	DECLARE_VIRTUAL_TRACE();

	Ungc()
	{

	}

	~Ungc() {
		OutputDebugStringA("~Ungc\n");
	}
};

DEFINE_TRACE(Ungc) {
}

class EventTarget : public blink::GarbageCollectedFinalized<EventTarget> {
public:
	EventTarget()
	{
		m_element = new Element();
	}

	~EventTarget()
	{
		OutputDebugStringA("~EventTarget\n");
	}

	DECLARE_VIRTUAL_TRACE();

	blink::Member<Element> m_element;
};

DEFINE_TRACE(EventTarget)
{
	visitor->trace(m_element);
}

class TestPersistent {
public:
	TestPersistent()
	{

	}
	~TestPersistent()
	{
		//delete m_ungc.get();
	}

	blink::Persistent<Ungc> m_ungc;
};
TestPersistent* testPersistent = NULL;



void gcTest()
{
	blink::Persistent<EventTarget> p = new EventTarget;
	
	if (!testPersistent)
		testPersistent = new TestPersistent();
	testPersistent->m_ungc = new Ungc();

	//GC���������߳��е���
	((blink::WebThreadImpl*)(blink::Platform::current()->currentThread()))->fire();
	blink::Heap::collectAllGarbage();
}

void memgc_test()
{
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);

	blink::initialize();

	gcTest();

	//���ִ�����´�����m_ungc���͹���ע�͵�����
	if (testPersistent)
	{
		delete testPersistent;
		testPersistent = NULL;
	}

	//GC���������߳��е���
	((blink::WebThreadImpl*)(blink::Platform::current()->currentThread()))->fire();
	blink::Heap::collectAllGarbage();

	blink::uninitialize();
}