#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>

class Observer;

class Subject {
    std::vector<Observer*> observers;
    public:
        void attach(Observer *ob);
        void detach(Observer *ob);
        void notifyObservers();
        virtual char pieceAt(int row, int col) const = 0;
        virtual ~Subject() = default;
};

#endif
