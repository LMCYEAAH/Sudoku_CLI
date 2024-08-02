#ifndef BLOCK_H
#define BLOCK_H
#include <iostream>
#include <vector>

class Block {
    public:
        Block();
        Block(int val);
        int                 getValue();
        int                 setValue(int val);
        bool                isLocked();
        void                lock();
        void                unlock();
        void                setPossibleValues(std::vector<int> vec);
        std::vector<int>    getPossibleValues();
    private:
        int _value;
        bool _locked;
        std::vector<int> _possibleValues;
};

#endif