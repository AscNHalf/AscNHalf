SET(DEV_SOURCES adev.cpp)

add_library(dev STATIC ${DEV_SOURCES})

target_link_libraries(
    dev
    shared
    pcre
    ${SSLLIB}
    ${MYSQL_LIBRARIES}
    ${POSTGRESQL_LIBRARIES}
)

install(TARGETS dev DESTINATION bin)
