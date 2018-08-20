######################################################################
# Automatically generated by qmake (3.0) mar ago 22 09:32:03 2017
######################################################################

TEMPLATE = app
TARGET = locomotion_framework
INCLUDEPATH += .

# Input
HEADERS += common/include/mwoibn/common/ros.h \
           common/include/mwoibn/common/types.h \
           point_handling/include/mwoibn/point_handling/base_points_handler.h \
           point_handling/include/mwoibn/point_handling/point.h \
           point_handling/include/mwoibn/point_handling/point_handling.h \
           point_handling/include/mwoibn/point_handling/raw_full_states_handler.h \
           point_handling/include/mwoibn/point_handling/raw_orientations_handler.h \
           point_handling/include/mwoibn/point_handling/raw_positions_handler.h \
           point_handling/include/mwoibn/point_handling/state_points_handler.h \
           reference_generation/include/mwoibn/reference_generation/basic_object.h \
           reference_generation/include/mwoibn/reference_generation/line.h \
           reference_generation/include/mwoibn/reference_generation/local_circle.h \
           reference_generation/include/mwoibn/reference_generation/reference_generation.h \
           reference_generation/include/mwoibn/reference_generation/utils.h \
           robot_point_handling/include/mwoibn/point_handling/robot_points_handler.h \
           simple_log/include/mwoibn/simple_log/log.h \
           tests_common/include/mwoibn/tests_common/test.h \
           tests_common/include/mwoibn/tests_common/test_collision.h \
           tests_common/include/mwoibn/tests_common/tests_common.h \
           controllers/basic_controllers/include/mwoibn/basic_controllers/basic_controller.h \
           controllers/basic_controllers/include/mwoibn/basic_controllers/basic_controllers.h \
           controllers/basic_controllers/include/mwoibn/basic_controllers/lower_level_controller.h \
           controllers/gravity_compensation/include/mwoibn/gravity_compensation/gravity_compensation.h \
           controllers/gravity_compensation/include/mwoibn/gravity_compensation/simple_qr_gravity_compensation.h \
           controllers/hierarchical_control/include/mwoibn/hierarchical_control/cartesian_reference_task.h \
           controllers/hierarchical_control/include/mwoibn/hierarchical_control/cartesian_selective_task.h \
           controllers/hierarchical_control/include/mwoibn/hierarchical_control/cartesian_simplified_pelvis_task_v2.h \
           controllers/hierarchical_control/include/mwoibn/hierarchical_control/cartesian_simplified_pelvis_task_v3.h \
           controllers/hierarchical_control/include/mwoibn/hierarchical_control/cartesian_world_task.h \
           controllers/hierarchical_control/include/mwoibn/hierarchical_control/center_of_mass_task.h \
           controllers/hierarchical_control/include/mwoibn/hierarchical_control/constraints_task.h \
           controllers/hierarchical_control/include/mwoibn/hierarchical_control/controller_task.h \
           controllers/hierarchical_control/include/mwoibn/hierarchical_control/hierarchical_control.h \
           controllers/hierarchical_control/include/mwoibn/hierarchical_control/hierarchical_controller.h \
           controllers/hierarchical_control/include/mwoibn/hierarchical_control/hierarchical_controller_continous.h \
           controllers/hierarchical_control/include/mwoibn/hierarchical_control/joint_positions_task.h \
           controllers/hierarchical_control/include/mwoibn/hierarchical_control/orientation_selective_task.h \
           controllers/hierarchical_control/include/mwoibn/hierarchical_control/orientation_world_task.h \
           controllers/hierarchical_control/include/mwoibn/hierarchical_control/self_collision_task.h \
           controllers/hierarchical_control/include/mwoibn/hierarchical_control/self_collisions_task.h \
           controllers/motor_side_reference/include/mwoibn/motor_side_reference/motor_side_reference.h \
           controllers/motor_side_reference/include/mwoibn/motor_side_reference/sea_reference.h \
           models/collision_model/include/mwoibn/collision_model/collision_model.h \
           models/collision_model/include/mwoibn/collision_model/robot_collision.h \
           models/dynamic_models/include/mwoibn/dynamic_models/basic_model.h \
           models/dynamic_models/include/mwoibn/dynamic_models/dynamic_models.h \
           models/dynamic_models/include/mwoibn/dynamic_models/qr_decomposition.h \
           models/robot_class/include/mwoibn/communication_modules/basic_module.h \
           models/robot_class/include/mwoibn/communication_modules/communication_modules.h \
           models/robot_class/include/mwoibn/robot_class/actuator.h \
           models/robot_class/include/mwoibn/robot_class/actuators.h \
           models/robot_class/include/mwoibn/robot_class/center_of_mass.h \
           models/robot_class/include/mwoibn/robot_class/contact_v2.h \
           models/robot_class/include/mwoibn/robot_class/contacts.h \
           models/robot_class/include/mwoibn/robot_class/robot.h \
           models/robot_class/include/mwoibn/robot_class/robot_class.h \
           models/robot_class/include/mwoibn/robot_class/state.h \
           models/robot_class/include/mwoibn/robot_class/wheel_contact.h \
           models/robot_class/test/include/mwoibn/test.h \
           models/visualization_tools/include/mwoibn/visualization_tools/rviz_custom_model.h \
           models/visualization_tools/include/mwoibn/visualization_tools/rviz_distinc_links.h \
           models/visualization_tools/include/mwoibn/visualization_tools/rviz_joint_limits.h \
           models/visualization_tools/include/mwoibn/visualization_tools/rviz_track_point.h \
           models/visualization_tools/include/mwoibn/visualization_tools/visualization_tools.h \
           point_handling/test/include/mwoibn/point_handling/test.h \
           robot_point_handling/test/include/mwoibn/point_handling/make_log.h \
           ros/collision_model_ros_extension/include/mwoibn/collision_model/robot_collision_ros.h \
           ros/collision_model_ros_extension/include/mwoibn/collision_model/vision.h \
           ros/communication_modules_ros_extension/include/mwoibn/communication_modules/custom_controller.h \
           ros/robot_class_ros_extension/include/mwoibn/robot_class/contact_ros.h \
           ros/robot_class_ros_extension/include/mwoibn/robot_class/robot_ros.h \
           ros/robot_class_ros_extension/include/mwoibn/robot_class/robot_ros_nrt.h \
           utils/eigen_utils/include/mwoibn/eigen_utils/eigen_utils.h \
           utils/eigen_utils/include/mwoibn/eigen_utils/quaternion.h \
           utils/rbdl_utils/include/mwoibn/rbdl_utils/quaternion.h \
           utils/rbdl_utils/include/mwoibn/rbdl_utils/rbdl_utils.h \
           xbot/robot_class_xbot/include/mwoibn/robot_class/robot_xbot.h \
    models/robot_class/include/mwoibn/robot_class/map.h \
    models/robot_class/include/mwoibn/robot_class/mappings.h \
    common/include/mwoibn/common/ros.h \
    common/include/mwoibn/common/types.h \
    controllers/basic_controllers/include/mwoibn/basic_controllers/basic_controller.h \
    controllers/basic_controllers/include/mwoibn/basic_controllers/basic_controllers.h \
    controllers/basic_controllers/include/mwoibn/basic_controllers/lower_level_controller.h \
    controllers/gravity_compensation/include/mwoibn/gravity_compensation/gravity_compensation.h \
    controllers/gravity_compensation/include/mwoibn/gravity_compensation/simple_qr_gravity_compensation.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/cartesian_reference_task.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/cartesian_selective_task.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/cartesian_simplified_pelvis_task_v2.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/cartesian_simplified_pelvis_task_v3.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/cartesian_world_task.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/center_of_mass_task.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/constraints_task.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/controller_task.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/hierarchical_control.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/hierarchical_controller.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/hierarchical_controller_continous.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/joint_positions_task.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/orientation_selective_task.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/orientation_world_task.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/self_collision_task.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/self_collisions_task.h \
    controllers/motor_side_reference/include/mwoibn/motor_side_reference/motor_side_reference.h \
    controllers/motor_side_reference/include/mwoibn/motor_side_reference/sea_reference.h \
    models/collision_model/include/mwoibn/collision_model/collision_model.h \
    models/collision_model/include/mwoibn/collision_model/robot_collision.h \
    models/dynamic_models/include/mwoibn/dynamic_models/basic_model.h \
    models/dynamic_models/include/mwoibn/dynamic_models/dynamic_models.h \
    models/dynamic_models/include/mwoibn/dynamic_models/qr_decomposition.h \
    models/robot_class/include/mwoibn/communication_modules/basic_module.h \
    models/robot_class/include/mwoibn/communication_modules/communication_modules.h \
    models/robot_class/include/mwoibn/robot_class/actuator.h \
    models/robot_class/include/mwoibn/robot_class/actuators.h \
    models/robot_class/include/mwoibn/robot_class/center_of_mass.h \
    models/robot_class/include/mwoibn/robot_class/contact_v2.h \
    models/robot_class/include/mwoibn/robot_class/contacts.h \
    models/robot_class/include/mwoibn/robot_class/map.h \
    models/robot_class/include/mwoibn/robot_class/mappings.h \
    models/robot_class/include/mwoibn/robot_class/robot.h \
    models/robot_class/include/mwoibn/robot_class/robot_class.h \
    models/robot_class/include/mwoibn/robot_class/state.h \
    models/robot_class/include/mwoibn/robot_class/wheel_contact.h \
    models/robot_class/test/include/mwoibn/test.h \
    models/visualization_tools/include/mwoibn/visualization_tools/rviz_custom_model.h \
    models/visualization_tools/include/mwoibn/visualization_tools/rviz_distinc_links.h \
    models/visualization_tools/include/mwoibn/visualization_tools/rviz_joint_limits.h \
    models/visualization_tools/include/mwoibn/visualization_tools/rviz_track_point.h \
    models/visualization_tools/include/mwoibn/visualization_tools/visualization_tools.h \
    point_handling/include/mwoibn/point_handling/base_points_handler.h \
    point_handling/include/mwoibn/point_handling/point.h \
    point_handling/include/mwoibn/point_handling/point_handling.h \
    point_handling/include/mwoibn/point_handling/raw_full_states_handler.h \
    point_handling/include/mwoibn/point_handling/raw_orientations_handler.h \
    point_handling/include/mwoibn/point_handling/raw_positions_handler.h \
    point_handling/include/mwoibn/point_handling/state_points_handler.h \
    point_handling/test/include/mwoibn/point_handling/test.h \
    reference_generation/include/mwoibn/reference_generation/basic_object.h \
    reference_generation/include/mwoibn/reference_generation/line.h \
    reference_generation/include/mwoibn/reference_generation/local_circle.h \
    reference_generation/include/mwoibn/reference_generation/reference_generation.h \
    reference_generation/include/mwoibn/reference_generation/utils.h \
    robot_point_handling/include/mwoibn/point_handling/robot_points_handler.h \
    robot_point_handling/test/include/mwoibn/point_handling/make_log.h \
    ros/collision_model_ros_extension/include/mwoibn/collision_model/robot_collision_ros.h \
    ros/collision_model_ros_extension/include/mwoibn/collision_model/vision.h \
    ros/communication_modules_ros_extension/include/mwoibn/communication_modules/custom_controller.h \
    ros/robot_class_ros_extension/include/mwoibn/robot_class/contact_ros.h \
    ros/robot_class_ros_extension/include/mwoibn/robot_class/robot_ros.h \
    ros/robot_class_ros_extension/include/mwoibn/robot_class/robot_ros_nrt.h \
    simple_log/include/mwoibn/simple_log/log.h \
    tests_common/include/mwoibn/tests_common/test.h \
    tests_common/include/mwoibn/tests_common/test_collision.h \
    tests_common/include/mwoibn/tests_common/tests_common.h \
    utils/eigen_utils/include/mwoibn/eigen_utils/eigen_utils.h \
    utils/eigen_utils/include/mwoibn/eigen_utils/quaternion.h \
    utils/rbdl_utils/include/mwoibn/rbdl_utils/quaternion.h \
    utils/rbdl_utils/include/mwoibn/rbdl_utils/rbdl_utils.h \
    xbot/robot_class_xbot/include/mwoibn/robot_class/robot_xbot.h \
    xbot/communication_modules_xbot/include/mwoibn/xbot_lower_level.h \
    xbot/communication_modules_xbot/include/mwoibn/communication_modules/xbot_lower_level.h \
    xbot/robot_class_xbot/include/mwoibn/robot_class/robot_xbot_feedback.h \
    models/robot_class/include/mwoibn/communication_modules/basic_controller.h \
    models/robot_class/include/mwoibn/communication_modules/basic_feedback.h \
    ros/communication_modules_ros_extension/include/mwoibn/communication_modules/ros_controller.h \
    ros/communication_modules_ros_extension/include/mwoibn/communication_modules/ros_feedback.h \
    models/robot_class/include/mwoibn/robot_class/controllers.h \
    models/robot_class/include/mwoibn/robot_class/feedbacks.h \
    models/robot_class/include/mwoibn/communication_modules/basic_operational_euler.h \
    ros/communication_modules_ros_extension/include/mwoibn/communication_modules/ros_operational_euler.h \
    xbot/communication_modules_xbot/include/mwoibn/communication_modules/xbot_feedback_online.h \
    xbot/communication_modules_xbot/include/mwoibn/communication_modules/xbot_operational_euler.h \
    xbot/robot_class_xbot/include/mwoibn/robot_class/robot_xbot_nrt.h \
    xbot/robot_class_xbot/include/mwoibn/robot_class/robot_xbot_rt.h \
    xbot/communication_modules_xbot/include/mwoibn/communication_modules/xbot_feedback_shared.h \
    xbot/communication_modules_xbot/include/mwoibn/communication_modules/xbot_controller_shared.h \
    xbot/communication_modules_xbot/include/mwoibn/communication_modules/xbot_feedback_from_nrt.h \
    xbot/communication_modules_xbot/include/mwoibn/communication_modules/xbot_controller_to_rt.h \
    xbot/communication_modules_xbot/include/mwoibn/communication_modules/xbot_feedback_from_rt.h \
    xbot/communication_modules_xbot/include/mwoibn/communication_modules/xbot_controller_to_nrt.h \
    xbot/communication_modules_xbot/include/mwoibn/communication_modules/xbot_operational_euler_from_nrt.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/cartesian_simplified_pelvis_task_v3.h \
    ros/communication_modules_ros_extension/include/mwoibn/communication_modules/velocity_controller.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/cartesian_simplified_pelvis_task_v4.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/castor_angle_task.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/camber_angle_task.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/steering_angle_task.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/camber_angle_task_2.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/cartesian_simplified_pelvis_task_v5.h \
    models/loaders/include/mwoibn/loaders/config.h \
    models/loaders/include/mwoibn/loaders/robot.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/center_of_mass_task_v2.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/cartesian_simplified_pelvis_task_v6.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/cartesian_simplified_pelvis_task_v7.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/cartesian_simplified_pelvis_task_world.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/castor_angle_task_2.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/center_of_mass_task_v3.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/constraints_task_v2.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/contact_point_2D_rbdl_task.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/contact_point_3D_rbdl_task.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/contact_point_rbdl_task.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/contact_point_tracking_task.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/actions/basic_action.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/actions/compute.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/actions/controller.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/actions/idle.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/actions/primary.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/actions/replace.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/actions/secondary.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/actions/snap.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/actions/task.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/controllers/actions.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/controllers/basic.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/controllers/continous.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/controllers/default.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/controllers/memory_manager.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/controllers/wheels.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/tasks/aggravated.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/tasks/angle.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/tasks/camber_angle_task_2.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/tasks/cartesian_reference_task.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/tasks/cartesian_selective_task.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/tasks/cartesian_simplified_pelvis_task_v2.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/tasks/cartesian_simplified_pelvis_task_v3.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/tasks/cartesian_simplified_pelvis_task_v4.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/tasks/cartesian_simplified_pelvis_task_v5.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/tasks/cartesian_simplified_pelvis_task_v6.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/tasks/cartesian_simplified_pelvis_task_v7.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/tasks/cartesian_simplified_pelvis_task_world.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/tasks/cartesian_world_task.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/tasks/castor_angle_task.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/tasks/castor_angle_task0.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/tasks/center_of_mass_task.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/tasks/center_of_mass_task_v2.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/tasks/center_of_mass_task_v3.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/tasks/constraints_task.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/tasks/constraints_task_v2.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/tasks/contact_point_2D_rbdl_task.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/tasks/contact_point_3D_rbdl_task.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/tasks/contact_point_rbdl_task.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/tasks/contact_point_tracking_task.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/tasks/controller_task.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/tasks/joint_positions_task.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/tasks/orientation_selective_task.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/tasks/orientation_world_task.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/tasks/self_collision_task.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/tasks/self_collisions_task.h \
    controllers/hierarchical_control/include/mwoibn/hierarchical_control/tasks/steering_angle_task.h
