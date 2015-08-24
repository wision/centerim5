/*
 * Copyright (C) 2007 Mark Pustjens <pustjens@dds.nl>
 * Copyright (C) 2010-2015 Petr Pavlu <setup@dagobah.cz>
 *
 * This file is part of CenterIM.
 *
 * CenterIM is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * CenterIM is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/**
 * @file
 * Panel class implementation.
 *
 * @ingroup cppconsui
 */

#include "Panel.h"

#include "ColorScheme.h"

#include <algorithm>
#include <cstring>

namespace CppConsUI {

Panel::Panel(int w, int h, const char *text)
  : Widget(w, h), title(NULL), title_width(0)
{
  setTitle(text);
}

Panel::~Panel()
{
  delete[] title;
}

int Panel::draw(Curses::ViewPort area, Error &error)
{
  int attrs, i;

  // Calculate title width.
  int draw_title_width = 0;
  if (real_width > 4)
    draw_title_width = real_width - 4;
  draw_title_width = std::min(draw_title_width, title_width);

  // Calculate horizontal line length (one segment width).
  int hline_len = 0;
  int extra = draw_title_width ? 4 : 2;
  if (real_width > draw_title_width + extra)
    hline_len = (real_width - draw_title_width - extra) / 2;

  if (draw_title_width) {
    // Draw title.
    DRAW(getAttributes(ColorScheme::PANEL_TITLE, &attrs, error));
    DRAW(area.attrOn(attrs, error));
    DRAW(area.addString(2 + hline_len, 0, draw_title_width, title, error));
    DRAW(area.attrOff(attrs, error));
  }

  // Draw lines.
  DRAW(getAttributes(ColorScheme::PANEL_LINE, &attrs, error));
  DRAW(area.attrOn(attrs, error));

  // Draw top horizontal line.
  for (i = 1; i < 1 + hline_len; ++i)
    DRAW(area.addLineChar(i, 0, Curses::LINE_HLINE, error));
  for (i = 1 + hline_len + extra - 2 + draw_title_width; i < real_width - 1;
       ++i)
    DRAW(area.addLineChar(i, 0, Curses::LINE_HLINE, error));

  // Draw bottom horizontal line.
  for (i = 1; i < real_width - 1; ++i)
    DRAW(area.addLineChar(i, real_height - 1, Curses::LINE_HLINE, error));

  // Draw left and right vertical line.
  for (i = 1; i < real_height - 1; ++i)
    DRAW(area.addLineChar(0, i, Curses::LINE_VLINE, error));
  for (i = 1; i < real_height - 1; ++i)
    DRAW(area.addLineChar(real_width - 1, i, Curses::LINE_VLINE, error));

  // Draw corners.
  DRAW(area.addLineChar(0, 0, Curses::LINE_ULCORNER, error));
  DRAW(area.addLineChar(real_width - 1, 0, Curses::LINE_URCORNER, error));
  DRAW(area.addLineChar(0, real_height - 1, Curses::LINE_LLCORNER, error));
  DRAW(area.addLineChar(
    real_width - 1, real_height - 1, Curses::LINE_LRCORNER, error));

  DRAW(area.attrOff(attrs, error));

  return 0;
}

void Panel::setTitle(const char *new_title)
{
  delete[] title;

  size_t size = 1;
  if (new_title)
    size += std::strlen(new_title);
  title = new char[size];
  if (new_title)
    std::strcpy(title, new_title);
  else
    title[0] = '\0';
  title_width = Curses::onScreenWidth(title);

  redraw();
}

} // namespace CppConsUI

/* vim: set tabstop=2 shiftwidth=2 textwidth=80 expandtab : */
