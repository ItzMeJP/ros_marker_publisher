/**\file text_marker.cpp
 * \brief File with text_marker class definition
 *
 * @version 0.0.2 - 11/11/2020
 * @author João Pedro Carvalho de Souza
 * @email. joao.pedro@engenharia.ufjf.br || jsouza@fe.up.pt
 * @license: BSD
 */
#include "ros_marker_publisher/text_marker.h"

namespace marker_publisher {

    TextMarker::TextMarker(){

    }

    TextMarker::~TextMarker(){

    }

    void TextMarker::setupMarkerConfigurationFromParameterServer(ros::NodeHandlePtr& _node_handle, ros::NodeHandlePtr& _private_node_handle,
            std::string _configuration_namespace, std::string _marker_name){


        _configuration_namespace = _configuration_namespace + "/" + _marker_name + "/";

        marker_.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
        marker_.action = visualization_msgs::Marker::ADD;

        this->setupBaseConfigurationFromParameterServer(_node_handle, _private_node_handle, _configuration_namespace, _marker_name);

        std::vector<float> scale_arr;

        private_node_handle_->param<double>(_configuration_namespace + "scale",  marker_.scale.z, 1);
        private_node_handle_->param<std::string>(_configuration_namespace + "text",  marker_.text, "");


        marker_.header.stamp = ros::Time();
        marker_.ns = _marker_name;
        marker_.id = 0;

        this->setupPublisher("/"+_marker_name);

    }

}//namespace end
