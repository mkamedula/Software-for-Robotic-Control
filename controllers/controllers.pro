######################################################################
# Automatically generated by qmake (3.0) lun set 11 13:46:26 2017
######################################################################

TEMPLATE = app
TARGET = controllers
INCLUDEPATH += .

# Input
HEADERS += rt_plugins/include/rt_plugins/all.h \
           rt_plugins/include/rt_plugins/centralized_controller.h \
           rt_plugins/include/rt_plugins/gravity_test.h \
           rt_plugins/include/rt_plugins/rt_my_test.h \
           rt_plugins/include/rt_plugins/wheeled_controller.h \
           communication/include/mgnss/communication/basic_handler.h \
           communication/include/mgnss/communication/events_handler.h \
           controllers/include/mgnss/controllers/steering.h \
           controllers/include/mgnss/controllers/wheeled_motion.h \
           controllers/include/mgnss/controllers/wheeled_references.h \
    controllers/include/mgnss/controllers/online_centralized_controller.h \
    rt_plugins/include/rt_plugins/online_centralized_controller_plugin.h \
    rt_plugins/include/mgnss/rt_plugins/centralized_controller.h \
    rt_plugins/include/mgnss/rt_plugins/gravity_test.h \
    rt_plugins/include/mgnss/rt_plugins/online_centralized_controller_plugin.h \
    rt_plugins/include/mgnss/rt_plugins/rt_my_test.h \
    rt_plugins/include/mgnss/rt_plugins/wheeled_controller.h \
    rt_plugins/include/mgnss/rt_plugins/combined_controller.h \
    development/include/cartesian_simplified_pelvis_task.h \
    development/include/cartesian_simplified_pelvis_task_v3.h \
    odometry/include/mgnss/odometry/odometry.h \
    controllers/include/mgnss/controllers/wheeled_motion_full.h \
    controllers/include/mgnss/controllers/joint_states.h \
    controllers/include/mgnss/controllers/steering_v2.h \
    controllers/include/mgnss/controllers/steering_v3.h \
    controllers/include/mgnss/controllers/steering_v4.h \
    controllers/include/mgnss/controllers/wheeled_motion_com.h \
    controllers/include/mgnss/controllers/wheeled_motion_event.h \
    controllers/include/mgnss/controllers/wheeled_motion_event_v2.h \
    controllers/include/mgnss/controllers/wheeled_references_v2.h \
    controllers/include/mgnss/controllers/wheeled_references_v3.h \
    xbot_plugins/include/mgnss/xbot_plugins/centralized_controller.h \
    xbot_plugins/include/mgnss/xbot_plugins/combined_controller.h \
    xbot_plugins/include/mgnss/xbot_plugins/gravity_test.h \
    xbot_plugins/include/mgnss/xbot_plugins/online_centralized_controller_plugin.h \
    xbot_plugins/include/mgnss/xbot_plugins/rt_my_test.h \
    xbot_plugins/include/mgnss/xbot_plugins/wheeled_controller.h \
    xbot_plugins/include/mgnss/xbot_plugins/joint_states.h \
    xbot_plugins/include/mgnss/xbot_plugins/wheeled_controller_v2.h
