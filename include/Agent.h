#ifndef AGENT_H_
#define AGENT_H_

#include <vector>

class Session;

class Agent{
public:
    Agent();
    virtual void act(Session& session)=0;
    virtual Agent* clone() const=0;
};

class ContactTracer: public Agent{
public:
    ContactTracer();
    virtual Agent* clone() const;
    virtual void act(Session& session);
};


class Virus: public Agent{
public:
    Virus(int nodeInd);
    virtual Agent* clone() const;
    virtual void act(Session& session);
protected:
    const int nodeInd;
};

#endif
