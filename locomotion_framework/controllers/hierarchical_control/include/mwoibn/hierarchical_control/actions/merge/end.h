#ifndef __MWOIBN_HIERARCHICAL_CONTROL_ACTIONS_MERGE__END_H
#define __MWOIBN_HIERARCHICAL_CONTROL_ACTIONS_MERGE__END_H

#include "mwoibn/hierarchical_control/maps/task_map.h"
#include "mwoibn/hierarchical_control/actions/merge/local.h"
#include "mwoibn/hierarchical_control/actions/dynamic_replace.h"
#include "mwoibn/hierarchical_control/actions/merge/front.h"
// #include "mwoibn/hierarchical_control/actions/merge.h"

namespace mwoibn
{
namespace hierarchical_control
{
namespace actions {

namespace merge {

class End : public Local  {
//
public:
End(mwoibn::Matrix& P, mwoibn::VectorN& command, MergeManager& memory, maps::TaskMap& map, actions::Merge& merge,  double dt, double mu);
End(const End& other);

virtual ~End();
const End& operator=(const End& task){
        return task;
}
virtual Local& pull(){
        return *this;
}
virtual void push(Local& parent);

virtual void release();
// // this should initialized with the zero set-up or keep current?
virtual void assign(actions::Task& t_new, actions::Task* t_old, Local* parent);
virtual void assign(actions::Task& t_new, actions::Task&);

//
const double getGain();
virtual void run();
virtual void reset();
virtual void progress();
virtual void updateGain();
virtual void setProgress(double p);
virtual actions::Task& next();
actions::Primary& baseAction();
actions::Task& action();
virtual bool isParent(actions::Task& task);
virtual Local& swapFromFront(Local& lower);
virtual Local& swapFromReplace(Local& lower);
virtual void setParent(Local& parent){
}

protected:

double _t, _dt, _mu, _p;
mwoibn::VectorN _gain;         // it is a scalar anyway for this code
actions::DynamicReplace _this;
memory::Manager _this_memory;

virtual void _setLimit();
virtual void _end();

virtual void _finish(Local& local);




};


}
}
} // namespace package
} // namespace library
#endif
