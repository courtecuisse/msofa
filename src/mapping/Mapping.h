#ifndef MAPPING_H
#define MAPPING_H

#include <state/State.h>
#include <core/BaseObject.h>
#include <dataStructures.h>
#include <vector>
#include <core/Visitor.h>

class Mapping : public BaseObject {
public:

    Data<std::string> d_input;
    Data<std::string> d_output;

    Mapping()
    : d_input("input","..",this)
    , d_output("output",".",this) {
        m_stateFrom = NULL;
        m_stateTo = NULL;
    }


    void init() {
        BaseObject * obj1 = this->getContext()->get(d_input.getValue());
        BaseObject * obj2 = this->getContext()->get(d_output.getValue());

        if (obj1 == NULL) std::cerr << "Error Mapping " << this->getName() << " cannot find the mstate source" << std::endl;
        if (obj2 == NULL) std::cerr << "Error Mapping " << this->getName() << " cannot find the mstate dest" << std::endl;

        Context * c1 = obj1->getContext();
        Context * c2 = obj2->getContext();

        if (c1 == NULL) std::cerr << "Error Mapping " << this->getName() << " cannot find the mstate source" << std::endl;
        if (c2 == NULL) std::cerr << "Error Mapping " << this->getName() << " cannot find the mstate source" << std::endl;

        m_stateFrom = c1->getMstate();
        m_stateTo = c2->getMstate();

        if (m_stateFrom == NULL) std::cerr << "Error Mapping " << this->getName() << " cannot find the mstate source" << std::endl;
        if (m_stateTo == NULL) std::cerr << "Error Mapping " << this->getName() << " cannot find the mstate destination" << std::endl;

        m_stateTo->setMapped(true);
    }

    virtual void apply() = 0;

    virtual void applyJT(TVecId f) = 0;

protected:
    State * m_stateFrom;
    State * m_stateTo;

};

class MappingApplyJTVisitor : public Visitor {
public:

    MappingApplyJTVisitor(TVecId v) : Visitor(true) {
        m_v = v;
    }

    bool processObject(BaseObject * o) {
        if (dynamic_cast<Mapping *>(o)) {
            ((Mapping *) o)->applyJT(m_v);
        }

        return true;
    }

    TVecId m_v;
};


#endif
