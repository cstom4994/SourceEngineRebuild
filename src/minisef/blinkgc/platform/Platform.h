

#ifndef Platform_h
#define Platform_h

#include <wtypes.h>

namespace blink {

class WebThread;

class Platform {
public:
    static Platform* current();
	static void shutdownCurrent();

    WebThread* currentThread();
    WebThread* mainThread() const;

private:
    Platform();
	~Platform();

    static Platform* m_inst;
    WebThread* m_mainThread;
    WebThread* m_thread;
};

}

#endif Platform_h