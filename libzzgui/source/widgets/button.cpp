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

#include "widgets/button.hpp"

#include "event/mouse_button_event.hpp"
#include "key_map.hpp"
#include "painter.hpp"
#include "resources/font_resource.hpp"

namespace cozz {

namespace zzgui {

Button::Button(const std::string& text, std::shared_ptr<FontResource> font, int64_t x, int64_t y)
    : Label(text, font, x, y) {
    SetBackgroundColor({0xFF, 0xFF, 0xFF});
    SetBorderColor({0, 0, 0});
    SetForegroundColor({0, 0, 0});
}

void Button::Draw(std::shared_ptr<Painter> painter, std::shared_ptr<Canvas> canvas) { Label::Draw(painter, canvas); }

bool Button::DoOnMouseButton(const MouseButtonEvent& event) {
    if (event.GetButton() == KeyMap::kLeftMouseButton) {
        if (event.IsPressed()) {
            y_ += 2;
        } else {
            y_ -= 2;
        }
        return true;
    }
    return false;
}

}  // namespace zzgui

}  // namespace cozz
