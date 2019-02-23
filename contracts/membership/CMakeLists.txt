add_contract(membership membership ${CMAKE_CURRENT_SOURCE_DIR}/src/membership.cpp)
target_include_directories(membership.wasm
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(membership.wasm
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
