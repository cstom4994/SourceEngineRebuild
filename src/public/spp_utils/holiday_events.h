#ifndef IHOLIDAY_EVENTS_H
#define IHOLIDAY_EVENTS_H
#pragma once

#include <time.h>

#define HOLIDAYEVENTS_INTERFACE_VERSION "IHolidayEvents002"

class IHoliday
{
public:
	virtual bool IsActive(const time_t& timeCurrent) = 0;
	virtual const char* GetHolidayName() const = 0;

	virtual time_t GetStartTime() = 0;
	virtual time_t GetEndTime() = 0;
};

class IHolidayEvents
{
public:
	virtual bool IsEventActive(int iEvent) = 0;
	virtual int NumEvents() = 0;
	//Lookup an event by name
	// Returns -1 if no event
	virtual int LookupEvent(const char* pchEventName) = 0;
	virtual IHoliday* GetEvent(int iEvent) = 0;
	virtual int GetActiveEvents(IHoliday** ppEvents, int iMaxEvents) = 0;
};
#endif // !HOLIDAY_EVENTS_H
