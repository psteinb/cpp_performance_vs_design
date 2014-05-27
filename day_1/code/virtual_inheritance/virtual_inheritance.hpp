#ifndef _VIRTUAL_INHERITANCE_H_
#define _VIRTUAL_INHERITANCE_H_
class Direct
{
public:
    int Perform(int &ia) { return --ia; }
};

class AbstrBase
{
public:
    virtual int Perform(int &ia)=0;
};

class Derived: public AbstrBase
{
public:
    virtual int Perform(int &ia) { return --ia; }
};

#endif /* _VIRTUAL_INHERITANCE_H_ */
