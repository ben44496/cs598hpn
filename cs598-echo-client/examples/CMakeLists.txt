build_lib_example(
    NAME cs598-echo-client-example
    SOURCE_FILES cs598-echo-client-example.cc
    LIBRARIES_TO_LINK
        ${libapplications}
        ${libpoint-to-point}
        ${libinternet}
        ${libnetwork}
        ${libcs598-echo-client}
)

