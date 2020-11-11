/**\file marker_base.h
 * \brief File with marker_publisher_server class definition
 *
 * @version 0.0.1 - 11/09/2020
 * @author João Pedro Carvalho de Souza
 * @email. joao.pedro@engenharia.ufjf.br || jsouza@fe.up.pt
 * @license: BSD
 */
#include "ros_marker_publisher/marker_publisher_server.h"

namespace marker_publisher{

    MarkerPublisher::MarkerPublisher(){

    }

    MarkerPublisher::~MarkerPublisher(){

    }

    /// <summary>
    /// Start the server
    /// </summary>
    bool MarkerPublisher::start () {

        cleanArrays();

        if(!loadMarkersPipeline() ||
           !runPublishers())
            return false;

        return true;
    }

    /// <summary>
    /// Free and clean arrays
    /// </summary>
    void MarkerPublisher::cleanArrays() {

        markerPipelineArrPtr_->clear();
    }

    bool MarkerPublisher::setupServerConfigurationFromParameterServer (ros::NodeHandlePtr &_node_handle, ros::NodeHandlePtr &_private_node_handle){
        node_handle_ = _node_handle;
        private_node_handle_ = _private_node_handle;
        return true;
    }

    void MarkerPublisher::splitStrings(std::string str, char dl, std::vector<std::string>& substr_list)
    {
        std::string word = "";

        // to count the number of split strings
        int num = 0;

        // adding delimiter character at the end
        // of 'str'
        str = str + dl;

        // length of 'str'
        int l = str.size();

        // traversing 'str' from left to right
        for (int i = 0; i < l; i++) {

            // if str[i] is not equal to the delimiter
            // character then accumulate it to 'word'
            if (str[i] != dl)
                word = word + str[i];

            else {

                // if 'word' is not an empty string,
                // then add this 'word' to the array
                // 'substr_list[]'
                if ((int)word.size() != 0)
                    substr_list.push_back(word);

                // reset 'word'
                word = "";
            }
        }

    }

    // Comparator function to sort pairs (used in loadMarkersPipeline method)
    // according to first value
    bool MarkerPublisher::cmp(std::pair<int, std::string>& a, std::pair<int, std::string>& b)
    {
        return a.first < b.first;
    }

    /// <summary>
    /// Load the marker definition pipeline from parameter server. Supported marker's tag names (X is an alpha_numeric that define the order):
    /// X_arrow: euclidean distance evaluator
    /// X_cube: depth distance evaluator
    /// </summary>
    /// <returns> false if the pipeline is empty (no identified tag), otherwise true </returns>
    bool MarkerPublisher::loadMarkersPipeline () {

        //just to know the order of the pipeline metrics
        XmlRpc::XmlRpcValue xml_param;
        std::string configuration_namespace = private_node_handle_->getNamespace() + "/pipeline";
        ROS_DEBUG_STREAM("Config_ns to load pipelines: " << configuration_namespace);

        std::vector<std::pair<int,std::string>> pipeline_pair_arr;
        std::pair<int,std::string> current_pair;
        std::vector<std::string> substr_list;
        std::string delimiter = "_",
                    xml_marker_name,
                    marker_name;

        if (private_node_handle_->getParam(configuration_namespace, xml_param) &&
            xml_param.getType() == XmlRpc::XmlRpcValue::TypeStruct) {

            for (XmlRpc::XmlRpcValue::iterator it = xml_param.begin(); it != xml_param.end(); ++it) {
                xml_marker_name = it->first;
                substr_list.clear();
                splitStrings(xml_marker_name, '_', substr_list);
                current_pair.first  = std::stoi(substr_list.at(0));
                current_pair.second = substr_list.at(1);
                pipeline_pair_arr.push_back(current_pair);
            }

            std::sort(pipeline_pair_arr.begin(), pipeline_pair_arr.end(), this->cmp);

            MarkerBase::Ptr marker;

            for(size_t it = 0; it < pipeline_pair_arr.size(); it ++) {

                marker_name = std::to_string(pipeline_pair_arr.at(it).first) + delimiter + pipeline_pair_arr.at(it).second;

                if (marker_name.find("arrow") != std::string::npos) {
                    marker.reset(new ArrowMarker());
                } else if (marker_name.find("ppArrow") != std::string::npos) {
                    marker.reset(new ArrowPPMarker());
                } else if (marker_name.find("cube") != std::string::npos) {
                    marker.reset(new CubeMarker());
                } else if (marker_name.find("sphere") != std::string::npos) {
                    marker.reset(new SphereMarker());
                } else if (marker_name.find("cylinder") != std::string::npos) {
                    marker.reset(new CylinderMarker());
                } else if (marker_name.find("text") != std::string::npos) {
                    marker.reset(new TextMarker());
                } else if (marker_name.find("mesh") != std::string::npos) {
                    marker.reset(new MeshMarker());
                }
                //TODO: insert new markers ...

                if (marker) {
                    ROS_INFO_STREAM("Loading parameters for : " << configuration_namespace + "/" + marker_name);
                    //marker->setTfBuffer(tf_buffer_);
                    marker->setupMarkerConfigurationFromParameterServer(node_handle_, private_node_handle_,
                                                                        configuration_namespace, marker_name);
                    markerPipelineArrPtr_->push_back(marker);
                }
            }
        }


        if (markerPipelineArrPtr_->empty()) {
            ROS_ERROR_STREAM("The marker definition pipeline is empty.");
            return false;
        }

        return true;

    }

    bool MarkerPublisher::runPublishers(){
        for (size_t i = 0; i < markerPipelineArrPtr_->size(); ++i) {

            markerPipelineArrPtr_->at(i)->run();
        }

        return true;

    }

}// namespace end