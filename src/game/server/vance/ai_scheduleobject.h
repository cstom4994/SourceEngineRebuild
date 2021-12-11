#ifndef SCHEDULEOBJECT_H
#define SCHEDULEOBJECT_H

class CScheduleObject
{
public:
	int m_iSchedType;
	bool m_bCondition;
	bool m_bSquadslot = true;
	float m_fSchedPriority;
};

#endif // SCHEDULEOBJECT_H