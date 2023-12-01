#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include "piece.h"

class Observer {
    public:
        virtual void notify(const Piece &p) = 0;
        virtual ~Observer() = default;
};

#endif
