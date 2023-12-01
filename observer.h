#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Piece;

class Observer {
    public:
        virtual void notify(const Piece &p, int oldX, int oldY) = 0;
        virtual ~Observer() = default;
};

#endif
