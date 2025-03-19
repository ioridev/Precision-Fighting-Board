cmake_minimum_required(VERSION 3.14)

# STM32 CMake toolchain
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/stm32_gcc.cmake)

# プロジェクト名および言語設定
project(stm32h7_pfb C ASM)

# ターゲットマイコン設定
set(STM32_FAMILY H7)
set(STM32_CHIP STM32H743xx)

# ソースファイル
set(SOURCES
    Src/main.c
    Src/button.c
    Src/xinput.c
    Src/usb_descriptors.c
    Src/usb_xinput_device.c
    # TinyUSB関連のソースファイル
    ${CMAKE_CURRENT_SOURCE_DIR}/tinyusb/src/tusb.c
    ${CMAKE_CURRENT_SOURCE_DIR}/tinyusb/src/common/tusb_fifo.c
    ${CMAKE_CURRENT_SOURCE_DIR}/tinyusb/src/device/usbd.c
    ${CMAKE_CURRENT_SOURCE_DIR}/tinyusb/src/device/usbd_control.c
    ${CMAKE_CURRENT_SOURCE_DIR}/tinyusb/src/class/vendor/vendor_device.c
    ${CMAKE_CURRENT_SOURCE_DIR}/tinyusb/src/portable/synopsys/dwc2/dcd_dwc2.c
    # HAL関連のソース
)

# インクルードディレクトリ
set(INCLUDES
    Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/tinyusb/src
    Drivers/CMSIS/Include
    Drivers/CMSIS/Device/ST/STM32H7xx/Include
    Drivers/STM32H7xx_HAL_Driver/Inc
)

# 実行ファイル作成
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDES})

# コンパイルオプション
target_compile_definitions(${PROJECT_NAME} PRIVATE
    -DUSE_HAL_DRIVER
    -D${STM32_CHIP}
    -DCFG_TUSB_MCU=OPT_MCU_STM32H7
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -mcpu=cortex-m7
    -mfpu=fpv5-d16
    -mfloat-abi=hard
    -mthumb
    -Wall
    -Wextra
    -Wno-unused-parameter
    -Og
    -g3
    -ffunction-sections
    -fdata-sections
)

# リンカーオプション
target_link_options(${PROJECT_NAME} PRIVATE
    -mcpu=cortex-m7
    -mfpu=fpv5-d16
    -mfloat-abi=hard
    -mthumb
    -T${CMAKE_CURRENT_SOURCE_DIR}/STM32H743VITX_FLASH.ld
    -Wl,-Map=${PROJECT_NAME}.map
    -Wl,--gc-sections
    -static
    -Wl,--start-group
    -lc
    -lm
    -Wl,--end-group
)

# TinyUSBをダウンロード
include(ExternalProject)
ExternalProject_Add(
    tinyusb
    GIT_REPOSITORY https://github.com/hathach/tinyusb.git
    GIT_TAG master
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    TEST_COMMAND ""
)

# ビルド後の処理：バイナリ変換
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${PROJECT_NAME} ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME} ${PROJECT_NAME}.bin
) 