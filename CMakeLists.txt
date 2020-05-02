project(ensembleapi)

cmake_minimum_required(VERSION 2.8)

#opencv
#find_package(OpenCV REQUIRED)
#include_directories( ${OPENCV_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR} )

#boost
#find_package(Boost REQUIRED COMPONENTS thread)

set(APPENDED_SOURCE)

# 하위 디렉토리 추가
add_subdirectory(module)
add_subdirectory(src)

include_directories( ./module/EnsembleCommand )
include_directories( ./module/EnsembleCommon )
include_directories( ./module/PacketEthComm )
include_directories( ./module/PacketEthComm/Client )
include_directories( ./src )
include_directories( ./src/interface )


# 추가 할 파일의 확장자
file(GLOB SOURCES_IN_CURRENT_DIR   "${CMAKE_CURRENT_LIST_DIR}/*.cpp")

file(GLOB HEADER_IN_CURRENT_DIR   "${CMAKE_CURRENT_LIST_DIR}/*.h" 
                                  "${CMAKE_CURRENT_LIST_DIR}/*.hpp")
                                    
set(APPENDED_SOURCE ${SOURCES_IN_CURRENT_DIR} ${APPENDED_SOURCE})
set(APPENDED_HEADER ${HEADER_IN_CURRENT_DIR} ${APPENDED_HEADER})

foreach(SOURCE ${APPENDED_SOURCE})
    message("${SOURCE}")
endforeach(SOURCE)

foreach(SOURCE ${APPENDED_SOURCE})
    file(RELATIVE_PATH RELATIVE ${PROJECT_SOURCE_DIR} ${SOURCE})
    
    get_filename_component(FILENAME ${RELATIVE} NAME)
    get_filename_component(PARENT_DIRECTORY ${RELATIVE} DIRECTORY)

    message(STATUS "${FILENAME} in ${PARENT_DIRECTORY}")    
    source_group(${PARENT_DIRECTORY} FILES ${SOURCE})
endforeach(SOURCE)

add_library( ensembleapi STATIC ${APPENDED_SOURCE} )

#target_link_libraries(ensembleapi ${OpenCV_LIBS})

#install
SET ( CMAKE_INSTALL_PREFIX ./install )

install(TARGETS         ensembleapi
        DESTINATION     lib)
        
foreach(HEADER ${APPENDED_HEADER})
    file(RELATIVE_PATH RELATIVE ${PROJECT_SOURCE_DIR} ${HEADER})
    get_filename_component(FILENAME ${RELATIVE} NAME)
    get_filename_component(PARENT_DIRECTORY ${RELATIVE} DIRECTORY)

	install(FILES            ${HEADER}
        DESTINATION     	include/${PARENT_DIRECTORY}/${FILENAME}
	)
    
endforeach(HEADER)


