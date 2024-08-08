from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.conditions import IfCondition, UnlessCondition
from launch.substitutions import LaunchConfiguration, PythonExpression
from launch_ros.actions import Node


def generate_launch_description():
    params_file_set = PythonExpression(
        ["'", LaunchConfiguration("param_file"), "' != ''"]
    )
    return LaunchDescription([
        DeclareLaunchArgument(
            "param_file",
            default_value="",
            description="A parameters .yaml file for object filter/planning configuration."
        ),
        Node(
            package="stretch_seeing_eye_planning",
            executable="object_filter",
            output="screen",
            parameters=[LaunchConfiguration("param_file")],
            condition=IfCondition(params_file_set)
        ),
        Node(
            package="stretch_seeing_eye_planning",
            executable="object_filter",
            output="screen",
            condition=UnlessCondition(params_file_set)
        ),
        Node(
            package="stretch_seeing_eye_planning",
            executable="planning_node",
            output="screen"
        )
    ])