SOURCES += point_handling/devel_tests/simple_test.cpp \
           point_handling/src/base_points_handler.cpp \
           point_handling/src/point.cpp \
           reference_generation/src/line.cpp \
           reference_generation/src/local_circle.cpp \
           reference_generation/src/utils.cpp \
           controllers/hierarchical_control/src/cartesian_world_task.cpp \
           controllers/hierarchical_control/src/center_of_mass_task.cpp \
           controllers/hierarchical_control/src/constraints_task.cpp \
           controllers/hierarchical_control/src/controller_task.cpp \
           controllers/hierarchical_control/src/hierarchical_controller.cpp \
           controllers/hierarchical_control/src/hierarchical_controller_continous.cpp \
           controllers/hierarchical_control/src/joint_positions_task.cpp \
           controllers/hierarchical_control/src/orientation_world_task.cpp \
           controllers/hierarchical_control/src/self_collision_task.cpp \
           controllers/hierarchical_control/src/self_collisions_task.cpp \
           controllers/motor_side_reference/src/sea_reference.cpp \
           models/collision_model/src/robot_collision.cpp \
           models/dynamic_models/test/test_dynamic_model_qr.cpp \
           models/robot_class/src/actuator.cpp \
           models/robot_class/src/actuators.cpp \
           models/robot_class/src/center_of_mass.cpp \
           models/robot_class/src/contact_v2.cpp \
           models/robot_class/src/contacts.cpp \
           models/robot_class/src/robot.cpp \
           models/robot_class/src/state.cpp \
           models/robot_class/src/wheel_contact.cpp \
           models/visualization_tools/src/rviz_custom_model.cpp \
           models/visualization_tools/src/rviz_distinc_links.cpp \
           models/visualization_tools/src/rviz_joint_limits.cpp \
           models/visualization_tools/src/rviz_track_point.cpp \
           point_handling/test/src/test_full_state_handler.cpp \
           point_handling/test/src/test_orientation_handler.cpp \
           point_handling/test/src/test_point_handling.cpp \
           point_handling/test/src/test_point_position.cpp \
           point_handling/test/src/test_position_handler.cpp \
           robot_point_handling/test/src/test_point_handling.cpp \
           robot_point_handling/test/src/test_robot_handler.cpp \
           ros/collision_model_ros_extension/src/vision.cpp \
           ros/communication_modules_ros_extension/src/custom_controller.cpp \
           ros/robot_class_ros_extension/src/contact_ros.cpp \
           ros/robot_class_ros_extension/src/robot_ros.cpp \
           ros/robot_class_ros_extension/src/robot_ros_nrt.cpp \
           xbot/robot_class_xbot/src/robot_xbot.cpp \
           controllers/gravity_compensation/test/src/test_simple_qr_gravity_compensation.cpp \
           controllers/hierarchical_control/test/src/test_hierarchical_control.cpp \
           controllers/motor_side_reference/test/src/test_motor_side_reference.cpp \
           controllers/motor_side_reference/test/src/test_sea_reference.cpp \
           models/collision_model/test/src/test_collision_model.cpp \
           models/robot_class/test/src/test_actuators.cpp \
           models/robot_class/test/src/test_center_of_mass.cpp \
           models/robot_class/test/src/test_contacts.cpp \
           models/robot_class/test/src/test_robot_class.cpp \
           ros/collision_model_ros_extension/test/src/test_collision_model_ros.cpp \
           ros/robot_class_ros_extension/test/src/test_contacts.cpp \
           ros/robot_class_ros_extension/test/src/test_robot_ros.cpp \
           ros/robot_class_ros_extension/test/src/test_robot_ros_nrt.cpp \
           utils/eigen_utils/test/src/test_eigen_utils.cpp \
           xbot/robot_class_xbot/test/src/test_contacts.cpp \
           xbot/robot_class_xbot/test/src/test_robot_ros.cpp \
           xbot/robot_class_xbot/test/src/test_robot_ros_nrt.cpp \
           controllers/hierarchical_control/test/src/tasks/test_cartesian_world_task.cpp \
           controllers/hierarchical_control/test/src/tasks/test_center_of_mass_task.cpp \
           controllers/hierarchical_control/test/src/tasks/test_controller_task.cpp \
           controllers/hierarchical_control/test/src/tasks/test_self_collision_task.cpp \
           controllers/hierarchical_control/test/src/tasks/test_self_collisions_task.cpp \
    utils/eigen_utils/src/eigen_utils.cpp \
    controllers/gravity_compensation/test/src/test_simple_qr_gravity_compensation.cpp \
    controllers/hierarchical_control/src/cartesian_world_task.cpp \
    controllers/hierarchical_control/src/center_of_mass_task.cpp \
    controllers/hierarchical_control/src/constraints_task.cpp \
    controllers/hierarchical_control/src/controller_task.cpp \
    controllers/hierarchical_control/src/hierarchical_controller.cpp \
    controllers/hierarchical_control/src/hierarchical_controller_continous.cpp \
    controllers/hierarchical_control/src/joint_positions_task.cpp \
    controllers/hierarchical_control/src/orientation_world_task.cpp \
    controllers/hierarchical_control/src/self_collision_task.cpp \
    controllers/hierarchical_control/src/self_collisions_task.cpp \
    controllers/hierarchical_control/test/src/tasks/test_cartesian_world_task.cpp \
    controllers/hierarchical_control/test/src/tasks/test_center_of_mass_task.cpp \
    controllers/hierarchical_control/test/src/tasks/test_controller_task.cpp \
    controllers/hierarchical_control/test/src/tasks/test_self_collision_task.cpp \
    controllers/hierarchical_control/test/src/tasks/test_self_collisions_task.cpp \
    controllers/hierarchical_control/test/src/test_hierarchical_control.cpp \
    controllers/motor_side_reference/src/sea_reference.cpp \
    controllers/motor_side_reference/test/src/test_motor_side_reference.cpp \
    controllers/motor_side_reference/test/src/test_sea_reference.cpp \
    models/collision_model/src/robot_collision.cpp \
    models/collision_model/test/src/test_collision_model.cpp \
    models/dynamic_models/test/test_dynamic_model_qr.cpp \
    models/robot_class/src/actuator.cpp \
    models/robot_class/src/actuators.cpp \
    models/robot_class/src/center_of_mass.cpp \
    models/robot_class/src/contact_v2.cpp \
    models/robot_class/src/contacts.cpp \
    models/robot_class/src/robot.cpp \
    models/robot_class/src/state.cpp \
    models/robot_class/src/wheel_contact.cpp \
    models/robot_class/test/src/test_actuators.cpp \
    models/robot_class/test/src/test_center_of_mass.cpp \
    models/robot_class/test/src/test_contacts.cpp \
    models/robot_class/test/src/test_robot_class.cpp \
    models/visualization_tools/src/rviz_custom_model.cpp \
    models/visualization_tools/src/rviz_distinc_links.cpp \
    models/visualization_tools/src/rviz_joint_limits.cpp \
    models/visualization_tools/src/rviz_track_point.cpp \
    point_handling/devel_tests/simple_test.cpp \
    point_handling/src/base_points_handler.cpp \
    point_handling/src/point.cpp \
    point_handling/test/src/test_full_state_handler.cpp \
    point_handling/test/src/test_orientation_handler.cpp \
    point_handling/test/src/test_point_handling.cpp \
    point_handling/test/src/test_point_position.cpp \
    point_handling/test/src/test_position_handler.cpp \
    reference_generation/src/line.cpp \
    reference_generation/src/local_circle.cpp \
    reference_generation/src/utils.cpp \
    robot_point_handling/test/src/test_point_handling.cpp \
    robot_point_handling/test/src/test_robot_handler.cpp \
    ros/collision_model_ros_extension/src/vision.cpp \
    ros/collision_model_ros_extension/test/src/test_collision_model_ros.cpp \
    ros/communication_modules_ros_extension/src/custom_controller.cpp \
    ros/robot_class_ros_extension/src/contact_ros.cpp \
    ros/robot_class_ros_extension/src/robot_ros.cpp \
    ros/robot_class_ros_extension/src/robot_ros_nrt.cpp \
    ros/robot_class_ros_extension/test/src/test_contacts.cpp \
    ros/robot_class_ros_extension/test/src/test_robot_ros.cpp \
    ros/robot_class_ros_extension/test/src/test_robot_ros_nrt.cpp \
    utils/eigen_utils/src/eigen_utils.cpp \
    utils/eigen_utils/test/src/test_eigen_utils.cpp \
    xbot/robot_class_xbot/src/robot_xbot.cpp \
    xbot/robot_class_xbot/test/src/test_contacts.cpp \
    xbot/robot_class_xbot/test/src/test_robot_ros.cpp \
    xbot/robot_class_xbot/test/src/test_robot_ros_nrt.cpp \
    xbot/robot_class_xbot/src/robot_xbot_nrt.cpp \
    xbot/communication_modules_xbot/src/xbot_lower_level.cpp \
    xbot/robot_class_xbot/src/robot_xbot_feedback.cpp \
    ros/communication_modules_ros_extension/src/ros_controller.cpp \
    ros/communication_modules_ros_extension/src/ros_feedback.cpp \
    xbot/communication_modules_xbot/src/xbot_feedback_online.cpp \
    xbot/communication_modules_xbot/src/xbot_operational_euler.cpp \
    xbot/robot_class_xbot/src/robot_xbot_nrt.cpp \
    xbot/robot_class_xbot/src/robot_xbot_rt.cpp \
    xbot/robot_class_xbot/src/contact_ros.cpp \
    ros/communication_modules_ros_extension/src/velocity_controller.cpp \
    controllers/hierarchical_control/src/center_of_mass_task_v2.cpp \
    controllers/hierarchical_control/src/tasks/angle.cpp \
    controllers/hierarchical_control/src/controllers/actions.cpp \
    controllers/hierarchical_control/src/controllers/continous.cpp \
    controllers/hierarchical_control/src/controllers/default.cpp \
    controllers/hierarchical_control/src/controllers/wheels.cpp \
    controllers/hierarchical_control/src/tasks/aggravated.cpp \
    controllers/hierarchical_control/src/tasks/cartesian_world_task.cpp \
    controllers/hierarchical_control/src/tasks/center_of_mass_task.cpp \
    controllers/hierarchical_control/src/tasks/center_of_mass_task_v2.cpp \
    controllers/hierarchical_control/src/tasks/center_of_mass_task_v3.cpp \
    controllers/hierarchical_control/src/tasks/constraints_task.cpp \
    controllers/hierarchical_control/src/tasks/controller_task.cpp \
    controllers/hierarchical_control/src/tasks/controller_task_v2.cpp \
    controllers/hierarchical_control/src/tasks/controller_task_v2_copy.cpp \
    controllers/hierarchical_control/src/tasks/joint_positions_task.cpp \
    controllers/hierarchical_control/src/tasks/orientation_world_task.cpp \
    controllers/hierarchical_control/src/tasks/self_collision_task.cpp \
    controllers/hierarchical_control/src/tasks/self_collisions_task.cpp

