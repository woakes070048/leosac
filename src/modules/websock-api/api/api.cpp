/*
    Copyright (C) 2014-2015 Islog

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

#include "tools/leosac.hpp"
#include "api.hpp"
#include "../WSServer.hpp"

using namespace Leosac;
using namespace Leosac::Module;
using namespace Leosac::Module::WebSockAPI;

API::API(WSServer &server) :
    server_(server)
{

}

API::json API::get_leosac_version() const
{
    json ret;
    ret["version"] = getVersionString();
    return ret;
}

API::json API::create_auth_token(const API::json &req)
{
    json rep;
    std::string username = req.at("username");
    std::string password = req.at("password");

    auto token = server_.auth().generate_token(username, password);
    if (!token.empty())
    {
        rep["status"] = 0;
        rep["token"] = token;
    }
    else
    {
        rep["status"] = -1;
    }
    return rep;
}