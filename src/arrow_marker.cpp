/**\file arrow_marker.h
 * \brief File with arrow_marker class definition
 *
 * @version 0.0.2 - 11/11/2020
 * @author João Pedro Carvalho de Souza
 * @email. joao.pedro@engenharia.ufjf.br || jsouza@fe.up.pt
 * @license: BSD
 */
#include "ros_marker_publisher/arrow_marker.h"

namespace marker_publisher {

    ArrowMarker::ArrowMarker(){

    }

    ArrowMarker::~ArrowMarker(){

    }

    void ArrowMarker::setupMarkerConfigurationFromParameterServer(ros::NodeHandlePtr& _node_handle, ros::NodeHandlePtr& _private_node_handle,
                                                                 std::string _configuration_namespace, std::string _marker_name){


        _configuration_namespace = _configuration_namespace + "/" + _marker_name + "/";

        marker_.type = visualization_msgs::Marker::ARROW;
        marker_.action = visualization_msgs::Marker::ADD;

        this->setupBaseConfigurationFromParameterServer(_node_handle, _private_node_handle, _configuration_namespace, _marker_name);

        double length, width, height;

        private_node_handle_->param<double>(_configuration_namespace + "arrow_length", length, 1);
        private_node_handle_->param<double>(_configuration_namespace + "arrow_width", width, 0.1);
        private_node_handle_->param<double>(_configuration_namespace + "arrow_height", height, 0.1);

        marker_.scale.x = length;
        marker_.scale.y = width;
        marker_.scale.z = height;

        marker_.header.stamp = ros::Time();
        marker_.ns = _marker_name;
        marker_.id = 0;

        this->setupPublisher("/"+_marker_name);

    }

}//namespace end