DISTFILES += \
    controllers/motor_side_reference/test/launch/test_motor_side_reference.test \
    controllers/hierarchical_control/test/resources/cartesian_position_task.txt.old \
    controllers/hierarchical_control/test/resources/hierarchical_controller.txt.old \
    controllers/hierarchical_control/test/resources/cartesian_position_task.backup \
    controllers/hierarchical_control/test/resources/cartesian_world_task.txt \
    controllers/hierarchical_control/test/resources/center_of_mass_task.txt \
    controllers/hierarchical_control/test/resources/hierarchical_controller.backup \
    controllers/hierarchical_control/test/resources/hierarchical_controller.txt \
    controllers/hierarchical_control/test/resources/self_collision_controller.backup \
    controllers/hierarchical_control/test/resources/self_collision_controller.txt \
    controllers/hierarchical_control/test/resources/self_collisions_controller.backup \
    controllers/hierarchical_control/test/resources/self_collisions_controller.txt \
    xbot/robot_class_xbot/include/configs/srdf/centauro_full_wheels.srdf \
    xbot/robot_class_xbot/include/configs/srdf/centauro_lower_body.srdf \
    xbot/robot_class_xbot/include/configs/urdf/centauro.urdf \
    xbot/robot_class_xbot/include/configs/urdf/centauro_lower_body.urdf \
    xbot/robot_class_xbot/include/configs/urdf/centauro_static.urdf \
    xbot/robot_class_xbot/include/configs/joint_map/centauro_joint_map.yaml \
    xbot/robot_class_xbot/include/configs/joint_map/centauro_lower_body.yaml \
    xbot/robot_class_xbot/include/configs/config_centauro.yaml \
    ros/collision_model_ros_extension/test/launch/test_collision_model_ros.test \
    ros/robot_class_ros_extension/test/launch/test_robot_ros_nrt.test \
    xbot/robot_class_xbot/test/launch/test_robot_ros_nrt.test \
    configs/mwoibn_v2.yaml \
    ros/collision_model_ros_extension/package.xml \
    ros/communication_modules_ros_extension/package.xml \
    ros/robot_class_ros_extension/package.xml \
    xbot/robot_class_xbot/package.xml \
    ros/collision_model_ros_extension/config/FindEigen3.cmake \
    ros/collision_model_ros_extension/config/FindRBDL.cmake \
    ros/collision_model_ros_extension/config/Findsch_viewer.cmake \
    ros/communication_modules_ros_extension/config/FindEigen3.cmake \
    ros/communication_modules_ros_extension/config/FindRBDL.cmake \
    xbot/robot_class_xbot/config/FindXBotInterface.cmake \
    xbot/robot_class_xbot/config/FindXCM.cmake \
    ros/collision_model_ros_extension/CMakeLists.txt \
    ros/communication_modules_ros_extension/CMakeLists.txt \
    ros/robot_class_ros_extension/CMakeLists.txt \
    xbot/robot_class_xbot/CMakeLists.txt

unix:!macx: LIBS += -L$$PWD/../../../install_release/lib/ -lcentralized_controllers
unix:!macx: LIBS += -L$$PWD/../../../install_release/lib/ -lsimpe_log

INCLUDEPATH += $$PWD/../../../install_release/include
DEPENDPATH += $$PWD/../../../install_release/include
INCLUDEPATH += /home/malgorzata/ADVR-Humanoids/advr-superbuild/build/install/include
INCLUDEPATH += /usr/include/eigen3
