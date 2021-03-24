

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(compiler_options INTERFACE)
# Language standard
target_compile_features(compiler_options INTERFACE cxx_std_20)

# Link this 'library' to use the standard warnings
add_library(compiler_warnings INTERFACE)
# Warnings
target_compile_options(compiler_warnings INTERFACE /W4 "/permissive-")