SOURCES += communication/src/basic_handler.cpp \
           communication/src/events_handler.cpp \
           communication/src/gazebo_base_to_RT.cpp \
           communication/src/gazebo_base_transform.cpp \
           communication/src/gravity_test_communication.cpp \
           communication/src/wheels_refs.cpp \
           controllers/src/wheeled_motion.cpp \
           controllers/src/wheeled_references.cpp \
           development/src/wheeled_locomotion_v6_a.cpp \
           development/src/wheeled_locomotion_v7.cpp \
           development/src/wheeled_locomotion_v7_a.cpp \
           development/src/wheeled_locomotion_v8.cpp \
           development/src/wheeled_locomotion_v8_a.cpp \
           nrt_software/src/center_of_mass_controller.cpp \
           nrt_software/src/centralized_controller.cpp \
           nrt_software/src/collision_check.cpp \
           nrt_software/src/gravity_test.cpp \
           nrt_software/src/hierarchical_controller_with_events.cpp \
           nrt_software/src/my_test.cpp \
           nrt_software/src/simple_trajectory.cpp \
           nrt_software/src/wheeled_locomotion_v6.cpp \
           nrt_software/src/wheeled_motion_run.cpp \
           nrt_software/src/wheels_cut.cpp \
           rt_plugins/src/centralized_controller.cpp \
           rt_plugins/src/gravity_test.cpp \
           rt_plugins/src/rt_my_test.cpp \
           rt_plugins/src/wheeled_controller.cpp \
           utils/src/real_robot_tracker.cpp \
           rt_plugins/build/CMakeFiles/feature_tests.c \
           rt_plugins/build/CMakeFiles/feature_tests.cxx \
           rt_plugins/build/CMakeFiles/3.5.1/CompilerIdC/CMakeCCompilerId.c \
           rt_plugins/build/CMakeFiles/3.5.1/CompilerIdCXX/CMakeCXXCompilerId.cpp \
    rt_plugins/src/online_centralized_controller_plugin.cpp \
    controllers/src/online_centralized_controller.cpp \
    nrt_software/src/online_centralized_controller.cpp \
    rt_plugins/src/combined_controller.cpp \
    nrt_software/src/odometry.cpp \
    odometry/src/odometry.cpp \
    controllers/src/wheeled_motion_full.cpp \
    controllers/src/steering.cpp \
    nrt_software/src/wheels_full.cpp \
    nrt_software/src/joint_states.cpp \
    controllers/src/joint_states.cpp \
    nrt_software/src/wheels_cut_v2.cpp \
    nrt_software/src/contact_test.cpp \
    controllers/src/steering_v2.cpp \
    controllers/src/steering_v3.cpp \
    controllers/src/steering_v4.cpp \
    controllers/src/wheeled_motion_com.cpp \
    controllers/src/wheeled_motion_event.cpp \
    controllers/src/wheeled_motion_event_v2.cpp \
    controllers/src/wheeled_references_v2.cpp \
    controllers/src/wheeled_references_v3.cpp \
    nrt_software/src/com_test.cpp \
    nrt_software/src/wheels_event.cpp \
    xbot_plugins/src/centralized_controller.cpp \
    xbot_plugins/src/combined_controller.cpp \
    xbot_plugins/src/gravity_test.cpp \
    xbot_plugins/src/online_centralized_controller_plugin.cpp \
    xbot_plugins/src/rt_my_test.cpp \
    xbot_plugins/src/wheeled_controller.cpp \
    xbot_plugins/src/joint_states.cpp \
    xbot_plugins/src/wheeled_controller_v2.cpp \
    communication/src/odometry_to_RT.cpp

unix:!macx: LIBS += -L$$PWD/../../../install_release/lib/

INCLUDEPATH += /opt/ros/kinetic/include
INCLUDEPATH += /usr/include/eigen3

INCLUDEPATH += $$PWD/../../../install_release/include
DEPENDPATH += $$PWD/../../../install_release/include
INCLUDEPATH += $$PWD/../../../install_debug/include
DEPENDPATH += $$PWD/../../../install_debug/include
DEPENDPATH += /home/centauro/devel-superbuild/build/install/include

DISTFILES += \
    utils/nodes/__init__.py \
    utils/nodes/collision_test \
    utils/nodes/inertia_error_generator \
    utils/nodes/load_fixed_transforms \
    utils/launch/centauro_world.launch \
    utils/launch/centauro_world_no_head.launch \
    utils/launch/rrbot_rviz.launch \
    utils/launch/tasks.launch \
    utils/nodes/circular_reference_wheels \
    rt_plugins/CMakeLists.txt \
    xbot_plugins/CMakeLists.txt
