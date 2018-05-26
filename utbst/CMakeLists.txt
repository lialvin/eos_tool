include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/src)
link_directories( /usr/local/boost_1_66_0/stage/lib ${PROJECT_BINARY_DIR}/lib)

ADD_DEFINITIONS(-DBOOST_ALL_DYN_LINK)
set(MAIN_SRC_LIST
  steadytime.cpp 
  )

set(MAIN_HEADERS       )

#file(GLOB HEADERS "*.h")
#add_library(ethcore ${SRC_LIST} ${HEADERS})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
#add_executable(testma ${APP_SRC})

set(IMPORTLIB 
   boost_system boost_filesystem boost_program_options boost_thread m
   boost_log_setup  boost_log boost_date_time boost_chrono
)

add_executable(test_steady_time  steadytime.cpp)
target_link_libraries(test_steady_time  ${IMPORTLIB})

add_executable(test_bpo   bpo.cpp)
target_link_libraries(test_bpo  ${IMPORTLIB})

