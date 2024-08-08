#include <chrono>
#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "stretch_seeing_eye_msgs/msg/detected_object.hpp"
#include "stretch_seeing_eye_msgs/msg/robot_pathing_state.hpp"

using std::placeholders::_1;

class Planning : public rclcpp::Node {
public:
    using DetectedObject = stretch_seeing_eye_msgs::msg::DetectedObject;
    using RobotState = stretch_seeing_eye_msgs::msg::RobotPathingState;
    Planning() : Node("planning_node") {
        state_pub_ = this->create_publisher<RobotState>("robot_pathing_state", 10);
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(500),
            std::bind(&Planning::timer_callback, this)
        );
        sub_ = this->create_subscription<DetectedObject>(
            "filtered_objects", 10, std::bind(&Planning::object_callback, this, _1)
        );
    }
private:
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<RobotState>::SharedPtr state_pub_;
    rclcpp::Subscription<DetectedObject>::SharedPtr sub_;

    void timer_callback() {
        auto msg = RobotState();
        msg.state = msg.SUCCESS;
        msg.detour_attempt = false;
        msg.moving_around_object = false;
        state_pub_->publish(msg);
    }

    void object_callback(const DetectedObject &msg) const {
        RCLCPP_INFO(this->get_logger(), "TEST: Filtered object found: %s", msg.class_name.c_str());
    }
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Planning>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}