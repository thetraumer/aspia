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

#include "base/codec/video_util.h"

namespace base {

Rect parseRect(const proto::Rect& rect)
{
    return Rect::makeXYWH(rect.x(), rect.y(), rect.width(), rect.height());
}

void serializeRect(const Rect& from, proto::Rect* to)
{
    to->set_x(from.x());
    to->set_y(from.y());
    to->set_width(from.width());
    to->set_height(from.height());
}

PixelFormat parsePixelFormat(const proto::PixelFormat& format)
{
    return PixelFormat(
        static_cast<uint8_t>(format.bits_per_pixel()),
        static_cast<uint16_t>(format.red_max()),
        static_cast<uint16_t>(format.green_max()),
        static_cast<uint16_t>(format.blue_max()),
        static_cast<uint8_t>(format.red_shift()),
        static_cast<uint8_t>(format.green_shift()),
        static_cast<uint8_t>(format.blue_shift()));
}

void serializePixelFormat(const PixelFormat& from, proto::PixelFormat* to)
{
    to->set_bits_per_pixel(from.bitsPerPixel());

    to->set_red_max(from.redMax());
    to->set_green_max(from.greenMax());
    to->set_blue_max(from.blueMax());

    to->set_red_shift(from.redShift());
    to->set_green_shift(from.greenShift());
    to->set_blue_shift(from.blueShift());
}

} // namespace base
