add_executable(compiler.out)

file(GLOB_RECURSE COMPILER_INCLUDE *.h)
file(GLOB_RECURSE COMPILER_SOURCE *.cc)

target_include_directories(compiler.out
    PUBLIC
        .
    )

target_sources(compiler.out
    PUBLIC
        ${COMPILER_INCLUDE}
    PRIVATE
        ${COMPILER_SOURCE}
    )
