/*
 * This file is part of Fractol.

 * Fractol is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Fractol is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Fractol. If not, see <https://www.gnu.org/licenses/>.
 *
 * Author: Pavlo Hrytsenko
*/

#include "fractol.hpp"

#include <functional>
#include <iostream>

#include "sdl_event_handler.hpp"

namespace cozz {

Fractol::Fractol(int argc, char** argv) : is_running_(true), event_handler_(std::make_unique<SDLEventHandler>()) {
    event_handler_->RegisterEventCallback<QuitEvent>(std::bind(&Fractol::Terminate, this, std::placeholders::_1));
}

Fractol::~Fractol() = default;

void Fractol::Terminate(const QuitEvent& event) {
    std::cout << "Application is terminating" << std::endl;
    is_running_ = false;
}

uint8_t Fractol::Run() {
    while (is_running_) {
        event_handler_->Poll();
    }
}

}  // namespace cozz
