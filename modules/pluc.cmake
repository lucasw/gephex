
add_custom_command(OUTPUT ${PROJECT_NAME}.h
    COMMAND python ${CMAKE_HOME_DIRECTORY}/modules/pluc.py h ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.spec
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.spec
    COMMENT "generating ${PROJECT_NAME} header"
)

add_custom_command(OUTPUT ${PROJECT_NAME}_auto.c
    COMMAND python ${CMAKE_HOME_DIRECTORY}/modules/pluc.py c ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.spec
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.spec
    COMMENT "generating ${PROJECT_NAME} header"
)
