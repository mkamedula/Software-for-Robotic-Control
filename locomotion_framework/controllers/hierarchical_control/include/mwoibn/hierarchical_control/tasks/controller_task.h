#ifndef __MWOIBN_HIERARCHICAL_CONTROL_TASKS_CONTROLLER_TASK_H
#define __MWOIBN_HIERARCHICAL_CONTROL_TASKS_CONTROLLER_TASK_H

//#include <rbdl/rbdl.h>
#include "mwoibn/hierarchical_control/hierarchical_control.h"
namespace mwoibn {

namespace hierarchical_control
{
namespace tasks
{

/**
 * \brief Basic implementation of a task in the hierarchical controller
 *
 *
 */
class BasicTask {
public:
/**
 *
 * @param[in] i number of dofs of a task
 *
 */
BasicTask(int i, int dof){
        _init(i, dof);
}

BasicTask(BasicTask&& other) {
        _init(other._jacobian.rows(), other._jacobian.cols());
}

BasicTask(const BasicTask& other) {
        _init(other._jacobian.rows(), other._jacobian.cols());
}

const BasicTask& operator=(const BasicTask& task){
        return task;
}

virtual ~BasicTask(){
}

//! Returnes task Jacobian
const mwoibn::Matrix& getJacobian() const {
        return _jacobian;
}
//! Returnes previous task Jacobian
const mwoibn::Matrix& getPreviousJacobian() const {
        return _last_jacobian;
}

//! Returnes task error
const mwoibn::VectorN& getError() const {
        return _error;
}

const mwoibn::VectorN& getVelocity() const {
        return _velocity;
}

virtual void setVelocity(mwoibn::VectorN& velocity){_velocity = velocity;}

//! Returnes previous task error
const mwoibn::VectorN& getPreviousError() const {
        return _last_error;
}

//! updates task Jacobian based on the parsed argument
void updateJacobian(mwoibn::Matrix jacobian){
        _last_jacobian = _jacobian; _jacobian = jacobian;
}
//! updates task error based on the parsed argument
void updateError(mwoibn::VectorN error){
        _last_error = _error; _error = error;
}
//! generic function to provide the same syntax for Jacobian update of all derived classes
virtual void updateJacobian(){
}
//! generic function to provide the same syntax for error update of all derived classes
virtual void updateError(){
}
//! updates whole task in one call, calls updateError() and updateJacobin() in that order
virtual void update(){
        updateError(); updateJacobian();
}

//! Returnes size of a defined task
int getTaskSize() const {
        return _jacobian.rows();
}
//! Returnes number of task dofs
int getTaskDofs() const {
        return _jacobian.cols();
}

// virtual double det(){
//         return _jacobian.determinant();
// }
//! Allows to define the human readable name for the task
std::string name;

protected:
BasicTask(){
}
//! current jacobian task
mwoibn::Matrix _jacobian;
//! current task error
mwoibn::VectorN _error, _velocity;
//! previous jacobian task
mwoibn::Matrix _last_jacobian;
//! previous task error
mwoibn::VectorN _last_error;

//! internal function, initializes all function members to ensure proper matrices dimensions
bool _init(int i, int dof){
        _error = mwoibn::VectorN::Zero(i);
        _jacobian = mwoibn::Matrix::Zero(i,dof);
        _last_error = mwoibn::VectorN::Zero(i);
        _last_jacobian = mwoibn::Matrix::Zero(i,dof);
        _velocity = mwoibn::VectorN::Zero(i);
        return true;
}
};
}
}     // namespace package
}     // namespace library
    #endif
