include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/src)
link_directories( /usr/local/boost_1_67_0/stage/lib ${PROJECT_BINARY_DIR}/lib)

ADD_DEFINITIONS(-DBOOST_ALL_DYN_LINK)
set(MAIN_SRC_LIST
    BizDeal.cpp  
    connection.cpp  
    main.cpp  
    reply.cpp  
    server.cpp  
    TcpSplitPkt.cpp
    io_context_pool.cpp  
    connection_manager.cpp
  )

set(MAIN_HEADERS
   BizDeal.h  netpdu.h  TcpSplitPkt.h
   ostypedef.h
   connection.hpp   
   reply.hpp  server.hpp  cliTimer.hpp
   io_context_pool.hpp 
   connection_manager.hpp

)

#file(GLOB HEADERS "*.h")
#add_library(ethcore ${SRC_LIST} ${HEADERS})
set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_BINARY_DIR}/bin)
#add_executable(testma ${APP_SRC})

set(IMPORTLIB 
  pthread  boost_system boost_filesystem  
  boost_thread m 
  boost_log_setup  boost_log
)

add_executable(dappserv ${MAIN_SRC_LIST}  ${MAIN_HEADERS})
target_link_libraries(dappserv ${IMPORTLIB})

#https://www.meitulu.com/item/15559_2.html
