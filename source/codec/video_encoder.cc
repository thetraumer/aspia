//
// Aspia Project
// Copyright (C) 2018 Dmitry Chapyshev <dmitry@aspia.ru>
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

#include "codec/video_encoder.h"

#include "desktop_capture/desktop_frame.h"

namespace aspia {

void VideoEncoder::fillPacketInfo(proto::desktop::VideoEncoding encoding,
                                  const DesktopFrame* frame,
                                  proto::desktop::VideoPacket* packet)
{
    packet->set_encoding(encoding);

    QRect rect(frame->topLeft(), frame->size());

    if (screen_rect_ != rect)
    {
        screen_rect_ = rect;

        proto::desktop::Rect* rect = packet->mutable_format()->mutable_screen_rect();

        rect->set_x(screen_rect_.x());
        rect->set_y(screen_rect_.y());
        rect->set_width(screen_rect_.width());
        rect->set_height(screen_rect_.height());
    }
}

} // namespace aspia