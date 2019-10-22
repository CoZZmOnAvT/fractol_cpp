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

#ifndef LIBZZGUI_INCLUDE_INTERFACES_BASE_CONTROLLER_HPP_
#define LIBZZGUI_INCLUDE_INTERFACES_BASE_CONTROLLER_HPP_

#include <memory>

namespace cozz {

namespace zzgui {

class Window;
class ControllersManager;
class EventHandler;
class WindowsManager;
class ResourcesManager;
class BaseModel;
class BaseView;

class BaseController {
  public:
    virtual ~BaseController() = default;

    virtual void Create() = 0;

    virtual void Render(float delta) = 0;

    virtual void Pause() = 0;

    virtual void Resume() = 0;

    virtual void Resized(std::weak_ptr<Window> window) = 0;

    virtual void SetControllersManager(std::weak_ptr<ControllersManager> controllers_manager) = 0;

    virtual void SetEventHandler(std::weak_ptr<EventHandler> event_handler) = 0;

    virtual void SetWindowsManager(std::weak_ptr<WindowsManager> windows_manager) = 0;

    virtual void SetResourcesManager(std::weak_ptr<ResourcesManager> resources_manager) = 0;

    virtual void SetBaseModel(std::shared_ptr<BaseModel> model) = 0;

    virtual void SetBaseView(std::shared_ptr<BaseView> controller) = 0;

    virtual std::weak_ptr<ControllersManager> GetControllersManager() const = 0;

    virtual std::weak_ptr<EventHandler> GetEventHandler() const = 0;

    virtual std::weak_ptr<WindowsManager> GetWindowsManager() const = 0;

    virtual std::weak_ptr<ResourcesManager> GetResourcesManager() const = 0;

    virtual std::weak_ptr<BaseModel> GetBaseModel() const = 0;

    virtual std::weak_ptr<BaseView> GetBaseView() const = 0;
};

}  // namespace zzgui

}  // namespace cozz

#endif  // LIBZZGUI_INCLUDE_INTERFACES_BASE_CONTROLLER_HPP_
