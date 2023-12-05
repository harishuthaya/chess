#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Piece;

class Observer {
    public:
        // virtual method called by subjects to notify observers
        virtual void notify(const Piece &p, int oldX, int oldY) = 0;
        virtual ~Observer() = default;
};

#endif
