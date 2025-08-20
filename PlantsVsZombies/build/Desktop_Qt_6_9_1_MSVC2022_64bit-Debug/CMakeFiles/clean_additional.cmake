# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\PlantsVsZombies_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\PlantsVsZombies_autogen.dir\\ParseCache.txt"
  "PlantsVsZombies_autogen"
  )
endif()
