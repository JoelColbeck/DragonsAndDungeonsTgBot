cmake_minimum_required(VERSION 3.16)
project(testbot)

set(CMAKE_CXX_STANDARD 14)



include_directories(/Users/joelcolbeck/Work/tgbot-cpp/include)
add_executable(testing main.cpp)

# see https://cmake.org/cmake/help/latest/module/FindBoost.html
find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)
find_package(CURL)

include_directories(/usr/local/include ${OPENSSL_LIBRARIES} ${Boost_INCLUDE_DIR})
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()
#
# -L /usr/lib -lssl -lcrypto
# OPENSSL_ROOT_DIR=/usr/local/Cellar/openssl/1.0.2s
# Note: a target should be already defined using 'add_executable' or 'add_library'
target_link_libraries(testing /usr/local/lib/libTgBot.a ${CMAKE_THREAD_LIBS_INIT}
        /usr/local/Cellar/openssl/1.0.2s/lib/libssl.a
        /usr/local/Cellar/openssl/1.0.2s/lib/libcrypto.a
        ${Boost_LIBRARIES} ${CURL_LIBRARIES})

