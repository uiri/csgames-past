cmake_minimum_required(VERSION 2.8)

set(GameClient)

set(CMAKE_MODULE_PATH "/usr/local/lib/OGRE/cmake;${CMAKE_MODULE_PATH}")

set(OGRE_INCLUDE_DIRS "/usr/local/include/OGRE")
set(OGRE_Overlay_INCLUDE_DIRS "/usr/local/include/OGRE/Overlay")
#set(OGRE_SAMPLES_INCLUDE_DIRS "/usr/local/share/OGRE/samples/Common/include/")
set(OIS_INCLUDE_DIRS "/usr/include/OIS")

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.54.0 COMPONENTS system thread regex)
find_package(OGRE REQUIRED)
find_package(OIS REQUIRED)

file(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}
			${OIS_INCLUDE_DIRS}
			${OGRE_INCLUDE_DIRS}
			${OGRE_Overlay_INCLUDE_DIRS}
			${OGRE_SAMPLES_INCLUDE_DIRS})
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
    add_executable (GameClient ${HEADER_FILES} ${SOURCE_FILES})
    target_link_libraries(GameClient ${Boost_LIBRARIES} ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${OGRE_Overlay_LIBRARIES})
    
endif()

