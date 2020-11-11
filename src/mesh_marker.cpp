/**\file mesh_marker.cpp
 * \brief File with mesh_marker class definition
 *
 * @version 0.0.2 - 11/11/2020
 * @author João Pedro Carvalho de Souza
 * @email. joao.pedro@engenharia.ufjf.br || jsouza@fe.up.pt
 * @license: BSD
 */
#include "ros_marker_publisher/mesh_marker.h"

namespace marker_publisher {

    MeshMarker::MeshMarker(){

    }

    MeshMarker::~MeshMarker(){

    }

    void MeshMarker::setupMarkerConfigurationFromParameterServer(ros::NodeHandlePtr& _node_handle, ros::NodeHandlePtr& _private_node_handle,
            std::string _configuration_namespace, std::string _marker_name){


        std::string path;
        _configuration_namespace = _configuration_namespace + "/" + _marker_name + "/";

        marker_.type = visualization_msgs::Marker::MESH_RESOURCE;
        marker_.action = visualization_msgs::Marker::ADD;

        this->setupBaseConfigurationFromParameterServer(_node_handle, _private_node_handle, _configuration_namespace, _marker_name);

        private_node_handle_->param<std::string>(_configuration_namespace + "source", path , "");

        marker_.mesh_resource = path;
        ROS_INFO_STREAM("Locating mesh file at: " << marker_.mesh_resource);
        marker_.mesh_use_embedded_materials = true;

        std::vector<float> scale_arr;

        if (!private_node_handle_->param(_configuration_namespace + "scale", scale_arr, std::vector<float>())) {
            scale_arr.push_back(1.0);
            scale_arr.push_back(1.0);
            scale_arr.push_back(1.0);
            ROS_WARN_STREAM("Error reading scales for mesh marker. Using unit values");
        }

        marker_.scale.x = scale_arr.at(0);
        marker_.scale.y = scale_arr.at(1);
        marker_.scale.z = scale_arr.at(2);

        marker_.header.stamp = ros::Time();
        marker_.ns = _marker_name;
        marker_.id = 0;

        this->setupPublisher("/"+_marker_name);

    }

}//namespace end
