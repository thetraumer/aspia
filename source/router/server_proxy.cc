//
// Aspia Project
// Copyright (C) 2020 Dmitry Chapyshev <dmitry@aspia.ru>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.
//

#include "router/server_proxy.h"

#include "base/logging.h"

namespace router {

ServerProxy::ServerProxy(Server* server)
    : server_(server)
{
    DCHECK(server_);
}

ServerProxy::~ServerProxy()
{
    DCHECK(!server_);
}

std::unique_ptr<proto::RelayList> ServerProxy::relayList() const
{
    if (!server_)
        return nullptr;

    return server_->relayList();
}

std::unique_ptr<proto::HostList> ServerProxy::hostList() const
{
    if (!server_)
        return nullptr;

    return server_->hostList();
}

bool ServerProxy::disconnectHost(base::HostId host_id)
{
    if (!server_)
        return false;

    return server_->disconnectHost(host_id);
}

void ServerProxy::onHostSessionWithId(SessionHost* session)
{
    if (!server_)
        return;

    server_->onHostSessionWithId(session);
}

void ServerProxy::willDestroyCurrentServer()
{
    server_ = nullptr;
}

} // namespace router
