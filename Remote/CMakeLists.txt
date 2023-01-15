idf_component_register(SRCS "Lasko.cpp" "Remote.cpp"
                    INCLUDE_DIRS "include")

set_source_files_properties(
        "Remote.cpp"
        PROPERTIES COMPILE_FLAGS
        -Wmissing-field-initializers
)