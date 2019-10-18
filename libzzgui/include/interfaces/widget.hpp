/*
 * This file is part of LibZZgui.

 * LibZZgui is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LibZZgui is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LibZZgui. If not, see <https://www.gnu.org/licenses/>.
 *
 * Author: Pavlo Hrytsenko
*/

#ifndef LIBZZGUI_INCLUDE_INTERFACES_WIDGET_HPP_
#define LIBZZGUI_INCLUDE_INTERFACES_WIDGET_HPP_

#include <cstdint>
#include <memory>
#include <utility>

namespace cozz {

namespace zzgui {

class Painter;

class Widget {
  public:
    virtual ~Widget();

    virtual void Draw(std::shared_ptr<Painter> painter) = 0;

    void SetPosition(uint64_t x, uint64_t y);

    void SetSize(uint64_t width, uint64_t height);

    std::pair<uint64_t, uint64_t> GetPosition() const;

    std::pair<uint64_t, uint64_t> GetSize() const;

  protected:
    uint64_t x_;
    uint64_t y_;

    uint64_t width_;
    uint64_t height_;

    Widget(uint64_t x, uint64_t y, uint64_t width, uint64_t height);
};

}  // namespace zzgui

}  // namespace cozz

#endif  // LIBZZGUI_INCLUDE_INTERFACES_WIDGET_HPP_
