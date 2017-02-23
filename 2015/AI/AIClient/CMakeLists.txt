cmake_minimum_required(VERSION 2.8)
SET(AIClient)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.54.0 COMPONENTS system thread regex)

set(HEADER_FILES
  include/Character.h
  include/GameMap.h
  include/NetCommandController.h
  include/NetUtility.h
  include/NetworkController.h
  include/Player.h
)

set(SOURCE_FILES
  src/Character.cpp
  src/client.cpp
  src/GameMap.cpp
  src/NetCommandController.cpp
  src/NetworkController.cpp
  src/Player.cpp
)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include) 
    add_executable (AIClient ${HEADER_FILES} ${SOURCE_FILES})
    target_link_libraries(AIClient ${Boost_LIBRARIES})                                                                                                                                                                                                                            
endif()

