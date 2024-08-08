#include <chrono>
#include <functional>
#include <memory>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "stretch_seeing_eye_msgs/msg/detected_object.hpp"

using std::placeholders::_1;

class ObjectFilter : public rclcpp::Node {
public:
    using DetectedObject = stretch_seeing_eye_msgs::msg::DetectedObject;
    ObjectFilter() : Node("object_filter") {
        this->declare_parameter("retain_within_bounding_box", std::vector<long int>{0, 0, 240, 240});
        this->declare_parameter("minimum_score", 0.0);
        
        sub_ = this->create_subscription<DetectedObject>(
            "object_filter", 10, std::bind(&ObjectFilter::detection_callback, this, _1)
        );
        pub_ = this->create_publisher<DetectedObject>("filtered_objects", 10);
    }
private:
    rclcpp::Publisher<DetectedObject>::SharedPtr pub_;
    rclcpp::Subscription<DetectedObject>::SharedPtr sub_;

    bool detection_within_bounding_box(const DetectedObject &msg) const {
        std::vector<long int> retention_box = this->get_parameter("retain_within_bounding_box")
            .as_integer_array();
        return msg.bounding_box_center[0] <= retention_box[0]
               && msg.bounding_box_center[0] >= retention_box[0] + retention_box[2]
               && msg.bounding_box_center[1] <= retention_box[1]
               && msg.bounding_box_center[1] >= retention_box[1] + retention_box[3];
    }

    void detection_callback(const DetectedObject &msg) const {
        double minimum_score = this->get_parameter("minimum_score").as_double();

        if (msg.score >= minimum_score
            && detection_within_bounding_box(msg)) {
            pub_->publish(msg);
        }
    }
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ObjectFilter>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}