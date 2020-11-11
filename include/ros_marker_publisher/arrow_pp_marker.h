/**\file arrow_pp_marker.h
 * \brief File with arrow_pp_marker class declaration
 *
 * @version 0.0.2 - 11/11/2020
 * @author João Pedro Carvalho de Souza
 * @email. joao.pedro@engenharia.ufjf.br || jsouza@fe.up.pt
 * @license: BSD
 */

#ifndef ROS_MARKER_PUBLISHER_ARROW_PP_MARKER_H
#define ROS_MARKER_PUBLISHER_ARROW_PP_MARKER_H

#pragma once

#include "ros_marker_publisher/marker_base.h"

namespace marker_publisher {

    class ArrowPPMarker : public MarkerBase {
    public:
        ArrowPPMarker();
        ~ArrowPPMarker();

        void setupMarkerConfigurationFromParameterServer(ros::NodeHandlePtr& _node_handle, ros::NodeHandlePtr& _private_node_handle,
                                                         std::string _configuration_namespace, std::string _marker_name);
    private:


    };

}//namespace end

#endif //ROS_MARKER_PUBLISHER_ARROW_PP_MARKER_H
