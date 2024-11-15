file(GLOB src *.cpp)
target_sources(BansheeEngine PRIVATE ${src})
target_include_directories(BansheeEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})