add_executable(compiler)

file(GLOB_RECURSE COMPILER_INCLUDE *.h)
file(GLOB_RECURSE COMPILER_SOURCE *.cc)

target_include_directories(compiler
    PUBLIC
        .
    )

target_sources(compiler
    PUBLIC
        ${COMPILER_INCLUDE}
    PRIVATE
        ${COMPILER_SOURCE}
    )
