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

#include <core/tasks/GetLocalConfigVersion.hpp>
#include "CoreAPI.hpp"
#include "kernel.hpp"
#include "Scheduler.hpp"

using namespace Leosac;

CoreAPI::CoreAPI(Kernel &k) :
    kernel_(k)
{

}

uint64_t CoreAPI::config_version() const
{
    auto t = std::make_shared<Tasks::GetLocalConfigVersion>(kernel_);
    kernel_.core_utils()->scheduler().enqueue(t, TargetThread::MAIN);
    t->wait();
    assert(t->succeed());
    return t->config_version_;
}

uint64_t CoreAPI::uptime() const
{
    using namespace std::chrono;
    uint64_t out;
    auto task = Tasks::GenericTask::build([&] () {
            auto now = steady_clock::now();
            out = duration_cast<seconds>(now - kernel_.start_time()).count();
            return true;
    });
    kernel_.core_utils()->scheduler().enqueue(task, TargetThread::MAIN);
    task->wait();
    assert(task->succeed());

    return out;
}

std::string CoreAPI::instance_name() const
{
    std::string out;
     auto task = Tasks::GenericTask::build([&] () {
             out = kernel_.config_manager().instance_name();
             return true;
    });
    kernel_.core_utils()->scheduler().enqueue(task, TargetThread::MAIN);
    task->wait();
    assert(task->succeed());

    return out;
}
