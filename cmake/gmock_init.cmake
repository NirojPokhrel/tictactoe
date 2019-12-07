set (GTEST_SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/googletest/lib)
set (GTEST_STATIC_LIBRARIES
      ${GTEST_SOURCE_DIR}/libgmock_main.a
      ${GTEST_SOURCE_DIR}/libgmock.a
      ${GTEST_SOURCE_DIR}/libgtest_main.a
      ${GTEST_SOURCE_DIR}/libgtest.a)

find_library (GTEST_LIBRARY
  NAMES   libgmock.a
  HINTS   "${GTEST_SOURCE_DIR}"
)

function(gtestinit)
  include (${CMAKE_SOURCE_DIR}/cmake/gmock_download.cmake)
endfunction()

if (GTEST_LIBRARY)
  message(STATUS "GTest library - ${GTEST_LIBRARY}")
  # Check if the local copy of the library exists
  foreach(lib ${GTEST_STATIC_LIBRARIES})
    if (EXISTS ${lib})
      message(STATUS "Gtest Found - ${lib}")
    else ()
      message (STATUS "Gtest Not Found")
      gtestinit()
      break()
    endif ()
  endforeach(lib ${})
else ()
  gtestinit()
endif ()

set(GTEST_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/external/googletest/googletest/include)
set(GMOCK_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/external/googletest/googlemock/include)