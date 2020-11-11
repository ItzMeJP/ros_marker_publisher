/**\file arrow_pp_marker.h
 * \brief File with arrow_pp_marker class definition
 *
 * @version 0.0.1 - 11/09/2020
 * @author João Pedro Carvalho de Souza
 * @email. joao.pedro@engenharia.ufjf.br || jsouza@fe.up.pt
 * @license: BSD
 */
#include "ros_marker_publisher/arrow_pp_marker.h"

namespace marker_publisher {

    ArrowPPMarker::ArrowPPMarker(){ //TODO: does not work

    }

    ArrowPPMarker::~ArrowPPMarker(){

    }

    void ArrowPPMarker::setupMarkerConfigurationFromParameterServer(ros::NodeHandlePtr& _node_handle, ros::NodeHandlePtr& _private_node_handle,
                                                                 std::string _configuration_namespace, std::string _marker_name){


        _configuration_namespace = _configuration_namespace + "/" + _marker_name + "/";

        marker_.type = visualization_msgs::Marker::ARROW;
        marker_.action = visualization_msgs::Marker::ADD;

        this->setupBaseConfigurationFromParameterServer(_node_handle, _private_node_handle, _configuration_namespace, _marker_name);

        geometry_msgs::Point pb, pe;

        private_node_handle_->param<double>(_configuration_namespace + "begin/position/x", pb.x, 0);
        private_node_handle_->param<double>(_configuration_namespace + "begin/position/y", pb.y, 0);
        private_node_handle_->param<double>(_configuration_namespace + "begin/position/x", pb.z, 0);

        private_node_handle_->param<double>(_configuration_namespace + "end/position/x", pe.x, 0);
        private_node_handle_->param<double>(_configuration_namespace + "end/position/y", pe.y, 0);
        private_node_handle_->param<double>(_configuration_namespace + "end/position/x", pe.z, 1);

        marker_.points.clear();
        marker_.points.push_back(pb);
        marker_.points.push_back(pe);

        double length, width, height;

        private_node_handle_->param<double>(_configuration_namespace + "shaft_diameter", length, 1);
        private_node_handle_->param<double>(_configuration_namespace + "head_diameter", width, 0.1);
        private_node_handle_->param<double>(_configuration_namespace + "head_length", height, 0.1);

        marker_.scale.x = length;
        marker_.scale.y = width;
        marker_.scale.z = height;

        marker_.header.stamp = ros::Time();
        marker_.ns = _marker_name;
        marker_.id = 0;

        this->setupPublisher("/"+_marker_name);

    }

}//namespace end
