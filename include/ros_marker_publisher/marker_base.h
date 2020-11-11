/**\file marker_base.h
 * \brief File with marker_base class declaration
 *
 * @version 0.0.1 - 11/09/2020
 * @author João Pedro Carvalho de Souza
 * @email. joao.pedro@engenharia.ufjf.br || jsouza@fe.up.pt
 * @license: BSD
 */

#ifndef ROS_MARKER_PUBLISHER_MARKER_BASE_H
#define ROS_MARKER_PUBLISHER_MARKER_BASE_H

#pragma once

#include <ros/ros.h>

#include "visualization_msgs/Marker.h"
#include "visualization_msgs/MarkerArray.h"
#include <geometry_msgs/TransformStamped.h>
#include <tf2_ros/static_transform_broadcaster.h>

namespace marker_publisher {

    class MarkerBase {
    public:
        MarkerBase();
        ~MarkerBase();

        typedef std::shared_ptr<MarkerBase> Ptr;
        typedef std::vector<MarkerBase::Ptr> Arr;
        typedef std::shared_ptr<MarkerBase::Arr> ArrPtr;

        virtual void setupMarkerConfigurationFromParameterServer(ros::NodeHandlePtr& _node_handle, ros::NodeHandlePtr& _private_node_handle,
                                                                 std::string _configuration_namespace, std:: string _marker_name) = 0;
        void setupBaseConfigurationFromParameterServer(ros::NodeHandlePtr& _node_handle, ros::NodeHandlePtr& _private_node_handle, std::string _configuration_namespace, std::string _marker_name);

        void setupPublisher(std::string _name);
        virtual bool run();

    protected:

        ros::NodeHandlePtr node_handle_, private_node_handle_;
        ros::Publisher pub_;
        visualization_msgs::Marker marker_;

        tf2_ros::StaticTransformBroadcaster tf_static_broadcaster_;
        geometry_msgs::TransformStamped ref_frame_;
        static std::vector<geometry_msgs::TransformStamped> ref_frame_arr_;

    };

}//namespace end

#endif //ROS_MARKER_PUBLISHER_MARKER_BASE_H
