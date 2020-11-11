/**\file math_common.cpp
 * \brief Utils math operations with std::vector<> without convertions
 *
 * @version 1.0
 * @author João Pedro Carvalho de Souza
 */

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <includes>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include <ros_marker_publisher/common/std_vector_operations.h>

#include "ros_marker_publisher/common/std_vector_operations.h"

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </includes>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

namespace marker_publisher {
    namespace std_vector_operations {

        // Description: get the the normalized vector. The normalization is between the specified minimum and maximum values and the score range is [0,1].
        bool normalizeVector(std::vector<double> &_arr, double min, double max){
            if(max == min)
                return false;

            std::vector<double> norm_arr;

            for (size_t i = 0; i <_arr.size(); ++i) {
                norm_arr.push_back((_arr[i] - min) / (max - min));
            }

            _arr.clear();
            _arr.swap(norm_arr);

            return true;

        }

                // Description: get the the normalized vector. The normalization is between minimum and maximum value in the array and the score range is [0,1].
        bool normalizeVector(std::vector<double> &_arr){

            double min = (double)*std::min_element(_arr.begin(), _arr.end());
            double max = (double)*std::max_element(_arr.begin(), _arr.end());

            return normalizeVector(_arr, min, max);
        }

        // Description: multiply each element of a vector by a scalar
        void scalarMultiplicationToVector(std::vector<double> &_arr, double multiplier){
            std::transform(_arr.begin(), _arr.end(),
                           _arr.begin(), std::bind1st(std::multiplies<double>(), multiplier));
        }

        // Description: divides each element of a vector by a scalar
        void vectorDivisionToScalar(std::vector<double> &_arr, double multiplier){
            std::transform(_arr.begin(), _arr.end(),
                           _arr.begin(), std::bind1st(std::divides<double>(), multiplier));
        }

        // Description: sums two vectors point a point
        bool sumEachElementOfVector(std::vector<double> _arr1, std::vector<double> _arr2, std::vector<double> &_result){

            if(_arr1.size() != _arr2.size())
                return false;

            _result = _arr1;
            std::transform (_result.begin(), _result.end(), _arr2.begin(), _result.begin(), std::plus<double>());
            return true;

        }

        // Description: sums two vectors point a point
        bool sumEachElementOfVector(std::vector<bool> _arr1, std::vector<bool> _arr2, std::vector<bool> &_result){

            if(_arr1.size() != _arr2.size())
                return false;

            _result = _arr1;
            std::transform (_result.begin(), _result.end(), _arr2.begin(), _result.begin(), std::plus<bool>());
            return true;

        }

        // Description: add a scalar to each element of a vector
        bool addScalarToVector(std::vector<double> &_arr, double scalar){
            std::transform(_arr.begin(), _arr.end(), _arr.begin(), bind2nd(std::plus<double>(), scalar));
            return true;
        }

        bool scalarDivisionToVector(std::vector<double> &_arr, double scalar) {
            transform (_arr.begin(), _arr.end(),_arr.begin(), bind2nd(std::divides<double>(), scalar));
            return true;
        }

        bool invertEachElement (std::vector<double> &_arr) {

            for (size_t i = 0; i < _arr.size(); ++i) {
                _arr.at(i) == 0? _arr.at(i) = NAN : _arr.at(i) = 1/_arr.at(i);
            }
            return true;
        }


    } /* namespace std_vector_operations */
} /* namespace grasp_estimation_skill */
