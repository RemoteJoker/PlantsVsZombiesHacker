# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\PlantsVsZombiesFunc_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\PlantsVsZombiesFunc_autogen.dir\\ParseCache.txt"
  "PlantsVsZombiesFunc_autogen"
  )
endif()
