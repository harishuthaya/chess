#include "subject.h"

// Commenting out detach method and destructor. Add back if detaching is needed

Subject::Subject() {}
// Subject::~Subject() {}

void Subject::attach(Observer *o) {
  observers.emplace_back(o);
}

// void Subject::detach(Observer *o) {
//   for (auto it = observers.begin(); it != observers.end(); ++it) {
//     if (*it == o) {
//       observers.erase(it);
//       break;
//     }
//   }
// }

void Subject::notifyObservers() const {
  for (auto ob : observers) ob->notify();
}


