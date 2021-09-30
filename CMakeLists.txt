cmake_minimum_required(VERSION 3.16)

project(
        matrix-simple
        DESCRIPTION "Schönherz Mátrix super module"
        HOMEPAGE_URL "kszk.bme.hu"
        LANGUAGES CXX)

add_compile_definitions(QT_DISABLE_DEPRECATED_BEFORE=0x050F00)
add_subdirectory(libmueb-new)
add_subdirectory(emu)
add_subdirectory(matrixsource)
add_subdirectory(animsource)
add_subdirectory(colorsource)
add_subdirectory(drawsource)
add_subdirectory(percentsource)
add_subdirectory(windowtestsource)
add_subdirectory(q4x-extractor)
#add_subdirectory(screensaver)
#add_subdirectory(player)
