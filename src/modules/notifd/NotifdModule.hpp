/*
    Copyright (C) 2014-2016 Islog

    This file is part of Leosac.

    Leosac is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Leosac is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "modules/BaseModule.hpp"
#include <boost/asio/io_service.hpp>
#include <boost/fiber/all.hpp>

namespace Leosac
{
namespace Module
{
namespace Notifd
{

class NotifdModule : public BaseModule
{
  public:
    NotifdModule(zmqpp::context &ctx, zmqpp::socket *pipe,
                 const boost::property_tree::ptree &cfg, CoreUtilsPtr utils);

    ~NotifdModule();

    virtual void run() override;

  private:
    /**
     * Install a fiber that will watch for the STOP signal from
     * Leosac's Kernel.
     */
    void install_stop_watcher();

    std::shared_ptr<boost::asio::io_service> io_service_;
};
}
}
}
