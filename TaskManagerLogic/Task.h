#pragma once

#include <string>


class Task
{
private:
	std::string taskName;
	std::string taskDesc;
	unsigned int taskID;
	unsigned int taskPriority;
public:
	Task() = default;
	~Task() = default;
	Task(const std::string& name, const std::string& desc, unsigned int id, unsigned int priority);

	const std::string& getName() const;
	void setName(const std::string& name);

	const std::string& getDesc() const;
	void setDesc(const std::string& desc);

	unsigned int getPriority() const;
	void setPriority(unsigned int priority);


};
