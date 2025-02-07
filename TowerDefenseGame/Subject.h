#pragma once
#include <vector>

class IObserver;

class Subject
{
public:
	static void addObserver(IObserver* observer);
	static void removeObserver(IObserver* observer);
	static void removeAllObservers();

	virtual void notifyAllObservers();

private:
	static std::vector<IObserver*> observers;
};