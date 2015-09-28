## ======================================================================== ##
## Copyright 2009-2015 Intel Corporation                                    ##
##                                                                          ##
## Licensed under the Apache License, Version 2.0 (the "License");          ##
## you may not use this file except in compliance with the License.         ##
## You may obtain a copy of the License at                                  ##
##                                                                          ##
##     http://www.apache.org/licenses/LICENSE-2.0                           ##
##                                                                          ##
## Unless required by applicable law or agreed to in writing, software      ##
## distributed under the License is distributed on an "AS IS" BASIS,        ##
## WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. ##
## See the License for the specific language governing permissions and      ##
## limitations under the License.                                           ##
## ======================================================================== ##

# Version header
CONFIGURE_FILE(
  ${CMAKE_SOURCE_DIR}/ospray/version.h.in
  ${CMAKE_BINARY_DIR}/${HEADER_DIR}/version.h
  @ONLY
)

INSTALL(FILES ${CMAKE_BINARY_DIR}/${HEADER_DIR}/version.h
  DESTINATION ${HEADER_DIR}
)

# CMake config module
SET(ospray_MODULE_CONFIG_INPUT_DIR  ${CMAKE_SOURCE_DIR}/cmake/ospray_cmake_config)
SET(ospray_MODULE_CONFIG_OUTPUT_DIR ${CMAKE_BINARY_DIR}/cmake)

SET(ospray_MODULE_FILES
  osprayConfig.cmake
  osprayConfigVersion.cmake
  osprayUse.cmake
)

FOREACH(ospray_MODULE_FILENAME ${ospray_MODULE_FILES})

  LIST(APPEND ospray_MODULE_INSTALL_FILES
    ${ospray_MODULE_CONFIG_OUTPUT_DIR}/${ospray_MODULE_FILENAME}
  )

  CONFIGURE_FILE(
    ${ospray_MODULE_CONFIG_INPUT_DIR}/${ospray_MODULE_FILENAME}.in
    ${ospray_MODULE_CONFIG_OUTPUT_DIR}/${ospray_MODULE_FILENAME}
    @ONLY
  )

ENDFOREACH(ospray_MODULE_FILENAME ${ospray_MODULE_FILES})

INSTALL(FILES ${ospray_MODULE_INSTALL_FILES}
  DESTINATION ${CMAKE_DIR}
)