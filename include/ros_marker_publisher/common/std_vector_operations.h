#pragma once

/**\file std_vector_operations.h
 * \brief Some operations with std::vector<> without convertions
 *
 * @version 1.0
 * @author João Pedro Carvalho de Souza
 */

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <macros>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </macros>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  <includes>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// std includes
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>


namespace ros_marker_publisher {
    namespace std_vector_operations {

        bool normalizeVector(std::vector<double> &_arr, double min, double max);

        bool normalizeVector(std::vector<double> &_arr);

        void scalarMultiplicationToVector(std::vector<double> &_arr, double multiplier);

        bool sumEachElementOfVector(std::vector<double> _arr1, std::vector<double> _arr2, std::vector<double> &_result);

        bool sumEachElementOfVector(std::vector<bool> _arr1, std::vector<bool> _arr2, std::vector<bool> &_result);

        void vectorDivisionToScalar(std::vector<double> &_arr, double multiplier);

        bool addScalarToVector (std::vector<double> &_arr, double scalar);

        bool scalarDivisionToVector(std::vector<double> &_arr, double scalar);

        bool invertEachElement(std::vector<double> &_arr);


    } /* namespace std_vector_operations */
} /* namespace grasp_estimation_skill */

