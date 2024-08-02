#include "Block.h"

Block::Block() {
    _value = -1;
    _locked = false;
}

Block::Block(int val) {
    _value = val;
    if(val > 0) {
        _locked = true;
    } else {
        _locked = false;
    }
}

int Block::getValue() {
    return _value;
}

int Block::setValue(int val) {
    if(!_locked) {
        _value = val;
        return 0;
    } else {
        std::cout << "Cannot set Value (Locked)\r\n";
        return -1;
    }
}

bool    Block::isLocked()
{
    return _locked;
}
void    Block::lock()
{
    _locked = true;
}
void    Block::unlock()
{
    _locked = false;
}

void    Block::setPossibleValues(std::vector<int> vec)
{
    _possibleValues = vec;
}
std::vector<int>    Block::getPossibleValues()
{
    return _possibleValues;
}