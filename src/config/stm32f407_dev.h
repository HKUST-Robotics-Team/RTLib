/**
 * @file src/config/stm32f407_dev.h
 *
 * @brief Pin configurations for STM32F407 development board.
 *
 * Taobao Link: https://m.intl.taobao.com/detail/detail.html?id=524181346955
 *
 * Led Configuration:
 * |        Macro       | MCU Pinout | Mainboard Designation | Polarity |
 * | :----------------: | :--------: | :-------------------: | :------: |
 * | @c LIB_LED0_PINOUT |     PA6    |           D2          |  @c true |
 * | @c LIB_LED1_PINOUT |     PA7    |           D3          |  @c true |
 *
 * Button Configuration:
 * |          Macro        | MCU Pinout | Mainboard Designation |   Pull-Up/Pull-Down   |
 * | :-------------------: | :--------: | :-------------------: | :-------------------: |
 * | @c LIB_BUTTON0_PINOUT |     PA0    |          K_UP         |  @c Button::kPullDown |
 * | @c LIB_BUTTON1_PINOUT |     PE4    |           K0          |   @c Button::kPullUp  |
 * | @c LIB_BUTTON2_PINOUT |     PE3    |           K1          |   @c Button::kPullUp  |
 */

#ifndef RTLIB_CONFIG_STM32F407_DEV_H_
#define RTLIB_CONFIG_STM32F407_DEV_H_

#if !defined(STM32F407VET6)
#error "This configuration is designed for a STM32F407VET6 device. (Did you set DEVICE in CMakeLists.txt correctly?)"
#endif  // !defined(STM32F407VET6)

#define LIB_USE_LED 2
#define LIB_LED0_PINOUT {GPIOA, GPIO6}
#define LIB_LED1_PINOUT {GPIOA, GPIO7}

#define LIB_USE_BUTTON 3
#define LIB_BUTTON0_PINOUT {GPIOA, GPIO0}
#define LIB_BUTTON1_PINOUT {GPIOE, GPIO4}
#define LIB_BUTTON2_PINOUT {GPIOE, GPIO3}

#endif  // RTLIB_CONFIG_STM32F407_DEV_H_
