cmake_minimum_required(VERSION 3.5)

project(QtGrpcDemo LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(./common.cmake)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets Charts REQUIRED)

find_package(Protobuf REQUIRED)
find_package(gRPC CONFIG REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${gRPC_INCLUDE_DIRS})

add_executable(QtGrpcDemo
    bloodnewwindows.cpp
    chart.cpp
    main.cpp
    map.cpp
    test.cpp
    velocitynewwindows.cpp
    widget.cpp
    loading.cpp
    proto/communication.grpc.pb.cc
    proto/communication.pb.cc
    bloodnewwindows.h
    chart.h
    map.h
    test.h
    velocitynewwindows.h
    widget.h
    loading.h
    proto/communication.grpc.pb.h
    proto/communication.pb.h
    bloodnewwindows.ui
    map.ui
    test.ui
    velocitynewwindows.ui
    widget.ui
    loading.ui
    map.png
    ip.txt
  )


target_link_libraries(QtGrpcDemo Qt5::Widgets Qt5::Charts
      ${PROTOBUF_LIBRARIES}
      ${gRPC_GRPC_LIBRARY} 
      ${gRPC_PROTOBUF_LIBRARY}
      ${_REFLECTION}
      ${_GRPC_GRPCPP}
      ${_PROTOBUF_LIBPROTOBUF}

)
message(STATUS "${gRPC_INCLUDE_DIRS}")



