if(POLICY CMP0207)
    cmake_policy(SET CMP0207 NEW)
endif()

file(GET_RUNTIME_DEPENDENCIES
        LIBRARIES "${TARGET_FILE}"
        RESOLVED_DEPENDENCIES_VAR RESOLVED_DLLS
        UNRESOLVED_DEPENDENCIES_VAR UNRESOLVED_DLLS
        DIRECTORIES "${SEARCH_DIR}"
        # Ignore Windows OS system DLLs (kernel32, user32, api-ms-win-*, etc.)
        PRE_EXCLUDE_REGEXES "api-ms-.*" "ext-ms-.*"
        POST_EXCLUDE_REGEXES ".*system32/.*\\.dll"
)

foreach(DLL ${RESOLVED_DLLS})
    file(COPY "${DLL}" DESTINATION "${OUTPUT_DIR}")
endforeach()
