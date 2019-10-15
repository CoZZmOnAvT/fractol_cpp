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

#ifndef LIBZZGUI_INCLUDE_INTERFACES_CONTROLLER_HPP_
#define LIBZZGUI_INCLUDE_INTERFACES_CONTROLLER_HPP_

#include <memory>

namespace cozz {

namespace zzgui {

class EventHandler;
class Model;
class View;

class Controller {
  public:
    Controller() = delete;

    virtual ~Controller();

    void Render(float delta);

    void Pause();

    void Resume();

    void Resize(uint64_t width, uint64_t height);

    void SetModelAndView(std::weak_ptr<Model> model, std::weak_ptr<View> view);

    std::weak_ptr<EventHandler> GetEventHandler() const;

    std::weak_ptr<Model> GetModel() const;

    std::weak_ptr<View> GetView() const;

  protected:
    std::weak_ptr<EventHandler> event_handler_;
    std::weak_ptr<Model> model_;
    std::weak_ptr<View> view_;

    Controller(std::weak_ptr<EventHandler> event_handler, std::weak_ptr<Model> model, std::weak_ptr<View> view);
};

}  // namespace zzgui

}  // namespace cozz

#endif  // LIBZZGUI_INCLUDE_INTERFACES_CONTROLLER_HPP_
