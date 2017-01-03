# Install script for directory: /Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "runtime" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/cmake-build-debug/libbgs.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libbgs.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libbgs.dylib")
    execute_process(COMMAND "/usr/bin/install_name_tool"
      -id "libbgs.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libbgs.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/usr/local/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libbgs.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libbgs.dylib")
    endif()
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/package_bgs" TYPE FILE FILES
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/AdaptiveBackgroundLearning.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/AdaptiveSelectiveBackgroundLearning.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/FrameDifferenceBGS.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/IBGS.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/MixtureOfGaussianV1BGS.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/MixtureOfGaussianV2BGS.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/StaticFrameDifferenceBGS.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/WeightedMovingMeanBGS.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/WeightedMovingVarianceBGS.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/ae/KDE.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/ae/KernelTable.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/ae/NPBGSubtractor.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/ae/NPBGmodel.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/av/TBackground.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/av/TBackgroundVuMeter.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/av/VuMeter.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/bl/SigmaDeltaBGS.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/bl/sdLaMa091.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/bl/stdbool.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/ck/LbpMrf.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/ck/block.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/ck/graph.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/db/IndependentMultimodalBGS.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/dp/AdaptiveMedianBGS.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/dp/Bgs.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/dp/BgsParams.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/dp/DPAdaptiveMedianBGS.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/dp/DPEigenbackgroundBGS.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/dp/DPGrimsonGMMBGS.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/dp/DPMeanBGS.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/dp/DPPratiMediodBGS.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/dp/DPTextureBGS.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/dp/DPWrenGABGS.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/dp/DPZivkovicAGMMBGS.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/dp/Eigenbackground.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/dp/Error.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/dp/GrimsonGMM.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/dp/Image.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/dp/MeanBGS.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/dp/PratiMediodBGS.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/dp/TextureBGS.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/dp/WrenGA.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/dp/ZivkovicAGMM.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/lb/BGModel.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/lb/BGModelFuzzyGauss.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/lb/BGModelFuzzySom.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/lb/BGModelGauss.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/lb/BGModelMog.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/lb/BGModelSom.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/lb/LBAdaptiveSOM.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/lb/LBFuzzyAdaptiveSOM.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/lb/LBFuzzyGaussian.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/lb/LBMixtureOfGaussians.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/lb/LBSimpleGaussian.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/lb/Types.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/my/MyBGS.h"
    "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/package_bgs/sjn/SJN_MultiCueBGS.h"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "app" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/cmake-build-debug/bgs")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/bgs" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/bgs")
    execute_process(COMMAND "/usr/bin/install_name_tool"
      -change "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/cmake-build-debug/libbgs.dylib" "libbgs.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/bgs")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/usr/local/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/bgs")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/bgs")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/liuguiyang/Documents/CodeProj/ConsoleProj/bgslibrary/cmake-build-debug/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
