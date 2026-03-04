#include "Task.h"

Task::Task(const std::string& name, const std::string& desc, unsigned int id, unsigned int priority)
{
	taskName = name;
	taskDesc = desc;
	taskID = id;
	taskPriority = priority;
}

const std::string& Task::getName() const
{
	return taskName;
}

void Task::setName(const std::string& name)
{
	taskName = name;
}

const std::string& Task::getDesc() const
{
	return taskDesc;
}

void Task::setDesc(const std::string& desc)
{
	taskDesc = desc;
}

unsigned int Task::getPriority() const
{
	return taskPriority;
}

void Task::setPriority(unsigned int priority)
{
	taskPriority = priority;
}
