# 추가 할 파일의 확장자
file(GLOB SOURCES_IN_CURRENT_DIR	"${CMAKE_CURRENT_LIST_DIR}/interface/*.cpp"
	                                "${CMAKE_CURRENT_LIST_DIR}/*.cpp")

file(GLOB HEADER_IN_CURRENT_DIR	"${CMAKE_CURRENT_LIST_DIR}/interface/*.h" 
			            			"${CMAKE_CURRENT_LIST_DIR}/interface/*.hpp"
									"${CMAKE_CURRENT_LIST_DIR}/*.h" 
									"${CMAKE_CURRENT_LIST_DIR}/*.hpp")
									
set(APPENDED_SOURCE ${SOURCES_IN_CURRENT_DIR} ${APPENDED_SOURCE} PARENT_SCOPE)
set(APPENDED_HEADER ${HEADER_IN_CURRENT_DIR} ${APPENDED_HEADER} PARENT_SCOPE)

