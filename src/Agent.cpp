//
// Created by spl211 on 09/11/2020.
//
#include "../include/Agent.h"


// Constructor
Agent::Agent() {}

//------------ContactTracer----------------
ContactTracer::ContactTracer() {}
Agent* ContactTracer::clone() const {return new ContactTracer(*this);}
void ContactTracer::act(Session &session) {}

//------------Virus-------------------
Virus::Virus(int nodeInd):nodeInd(nodeInd) {}
Agent* Virus::clone() const {return new Virus(*this);}
void Virus::act(Session &session) {}