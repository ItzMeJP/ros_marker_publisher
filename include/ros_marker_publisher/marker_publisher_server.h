/**\file marker_publisher_server.h
 * \brief File with marker_publisher_server class declaration
 *
 * @version 0.0.2 - 11/11/2020
 * @author João Pedro Carvalho de Souza
 * @email. joao.pedro@engenharia.ufjf.br || jsouza@fe.up.pt
 * @license: BSD
 */

#ifndef ROS_MARKER_PUBLISHER_MARKER_PUBLISHER_SERVER_H
#define ROS_MARKER_PUBLISHER_MARKER_PUBLISHER_SERVER_H

#pragma once

#include <ros/ros.h>

#include <ros_marker_publisher/marker_base.h>
#include <ros_marker_publisher/cube_marker.h>
#include <ros_marker_publisher/arrow_marker.h>
#include <ros_marker_publisher/arrow_pp_marker.h>
#include <ros_marker_publisher/sphere_marker.h>
#include <ros_marker_publisher/cylinder_marker.h>
#include <ros_marker_publisher/text_marker.h>
#include <ros_marker_publisher/mesh_marker.h>

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <cstdlib>




namespace marker_publisher {

    class MarkerPublisher {
    public:

        MarkerPublisher ();
        ~MarkerPublisher (void);

        bool start (); //start the server
        void cleanArrays();

        bool setupServerConfigurationFromParameterServer (ros::NodeHandlePtr &_node_handle,
                                                         ros::NodeHandlePtr &_private_node_handle);
    protected:

        ros::NodeHandlePtr node_handle_, private_node_handle_;

        bool loadMarkersPipeline ();

        bool runPublishers();

//If you do need it be a non-static member function in the future, bind it with boost::bind or std::bind (for C++0x compiler):
//std::sort(hand.begin(),hand.end(),bind(&Hand::CardCompare, this, _1, _2));

        static bool cmp(std::pair<int, std::string>& a, std::pair<int, std::string>& b);

        void splitStrings(std::string str, char dl, std::vector<std::string>& substr_list);

        MarkerBase::ArrPtr markerPipelineArrPtr_ = std::make_shared<MarkerBase::Arr>();

    };// Class end

}//namespace end

#endif //ROS_MARKER_PUBLISHER_MARKER_PUBLISHER_SERVER_H
