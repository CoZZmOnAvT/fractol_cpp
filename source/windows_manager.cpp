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

#include "windows_manager.hpp"

namespace cozz {

WindowsManager::WindowsManager(std::shared_ptr<EventHandler> event_handler) : event_handler_(event_handler) {
    event_handler_->RegisterEventCallback<WindowCloseEvent>(std::bind(&WindowsManager::OnWindowClose, this, std::placeholders::_1));
}

void WindowsManager::OnWindowClose(const WindowCloseEvent& event) {
    auto it = windows_.find(event.GetWindowId());
    if (it != windows_.end()) {
        event_handler_->UnregisterEventCallbacks(it->second.second);
        windows_.erase(event.GetWindowId());
    }
}

void WindowsManager::UpdateWindows() const {
    std::for_each(windows_.begin(), windows_.end(), [](const auto& window) {  window.second.first->Update(); });
}

}  // namespace cozz