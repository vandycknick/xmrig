/* XMRig
 * Copyright (c) 2018-2021 SChernykh   <https://github.com/SChernykh>
 * Copyright (c) 2016-2021 XMRig       <https://github.com/xmrig>, <support@xmrig.com>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "App.h"
#include "base/kernel/Entry.h"
#include "base/kernel/Process.h"

using namespace xmrig;
static App *app;

extern "C" int xmrig_start(int argc, char **argv)
{
    Process process(argc, argv);
    const Entry::Id entry = Entry::get(process);
    if (entry)
    {
        return Entry::exec(process, entry);
    }

    // App app(&process);
    app = new App(&process);

    app->exec();
    return 0;
}

extern "C" int xmrig_stop()
{

    if (app == nullptr)
        return 0;

    app->close();
    return 0;
}
