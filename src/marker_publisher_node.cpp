/**\file marker_publisher_node.cpp
 * \brief run marker publisher node to publish several shapes format in RVIZ
 *
 * @version 0.0.2 - 11/11/2020
 * @author João Pedro Carvalho de Souza
 * @email. joao.pedro@engenharia.ufjf.br || jsouza@fe.up.pt
 * @license: BSD
 */

#include <ros_marker_publisher/common/verbosity_levels.h>
#include <ros_marker_publisher/marker_publisher_server.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "ros_marker_publisher");

    ros::NodeHandlePtr node_handle(new ros::NodeHandle());
    ros::NodeHandlePtr private_node_handle(new ros::NodeHandle("~"));

    std::string ros_verbosity_level;
    private_node_handle->param("ros_verbosity_level", ros_verbosity_level, std::string("DEBUG"));
    ros_marker_publisher::verbosity_levels::setVerbosityLevelROS(ros_verbosity_level);

    marker_publisher::MarkerPublisher server;
    server.setupServerConfigurationFromParameterServer(node_handle, private_node_handle);

    if(!server.start())
        ROS_ERROR_STREAM("Error while executing ros marker publish node.");

    ros::spin();

    //skill.generateLog();

}
