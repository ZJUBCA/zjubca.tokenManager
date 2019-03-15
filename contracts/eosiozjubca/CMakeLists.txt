add_contract(eosiozjubca eosiozjubca ${CMAKE_CURRENT_SOURCE_DIR}/src/eosiozjubca.cpp)
target_include_directories(eosiozjubca.wasm
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(eosiozjubca.wasm
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
