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

#ifndef ROUTER__SERVER_PROXY_H
#define ROUTER__SERVER_PROXY_H

#include "router/server.h"

namespace router {

class ServerProxy
{
public:
    ~ServerProxy();

    std::unique_ptr<proto::RelayList> relayList() const;
    std::unique_ptr<proto::HostList> hostList() const;

    bool disconnectHost(base::HostId host_id);
    void onHostSessionWithId(SessionHost* session);

private:
    friend class Server;
    explicit ServerProxy(Server* server);

    void willDestroyCurrentServer(); // Called by ~Server().

    Server* server_;
};

} // namespace router

#endif // ROUTER__SERVER_PROXY_H
