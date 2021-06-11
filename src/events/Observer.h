#ifndef RPG_OBSERVER_H
#define RPG_OBSERVER_H

template<class T>
struct Observer {

  virtual void onNotify(T& f, Event event) = 0;

};

#endif
