#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
#include "observer.h"

// Commenting out detach method and destructor. Add back if detaching is needed

class Subject {
  std::vector<Observer*> observers;

 public:
  Subject();
  void attach(Observer *o);
  // void detach(Observer *o);
  void notifyObservers() const;
  // virtual ~Subject()=0;
};

#endif
