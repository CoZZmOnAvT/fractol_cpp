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

#include "models/menu.hpp"

#include "controller.tpp"
#include "view.tpp"
#include "controllers/menu.hpp"
#include "controllers_manager.hpp"
#include "views/menu.hpp"

namespace cozz {

MenuController::MenuController() : Controller(std::make_shared<MenuView>(std::make_shared<MenuModel>())) {}

MenuController::~MenuController() = default;

void MenuController::Create() {}

void MenuController::OnWindowClose(const zzgui::WindowCloseEvent&) {
    controllers_manager_.lock()->Erase(shared_from_this());
}

void MenuController::OnMandelbrotFractalButtonClick(const zzgui::MouseButtonEvent&) const {
    controllers_manager_.lock()->Push(std::make_shared<MenuController>());
}

void MenuController::OnExitButtonClick(const zzgui::MouseButtonEvent&) const {
    event_handler_.lock()->PushEvent(zzgui::QuitEvent());
}

}  // namespace cozz
