#ifndef RPG_SUBJECT_H
#define RPG_SUBJECT_H

#include "Event.h"
#include "Observer.h"

#include <vector>
#include <iostream>

template<class T>
struct Subject {

  std::vector<Observer<T>*> observers{};

  virtual void addObserver(Observer<T>* observer) {
    observers.push_back(observer);
  }

  virtual void removeObserver(Observer<T>* observer) {
    observers.erase(std::remove(observers.begin(),observers.end(), observer),observers.end());
  }

  void notify(T& subject, Event event) {
    for(auto& observer : observers)
      observer->onNotify(subject, event);
  }

};

#endif