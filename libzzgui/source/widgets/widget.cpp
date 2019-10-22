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

#include "widget.hpp"

#include "event/mouse_button_event.hpp"
#include "event/mouse_motion_event.hpp"

namespace cozz {

namespace zzgui {

Widget::Widget(uint64_t x, uint64_t y, uint64_t width, uint64_t height)
    : x_(x), y_(y), padding_left_(5), padding_right_(5), padding_top_(5), padding_bottom_(5) {
    SetSize(width, height);
}

Widget::~Widget() = default;

void Widget::SetPosition(uint64_t x, uint64_t y) {
    x_ = x;
    y_ = y;
}

void Widget::SetSize(uint64_t width, uint64_t height) {
    width_ = width + padding_left_ + padding_right_;
    height_ = height + padding_top_ + padding_bottom_;
}

void Widget::SetPadding(uint64_t padding) { SetPadding(padding, padding); }

void Widget::SetPadding(uint64_t horizontal, uint64_t vertical) {
    SetPadding(horizontal, horizontal, vertical, vertical);
}

void Widget::SetPadding(uint64_t left, uint64_t right, uint64_t top, uint64_t bottom) {
    auto raw_width = width_ - padding_left_ - padding_right_;
    auto raw_height = height_ - padding_top_ - padding_bottom_;

    padding_left_ = left;
    padding_right_ = right;
    padding_top_ = top;
    padding_bottom_ = bottom;

    SetSize(raw_width, raw_height);
}

std::pair<uint64_t, uint64_t> Widget::GetPosition() const { return std::make_pair(x_, y_); }

std::pair<uint64_t, uint64_t> Widget::GetSize() const { return std::make_pair(width_, height_); }

std::tuple<uint64_t, uint64_t, uint64_t, uint64_t> Widget::GetPadding() const {
    return std::make_tuple(padding_left_, padding_right_, padding_top_, padding_bottom_);
}

void Widget::OnMouseMotion(const MouseMotionEvent& event) {
    auto mouse_position = event.GetPosition();

    if (InBounds(mouse_position.first, mouse_position.second)) {
        hover_ = true;
    } else {
        hover_ = false;
    }
}

void Widget::OnMouseButton(const MouseButtonEvent& event) {
    if (!event.IsPressed()) {
        if (!button_queue_.empty()) {
            this->DoOnMouseButton(event);
            button_queue_.pop_front();
            if (event.GetButton() == KeyMap::kLeftMouseButton && click_callback_) {
                click_callback_(event);
            }
        }
    } else {
        auto mouse_position = event.GetPosition();

        if (InBounds(mouse_position.first, mouse_position.second)) {
            DoOnMouseButton(event);
            button_queue_.emplace_back(event.GetButton());
        }
    }
}

void Widget::OnClick(std::function<void(const MouseButtonEvent&)> func) { click_callback_ = func; }

bool Widget::InBounds(uint64_t x, uint64_t y) {
    if (x >= x_ && x <= x_ + width_ && y >= y_ && y <= y_ + height_) {
        return true;
    }
    return false;
}

}  // namespace zzgui

}  // namespace cozz