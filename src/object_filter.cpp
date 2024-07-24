#include <memory>

#include "rclcpp/rclcpp.hpp"

class ObjectFilter : public rclcpp::Node {
public:
    ObjectFilter() : Node("object_filter") {

    }
private:
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ObjectFilter>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}