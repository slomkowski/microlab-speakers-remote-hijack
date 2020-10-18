cmake_minimum_required(VERSION 3.5)
SET(CMAKE_SYSTEM_NAME Generic)

project(microlab-speaker-remote-hijack)

SET(DEVICE "attiny85")
SET(FREQ "16000000")

SET(CMAKE_C_COMPILER avr-gcc)
SET(CMAKE_CXX_COMPILER avr-g++)

SET(CMAKE_C_FLAGS "-Os -mmcu=${DEVICE} -DF_CPU=${FREQ}UL -std=c11 -Wl,--gc-sections -Wall -Wextra -pedantic")
SET(CMAKE_CXX_FLAGS "-Os -mmcu=${DEVICE} -DF_CPU=${FREQ}UL -std=c++17 -Wl,--gc-sections -Wall -Wextra -pedantic -fno-exceptions -fno-rtti")

SET(SOURCES src/main.cpp)

ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCES})

ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD COMMAND avr-objcopy -O ihex -R.eeprom ${CMAKE_BINARY_DIR}/${PROJECT_NAME} ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.hex)
ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD COMMAND avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 ${CMAKE_BINARY_DIR}/${PROJECT_NAME} ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.eep)
ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD COMMAND avr-size ${CMAKE_BINARY_DIR}/${PROJECT_NAME} --mcu=${DEVICE} --format=avr)
