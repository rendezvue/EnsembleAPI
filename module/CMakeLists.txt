# 추가 할 파일의 확장자
file(GLOB SOURCES_IN_CURRENT_DIR	"${CMAKE_CURRENT_LIST_DIR}/*.cpp"
                                    "${CMAKE_CURRENT_LIST_DIR}/EnsembleCommand/*.cpp"
                                   	"${CMAKE_CURRENT_LIST_DIR}/EnsembleCommon/*.cpp"
                                   	"${CMAKE_CURRENT_LIST_DIR}/PacketEthComm/*.cpp"
                                   	"${CMAKE_CURRENT_LIST_DIR}/PacketEthComm/Client/*.cpp" )

file(GLOB HEADER_IN_CURRENT_DIR		"${CMAKE_CURRENT_LIST_DIR}/*.h" 
			            			"${CMAKE_CURRENT_LIST_DIR}/*.hpp"

									"${CMAKE_CURRENT_LIST_DIR}/EnsembleCommand/*.h" 
			            			"${CMAKE_CURRENT_LIST_DIR}/EnsembleCommand/*.hpp"

									"${CMAKE_CURRENT_LIST_DIR}/EnsembleCommon/*.h" 
			        			    "${CMAKE_CURRENT_LIST_DIR}/EnsembleCommon/*.hpp"

									"${CMAKE_CURRENT_LIST_DIR}/PacketEthComm/*.h" 
			        			    "${CMAKE_CURRENT_LIST_DIR}/PacketEthComm/*.hpp"

									"${CMAKE_CURRENT_LIST_DIR}/PacketEthComm/Client/*.h" 
			        			    "${CMAKE_CURRENT_LIST_DIR}/PacketEthComm/Client/*.hpp" )

set(APPENDED_SOURCE ${SOURCES_IN_CURRENT_DIR} ${APPENDED_SOURCE} PARENT_SCOPE)
set(APPENDED_HEADER ${HEADER_IN_CURRENT_DIR} ${APPENDED_HEADER} PARENT_SCOPE)
