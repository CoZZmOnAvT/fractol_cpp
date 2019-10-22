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

#include "widgets/image.hpp"

#include "event/mouse_button_event.hpp"
#include "painter.hpp"
#include "resources/image_resource.hpp"

namespace cozz {

namespace zzgui {

Image::Image(std::shared_ptr<ImageResource> img, uint64_t x, uint64_t y) : Widget(x, y, 0, 0), img_(img) {
    if (!img_) {
        throw std::runtime_error("Bad image");
    }
    SetPadding(0);
    auto img_size = img_->GetSize();
    SetSize(img_size.first, img_size.second);
}

void Image::Draw(std::shared_ptr<Painter> painter) { painter->DrawImage({x_, y_}, img_, width_, height_); }

void Image::DoOnMouseButton(const MouseButtonEvent&) {}

}  // namespace zzgui

}  // namespace cozz