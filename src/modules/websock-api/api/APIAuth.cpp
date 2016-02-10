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

#include <algorithm>
#include "APIAuth.hpp"
#include "tools/GenGuid.h"

using namespace Leosac;
using namespace Leosac::Module;
using namespace Leosac::Module::WebSockAPI;

std::string APIAuth::generate_token(const std::string &username, const std::string &password)
{
    if (username == "admin" && password == "admin")
    {
        auto token = gen_uuid();
        tokens_[token] = username;
        return token;
    }
    return "";
}

bool APIAuth::authenticate(const std::string &token, std::string &user_id) const
{
    auto it = tokens_.find(token);
    if (it != tokens_.end())
    {
        user_id = it->second;
        return true;
    }
    return false;
}
