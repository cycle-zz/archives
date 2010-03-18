#include "SpMaths.h"

#include <cfloat>

//----------------------------------------------------------------------------
// explicit instantiation
//----------------------------------------------------------------------------
namespace Spark
{

template class SpMaths<float>;
template<> const float SpMaths<float>::EPSILON = FLT_EPSILON;
template<> const float SpMaths<float>::MAXIMUM = FLT_MAX;
template<> const float SpMaths<float>::PI = (float)(4.0*atan(1.0));
template<> const float SpMaths<float>::TWO_PI = 2.0f*SpMaths<float>::PI;
template<> const float SpMaths<float>::HALF_PI = 0.5f*SpMaths<float>::PI;
template<> const float SpMaths<float>::INV_PI = 1.0f/SpMaths<float>::PI;
template<> const float SpMaths<float>::INV_TWO_PI = 1.0f/SpMaths<float>::TWO_PI;
template<> const float SpMaths<float>::DEG_TO_RAD = SpMaths<float>::PI/180.0f;
template<> const float SpMaths<float>::RAD_TO_DEG = 180.0f/SpMaths<float>::PI;

template class SpMaths<double>;
template<> const double SpMaths<double>::EPSILON = DBL_EPSILON;
template<> const double SpMaths<double>::MAXIMUM = DBL_MAX;
template<> const double SpMaths<double>::PI = 4.0*atan(1.0);
template<> const double SpMaths<double>::TWO_PI = 2.0*SpMaths<double>::PI;
template<> const double SpMaths<double>::HALF_PI = 0.5*SpMaths<double>::PI;
template<> const double SpMaths<double>::INV_PI = 1.0/SpMaths<double>::PI;
template<> const double SpMaths<double>::INV_TWO_PI = 1.0/SpMaths<double>::TWO_PI;
template<> const double SpMaths<double>::DEG_TO_RAD = SpMaths<double>::PI/180.0;
template<> const double SpMaths<double>::RAD_TO_DEG = 180.0/SpMaths<double>::PI;

}
//----------------------------------------------------------------------------


