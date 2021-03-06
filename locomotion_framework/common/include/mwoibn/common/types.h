#ifndef COMMON_COMMON_H
#define COMMON_COMMON_H

#define QUATERNION_EIGEN // this should be a ccmake option
#define DECOMPOSITIONS_EIGEN
//#define QUATERNION_RBDL
#define EIGEN

#ifdef LOGGER
#include "mwoibn/simple_log/log.h"
#endif

#include <rbdl/rbdl.h>

#include "mwoibn/std_utils/std_utils.h"
#include "mwoibn/rbdl_utils/rbdl_utils.h"
#ifdef QUATERNION_RBDL
  #include "mwoibn/rbdl_utils/rbdl_utils.h"
  #include "mwoibn/rbdl_utils/quaternion.h"
#endif
#ifdef QUATERNION_EIGEN
  #include "mwoibn/eigen_utils/quaternion.h"
#endif
#ifdef DECOMPOSITIONS_EIGEN
  #include "mwoibn/eigen_utils/eigen_utils.h"
#endif
#include <float.h>
#include <math.h>
#include <memory>
#include <utility>

#define RT_SIZE 50
#define FS_SIZE 8

namespace mwoibn
{

typedef RigidBodyDynamics::Math::VectorNd VectorN;
typedef RigidBodyDynamics::Math::Vector3d Vector3;
typedef Eigen::Matrix<double, 1, 3> Vector3T;
typedef Eigen::Matrix<double, 1, Eigen::Dynamic> VectorNT;

typedef double Scalar;
typedef Vector3 Position;
typedef Vector3 Axis;

typedef RigidBodyDynamics::Math::MatrixNd Matrix;
typedef Eigen::Matrix<Scalar, 6, 6> Matrix6;
typedef Eigen::Matrix<Scalar, 3, 6> MatrixJ;
typedef Eigen::Matrix<Scalar, 3, 3> Matrix3;
typedef Eigen::VectorXi VectorInt;
typedef Eigen::Matrix<bool,Eigen::Dynamic,1> VectorBool;
typedef Eigen::Matrix<Scalar, RT_SIZE, 1> VectorRT;
typedef Eigen::Matrix<Scalar, FS_SIZE, 1> VectorFS;
typedef Eigen::Matrix<Scalar, 7, 1> Vector7;
typedef Eigen::Matrix<Scalar, 6, 1> Vector6;

typedef Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, 0, RT_SIZE, RT_SIZE> MatrixLimited; //???
typedef Eigen::Matrix<Scalar, Eigen::Dynamic, 1, 0, RT_SIZE, 1> VectorLimited;

typedef eigen_utils::PseudoInverse2<mwoibn::Matrix, mwoibn::Scalar> PseudoInverse;
typedef eigen_utils::Inverse<mwoibn::Matrix, mwoibn::Scalar> Inverse;
typedef eigen_utils::PseudoInverse2<mwoibn::MatrixLimited, mwoibn::Scalar> PseudoInverseLimited;
typedef mwoibn::eigen_utils::AgumentedNullSpaceProjection<mwoibn::Matrix, mwoibn::Scalar> Projection;

typedef std::string Interface;

const double PI= M_PI;
const double HALF_PI= M_PI_2;
const double TWO_PI= 2*PI;

const double MAX_DOUBLE= DBL_MAX;
const double EPS =  std::numeric_limits<double>::epsilon();

const int NON_EXISTING = INT_MAX;
const unsigned int RBDL_NON_EXISTING = UINT_MAX;
const int IS_VALID = INT_MAX;
const int INVALID = 0;

const int rt_size = RT_SIZE;
}
#endif
