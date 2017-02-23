cmake_minimum_required(VERSION 2.8)
SET(GameClient)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.54.0 COMPONENTS system thread regex) 

set(HEADER_FILES
  include/NetCommandController.h
  include/NetCharacter.h
  include/NetPlayer.h
  include/NetPlayerController.h
  include/NetworkController.h
  include/NetUtility.h
)

set(SOURCE_FILES
  src/NetCommandController.cpp
  src/NetCharacter.cpp
  src/NetPlayer.cpp
  src/NetPlayerController.cpp
  src/NetworkController.cpp
  src/client.cpp
)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include) 
    add_executable (GameClient ${HEADER_FILES} ${SOURCE_FILES})
    target_link_libraries(GameClient ${Boost_LIBRARIES})                                                                                                                                                                                                                            
endif()

