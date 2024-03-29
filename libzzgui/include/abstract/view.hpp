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

#ifndef LIBZZGUI_INCLUDE_INTERFACES_VIEW_HPP_
#define LIBZZGUI_INCLUDE_INTERFACES_VIEW_HPP_

#include "base_view.hpp"

#include <memory>

namespace cozz {

namespace zzgui {

template <class ModelType, class ControllerType>
class View : public BaseView {
  public:
    virtual ~View();

    virtual void SetEventHandler(std::weak_ptr<EventHandler> event_handler) override;

    virtual void SetWindowsManager(std::weak_ptr<WindowsManager> windows_manager) override;

    virtual void SetResourcesManager(std::weak_ptr<ResourcesManager> resources_manager) override;

    virtual void SetBaseModel(std::weak_ptr<BaseModel> model) override;

    virtual void SetBaseController(std::weak_ptr<BaseController> controller) override;

    void SetModel(std::weak_ptr<ModelType> model);

    void SetController(std::weak_ptr<ControllerType> controller);

    virtual std::weak_ptr<EventHandler> GetEventHandler() const override;

    virtual std::weak_ptr<WindowsManager> GetWindowsManager() const override;

    virtual std::weak_ptr<ResourcesManager> GetResourcesManager() const override;

    virtual std::weak_ptr<BaseModel> GetBaseModel() const override;

    virtual std::weak_ptr<BaseController> GetBaseController() const override;

    std::weak_ptr<ModelType> GetModel() const;

    std::weak_ptr<ControllerType> GetController() const;

  protected:
    std::weak_ptr<EventHandler> event_handler_;
    std::weak_ptr<WindowsManager> windows_manager_;
    std::weak_ptr<ResourcesManager> resources_manager_;
    std::weak_ptr<ModelType> model_;
    std::weak_ptr<ControllerType> controller_;

    View(std::weak_ptr<ModelType> model);
};

}  // namespace zzgui

}  // namespace cozz

#include "view.tpp"

#endif  // LIBZZGUI_INCLUDE_INTERFACES_VIEW_HPP_
