/*
 * This file is part of RTLib.
 *
 * Copyright (C) 2018 Derppening <david.18.19.21@gmail.com>
 *
 * RTLib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RTLib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with RTLib.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "core/stm32f1/gpio.h"

#if defined(STM32F1)

#include <cassert>
#include <utility>

#include <libopencm3/stm32/rcc.h>

#include "core/assert.h"

namespace rtlib::core::stm32f1 {
GPIO::GPIO(const Config& config) :
    pin_(AssertPin(config.pin, __FILE__, __LINE__, __func__)) {
  // Use external oscillator for RCC
  rcc_clock_setup_in_hse_8mhz_out_72mhz();

  // Initialize the RCC and enable the GPIO
  InitRcc(pin_.first);
  Init(config.cnf, config.mode);
}

GPIO::~GPIO() {
  Release();
}

void GPIO::Init(const Configuration cnf, const Mode mode) const {
  gpio_set_mode(pin_.first, uint8_t(mode), uint8_t(cnf), pin_.second);
}

void GPIO::InitRcc(const Port port) const {
  switch (port) {
    case GPIOA:
      rcc_periph_clock_enable(RCC_GPIOA);
      break;
    case GPIOB:
      rcc_periph_clock_enable(RCC_GPIOB);
      break;
    case GPIOC:
      rcc_periph_clock_enable(RCC_GPIOC);
      break;
    case GPIOD:
      rcc_periph_clock_enable(RCC_GPIOD);
      break;
    case GPIOE:
      rcc_periph_clock_enable(RCC_GPIOE);
      break;
    case GPIOF:
      rcc_periph_clock_enable(RCC_GPIOF);
      break;
    case GPIOG:
      rcc_periph_clock_enable(RCC_GPIOG);
      break;
    default:
      Assert(false, __FILE__, __LINE__, __func__, "Invalid GPIO Port");
      break;
  }
}

bool GPIO::Read() const {
#if defined(RTLIB_ENABLE_VALIDATION)
  Assert(IsBinded(), __FILE__, __LINE__, __func__);
#endif  // defined(RTLIB_ENABLE_VALIDATION)

  return bool(gpio_get(pin_.first, pin_.second));
}

void GPIO::Set(const bool state) const {
#if defined(RTLIB_ENABLE_VALIDATION)
  Assert(IsBinded(), __FILE__, __LINE__, __func__);
#endif  // defined(RTLIB_ENABLE_VALIDATION)

  if (state) {
    gpio_set(pin_.first, pin_.second);
  } else {
    gpio_clear(pin_.first, pin_.second);
  }
}

void GPIO::Toggle() const {
#if defined(RTLIB_ENABLE_VALIDATION)
  Assert(IsBinded(), __FILE__, __LINE__, __func__);
#endif  // defined(RTLIB_ENABLE_VALIDATION)

  gpio_toggle(pin_.first, pin_.second);
}

void GPIO::Release() {
  if (!IsBinded()) {
    return;
  }

  Reset();

  pin_ = kNullPinout;
}

void GPIO::Reset() const {
  if (!IsBinded()) {
    return;
  }

  gpio_set_mode(pin_.first, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, pin_.second);
}

void GPIO::SetPriAltFn(JTAGDisables swj_state, AltFnMaps maps) {
  gpio_primary_remap(uint32_t(swj_state), maps);
}

void GPIO::SetSecAltFn(AltFnMaps maps) {
  gpio_secondary_remap(maps);
}

}  // namespace rtlib::core::stm32f1

#endif  // defined(STM32F1)
