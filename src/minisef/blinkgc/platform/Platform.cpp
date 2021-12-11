
#include "config.h"
#include "Platform.h"

#include "web/WebThreadImpl.h"

namespace blink {

Platform* Platform::m_inst = nullptr;

Platform::Platform()
{
    m_thread = nullptr;
    m_mainThread = nullptr;
}

Platform::~Platform()
{
	if (m_thread) {
		delete m_thread;
		m_thread = nullptr;
		m_mainThread = nullptr;
	}
}

Platform* Platform::current()
{
    if (!m_inst)
        m_inst = new Platform();
    return m_inst;
}

void Platform::shutdownCurrent()
{
	if (m_inst)
	{
		delete m_inst;
		m_inst = nullptr;
	}
}

WebThread* Platform::currentThread()
{
    if (!m_thread) {
        m_thread = new WebThreadImpl("MainThread");
        m_mainThread = m_thread;
    }
    return m_thread;
}

WebThread* Platform::mainThread() const
{
    return m_mainThread;
}

}