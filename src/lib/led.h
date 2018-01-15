#ifndef RTLIB_LIB_LED_H_
#define RTLIB_LIB_LED_H_

#include <cstdint>

#include "config/config.h"
#include "core/gpio.h"

static_assert(LIB_USE_LED > 0, "Led library is disabled in your configuration.");

/**
 * @brief HAL implementation for LEDs.
 *
 * This abstraction layer provides standard state-setting and toggling features for onboard LEDs. One LED object is
 * designed to manage one LED on the mainboard.
 */
class Led {
 public:
  /**
   * @brief Configuration for LED.
   */
  struct Config {
    /**
     * @brief ID of the LED.
     *
     * See your device configuration header file to see which id corresponds to which hardware LED.
     */
    uint8_t id = 0;
    /**
     * @brief If true, LED is assumed to be active low.
     */
    bool polarity = false;
  };

  /**
   * @brief Default constructor for LED.
   *
   * @param config LED configuration
   */
  explicit Led(const Config& config);

  /**
   * @brief Default trivial destructor.
   */
  ~Led() = default;

  /**
   * @brief Move constructor for LED.
   *
   * @param other LED object to move from
   */
  Led(Led&& other) noexcept = default;
  /**
   * @brief Move assignment operator for LED.
   *
   * @param other LED object to move from
   * @return Reference to the moved LED.
   */
  Led& operator=(Led&& other) noexcept = default;

  /**
   * @brief Copy constructor for LED.
   *
   * This constructor is deleted because there should only be one object managing each LED, similar to @c
   * std::unique_ptr.
   */
  Led(const Led&) = delete;
  /**
   * @brief Copy assignment operator for LED.
   *
   * This constructor is deleted because there should only be one object managing each LED, similar to @c
   * std::unique_ptr.
   */
  Led& operator=(const Led&) = delete;

  /**
   * @brief Sets the state of the LED.
   *
   * @note LED will always be in off state after constructor is called. If it isn't, your board may have a pull-up
   * resistor; Set Led#Config#polarity to another value if that is the case.
   *
   * @param flag True if the LED should be on
   */
  void SetEnable(bool flag);
  /**
   * @brief Toggles the state of the LED, i.e. On -> Off, vice versa.
   */
  void Switch();

 protected:
  /**
   * @return GPIO object which manages the pin of the button
   */
  CORE_NS::GPIO* GetGpio() { return &gpio_; }

 private:
  CORE_NS::GPIO gpio_;
  bool polarity_;
};

#endif  // RTLIB_LIB_LED_H_
