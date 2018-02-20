cmake_minimum_required(VERSION 3.8)
project(card_anki)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Modal/card.cpp Modal/card.h Service/studyService.cpp Service/studyService.h Service/saveLoad.cpp Service/saveLoad.h config.h)
add_executable(card_anki ${SOURCE_FILES})