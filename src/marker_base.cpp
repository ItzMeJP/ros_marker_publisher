/**\file marker_base.h
 * \brief File with marker_base class definition
 *
 * @version 0.0.2 - 11/11/2020
 * @author João Pedro Carvalho de Souza
 * @email. joao.pedro@engenharia.ufjf.br || jsouza@fe.up.pt
 * @license: BSD
 */

#include "ros_marker_publisher/marker_base.h"


namespace marker_publisher {

    std::vector<geometry_msgs::TransformStamped> MarkerBase::ref_frame_arr_;

    MarkerBase::MarkerBase () {

    }

    MarkerBase::~MarkerBase () {

    }

    //TODO: option without TF
    void MarkerBase::setupBaseConfigurationFromParameterServer(ros::NodeHandlePtr& _node_handle, ros::NodeHandlePtr& _private_node_handle, std::string _configuration_namespace , std::string _marker_name){

        node_handle_ = _node_handle;
        private_node_handle_ = _private_node_handle;

        std::vector<float> rgb_arr;

        private_node_handle_->param<std::string>(_configuration_namespace + "parent_frame_id", ref_frame_.header.frame_id, "world");
        private_node_handle_->param<double>(_configuration_namespace + "pose/position/x", ref_frame_.transform.translation.x, 0);
        private_node_handle_->param<double>(_configuration_namespace + "pose/position/y", ref_frame_.transform.translation.y, 0);
        private_node_handle_->param<double>(_configuration_namespace + "pose/position/z", ref_frame_.transform.translation.z, 0);
        private_node_handle_->param<double>(_configuration_namespace + "pose/orientation/x", ref_frame_.transform.rotation.x, 0);
        private_node_handle_->param<double>(_configuration_namespace + "pose/orientation/y", ref_frame_.transform.rotation.y, 0);
        private_node_handle_->param<double>(_configuration_namespace + "pose/orientation/z", ref_frame_.transform.rotation.z, 0);
        private_node_handle_->param<double>(_configuration_namespace + "pose/orientation/w", ref_frame_.transform.rotation.w, 1);
        private_node_handle_->param<float>(_configuration_namespace + "opacity", marker_.color.a, 1);

        ref_frame_.child_frame_id = "marker_" + _marker_name;
        ref_frame_.header.stamp = ros::Time::now();

        ref_frame_arr_.push_back(ref_frame_);

        marker_.header.frame_id = "marker_" + _marker_name;
        marker_.header.stamp = ref_frame_.header.stamp;
        marker_.pose.position.x = 0;
        marker_.pose.position.y = 0;
        marker_.pose.position.z = 0;
        marker_.pose.orientation.x = 0;
        marker_.pose.orientation.y = 0;
        marker_.pose.orientation.z = 0;
        marker_.pose.orientation.w = 1;

        if (!private_node_handle_->param(_configuration_namespace + "rgb", rgb_arr, std::vector<float>())) {
            rgb_arr.push_back(1.0);
            rgb_arr.push_back(1.0);
            rgb_arr.push_back(1.0);
            ROS_WARN_STREAM("Error reading RGB for cube marker. Using unit values");
        }

        marker_.color.r = rgb_arr.at(0);
        marker_.color.g = rgb_arr.at(1);
        marker_.color.b = rgb_arr.at(2);

    }


    void MarkerBase::setupPublisher(std::string _name){
        std::string topic = _name;
        pub_ = private_node_handle_->advertise<visualization_msgs::Marker>(topic , 100, true );
    }

    bool MarkerBase::run() {

        tf_static_broadcaster_.sendTransform(ref_frame_arr_);
        pub_.publish(marker_);
        return true;
    }



}//namespace end