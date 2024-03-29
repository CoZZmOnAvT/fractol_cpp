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

#include "event/keyboard_event.hpp"

namespace cozz {

namespace zzgui {

KeyboardEvent::KeyboardEvent(Window::ID window_id, bool pressed, bool is_repeat, KeyMap key)
    : Event(Event::Type::kKeyboard, window_id),
      pressed_(pressed),
      is_repeat_(is_repeat),
      key_(key > KeyMap::kKeyboardButtonsBegin && key < KeyMap::kKeyboardButtonsEnd
               ? key
               : throw event_error("Invalid keyboard button")) {}

bool KeyboardEvent::IsPressed() const { return pressed_; }

bool KeyboardEvent::IsRepeat() const { return is_repeat_; }

KeyMap KeyboardEvent::GetKey() const { return key_; }

}  // namespace zzgui

}  // namespace cozz
