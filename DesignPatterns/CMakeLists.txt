cmake_minimum_required(VERSION 3.6)
project(DesignPatterns)

set(CMAKE_CXX_STANDARD 11)

INCLUDE_DIRECTORIES(/Users/liuguiyang/Documents/CodeProj/ConsoleProj/DesignPatterns/include)

set(SOURCE_FILES
#    mains/EquityFXMain.cpp
#    mains/PayFactoryMain.cpp
#    mains/RandomMain1.cpp
#    mains/RandomMain2.cpp
#    mains/RandomMain3.cpp
#    mains/SimpleMCMain1.cpp
#    mains/SimpleMCMain2.cpp
#    mains/SimpleMCMain3.cpp
    mains/SimpleMCMain4.cpp
#    mains/SimpleMCMain5.cpp
#    mains/SolveMain1.cpp
#    mains/SolveMain2.cpp
#    mains/StatsMain1.cpp
#    mains/StatsMain2.cpp
#    mains/TreeMain.cpp
#    mains/VanillaMain1.cpp
#    mains/VanillaMain2.cpp
#    mains/VanillaMain3.cpp
#    mains/VanillaMain4.cpp
    source/AntiThetic.cpp
    source/Arrays.cpp
    source/BinomialTree.cpp
    source/BlackScholesFormulas.cpp
    source/BSCallClass.cpp
    source/BSCallTwo.cpp
    source/ConvergenceTable.cpp
    source/DoubleDigital.cpp
#    source/DoubleDigital2.cpp
    source/ExoticBSEngine.cpp
    source/ExoticEngine.cpp
    source/MCStatistics.cpp
    source/Normals.cpp
    source/Parameters.cpp
    source/ParkMiller.cpp
    source/PathDependent.cpp
    source/PathDependentAsian.cpp
    source/PayOff1.cpp
    source/PayOff2.cpp
#    source/PayOff3.cpp
    source/PayOffBridge.cpp
    source/PayOffFactory.cpp
    source/PayOffForward.cpp
    source/PayOffRegistration.cpp
    source/Random1.cpp
    source/Random2.cpp
    source/Random3.cpp
#    source/SimpleMC.cpp
    source/SimpleMC2.cpp
#    source/SimpleMC3.cpp
#    source/SimpleMC4.cpp
    source/SimpleMC5.cpp
    source/SimpleMC6.cpp
    source/SimpleMC7.cpp
    source/SimpleMC8.cpp
    source/TreeAmerican.cpp
    source/TreeEuropean.cpp
    source/TreeProducts.cpp
#    source/Vanilla1.cpp
#    source/Vanilla2.cpp
    source/Vanilla3.cpp
        )

add_executable(DesignPatterns ${SOURCE_FILES})