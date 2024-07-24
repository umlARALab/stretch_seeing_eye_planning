#include <memory>

#include "rclcpp/rclcpp.hpp"

class Planning : public rclcpp::Node {
public:
    Planning() : Node("planning_node") {

    }
private:
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Planning>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}