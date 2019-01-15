include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/src)
link_directories( /usr/local/boost_1_66_0/stage/lib ${PROJECT_BINARY_DIR}/lib)

ADD_DEFINITIONS(-DBOOST_ALL_DYN_LINK)
set(MAIN_SRC_LIST
  async_tcp_echo_server.cpp 
  )

set(MAIN_HEADERS
)

#file(GLOB HEADERS "*.h")
#add_library(ethcore ${SRC_LIST} ${HEADERS})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
#add_executable(testma ${APP_SRC})

set(IMPORTLIB 
   boost_system 
   boost_log_setup
   boost_log
   boost_thread
   boost_filesystem
)

add_executable(uos_moni_server  uos_main.cpp)
target_link_libraries(uos_moni_server ${IMPORTLIB})

add_executable(uos_moni_cli  uos_moni_cli.cpp)
target_link_libraries(uos_moni_cli  ${IMPORTLIB})

