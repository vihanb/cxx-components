idf_component_register(SRCS "Master.cpp" "Slave.cpp" "devices/MAX17043.cpp"
                    INCLUDE_DIRS "include"
                    REQUIRES CXXFreeRTOS)
