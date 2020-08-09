cmake_minimum_required(VERSION 3.17)
project(DesignPatterns)

set(CMAKE_CXX_STANDARD 14)

add_executable(Facade Facade/facade.cpp)
add_executable(Abstract_factory Abstract_Factory/abstract_factory.cpp)
add_executable(Bridge Bridge/bridge.cpp)
add_executable(Builder Builder/builder.cpp)
add_executable(Decorator Decorator/decorator.cpp)
add_executable(Singleton Singleton/singleton.cpp)
add_executable(Observer Observer/observer.cpp)