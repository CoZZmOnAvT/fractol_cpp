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

#ifndef FRACTOL_INCLUDE_EVENT_WINDOW_MOVED_EVENT_HPP_
#define FRACTOL_INCLUDE_EVENT_WINDOW_MOVED_EVENT_HPP_

#include "window_event.hpp"

#include <cstdint>
#include <utility>

namespace cozz {

class WindowMovedEvent final : public WindowEvent<Event::Type::kWindowMoved> {
  public:
    WindowMovedEvent(uint32_t window_id, int32_t x, int32_t y);

    std::pair<int32_t, int32_t> GetPosition() const;

  protected:
    int32_t x_;
    int32_t y_;
};

}  // namespace cozz

#endif  // FRACTOL_INCLUDE_EVENT_WINDOW_MOVED_EVENT_HPP_
