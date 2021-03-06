#ifndef __MWOIBN__DYNAMIC_MODELS__QR_DECOMPOSITION_H
#define __MWOIBN__DYNAMIC_MODELS__QR_DECOMPOSITION_H

// #include <rbdl/rbdl.h>
#include "mwoibn/robot_class/robot.h"
#include "mwoibn/dynamic_models/dynamic_models.h"
#include "mwoibn/dynamic_models/basic_model.h"

namespace mwoibn
{

namespace dynamic_models
{

/** @brief This class provides QR decomposition for a robot
**/
class QrDecomposition : public BasicModel
{

public:
QrDecomposition(mwoibn::robot_class::Robot& robot, std::initializer_list<dynamic_models::DYNAMIC_MODEL> update = {}, const std::string& contact_group = "")
  : BasicModel(robot, update), _contact_group(contact_group)
{

        int i =0;
        if(_contact_group.empty()){
           i = _robot.contacts().jacobianRows();
          _contacts_transpose = _robot.contacts().getJacobian().transpose();
        }
        else{

          _robot.srdfContactGroup(_contact_group);
          if(!_robot.contacts().hasGroup(_contact_group)){
             i = _robot.contacts().jacobianRows();
        _contacts_transpose = _robot.contacts().getJacobian().transpose();
          }
          else{
            for(auto& contact: _robot.contacts().group(_contact_group)) i += contact->jacobianSize();
              _contacts_transpose.setZero(i,_robot.getDofs());
          }
        }
        _resize(std::min(_robot.contacts().jacobianCols(), i));
        _qr_ptr.reset(new Eigen::ColPivHouseholderQR<mwoibn::MatrixLimited>(_contacts_transpose));
        _qr_ptr->compute(_contacts_transpose);
}
virtual ~QrDecomposition() {
}

// virtual const mwoibn::VectorN& getGravity()
// {
//         _function_map[DYNAMIC_MODEL::GRAVITY]->count();
//
//         return _qr_gravity;
// }
/** @brief returns all modeled nonlinear effects including gravity in robots
 * dynamics, computed for a non-constrained directions **/
virtual const mwoibn::VectorN& getNonlinearEffects()
{
        _function_map[DYNAMIC_MODEL::NON_LINEAR]->count();

        //std::cout << "NON_LINEAR" << std::endl;
        return _qr_non_linear;
}

/** @brief returns inertia, computed for a non-constrained directions **/
virtual const mwoibn::Matrix& getInertia()
{
        _function_map[DYNAMIC_MODEL::INERTIA]->count();

        return _qr_inertia;
}
//
// const mwoibn::Matrix& getQMatrix(){
//         return _q;
// }

mwoibn::Matrix getRMatrix() const
{
        return _qr_ptr->matrixQR().triangularView<Eigen::Upper>();
}

/** @brief returns rank of a jacobian matrix, reveals number of unconstrained
 * dofs  **/
unsigned int getRank() const {
        return _qr_ptr->rank();
}


void resize()
{
        _resize(_qr_ptr->rank());
}

bool changed(){
        return _changed;
}

virtual void update() {
        _updateDecomposition();
          _manager.update();
}

/** @brief performs transformation of a user defined vector/matrix to a
   *non-constrainted system
 *
 * @warning this method doesn't check if the size of a state send to the
 **matrix is correct, it has to be ensured by a user
 *
 */
template <typename Type> Type decompose(Type state) const
{
        return _independent * state;
}

/** @brief retrunes transformation matrix to get the non-constrained state */
const mwoibn::Matrix& getTransformationMatrix() const {
        return _independent;
}

protected:
//  Eigen::PermutationMatrix<Eigen::Dynamic, Eigen::Dynamic>_permutation;
std::unique_ptr<Eigen::ColPivHouseholderQR<mwoibn::MatrixLimited> > _qr_ptr;
mwoibn::Matrix _qr_inertia;   //< matrix to extract independent rows
int _rank;
bool _changed;
mwoibn::MatrixLimited _q;
mwoibn::Matrix _contacts_transpose, _i, _independent, _q_cut;
mwoibn::VectorN _qr_non_linear;
std::string _contact_group;
void _resize(int rank)
{
        _rank = rank;
        _independent.setZero(_robot.getDofs()-_rank, _robot.getDofs());
        // _qr_gravity.setZero(_robot.getDofs()-_rank);
        _qr_non_linear.setZero(_robot.getDofs()-_rank);
        _qr_inertia.setZero(_robot.getDofs()-rank, _robot.getDofs());
        _q.setZero(_robot.getDofs(), _robot.getDofs());
        _i.setIdentity(_robot.getDofs(), _robot.getDofs());

        _q_cut.setZero(_robot.getDofs()-_rank, _robot.getDofs());

        _changed = true;
//    _qr_non_linear.setZero(_robot.getDofs()-_rank);
//    _qr_inertia.setZero(_robot.getDofs()-rank, _robot.getDofs());
}



// virtual void _updateGravity()
// {
//         BasicModel::_updateGravity();
//         _qr_gravity.noalias() =  _independent * BasicModel::getGravity();
// }
/** @brief returns all modeled nonlinear effects including gravity in robots
 * dynamics, computed for a non-constrained directions **/
virtual void _updateNonlinearEffects()
{
        BasicModel::_updateNonlinearEffects();
        _qr_non_linear.noalias() =  _independent * BasicModel::getNonlinearEffects();
}

/** @brief returns inertia, computed for a non-constrained directions **/
virtual void _updateInertia()
{
        BasicModel::_updateInertia();
        _qr_inertia.noalias() = _independent * BasicModel::getInertia();
}


void _updateDecomposition()
{
        if(_contact_group.empty())
        _contacts_transpose.noalias() = _robot.contacts().getJacobian().transpose();
        else{
          int i =0;
          for(auto& contact: _robot.contacts().group(_contact_group)){
            _contacts_transpose.middleRows(i, contact->jacobianSize()) = contact->getJacobian();
            i += contact->jacobianSize();
          }
        }

        _qr_ptr->compute(_contacts_transpose);


        _q = _qr_ptr->householderQ()*_i;
        _q_cut.noalias() = _q.rightCols(_robot.getDofs() - _rank);

        _independent = _q_cut.transpose();

        // _independent.noalias() = _q.transpose();
}


};
} // namespace package
} // namespace library

#endif // DYANMIC_MODELS_QR_DECOMPOSITION_H
