/*
 * Copyright (C) 2012-2013 by CenterIM developers
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
 * */

/**
 * @file
 * ColorPickerPalette class implementation.
 *
 * @ingroup cppconsui
 */

#include "ColorPickerPalette.h"

#include "ColorScheme.h"

#define GRAYSCALE_START 232
#define GRAYSCALE_END 255

namespace CppConsUI
{

ColorPickerPalette::ColorPickerPalette(int defaultcolor, int flags)
: Container(0, 0)
{
  if (flags == (FLAG_HIDE_ANSI | FLAG_HIDE_GRAYSCALE | FLAG_HIDE_COLORCUBE)) {
    // show at least ANSI colors
    flags = FLAG_HIDE_GRAYSCALE | FLAG_HIDE_COLORCUBE;
  }

  if (Curses::nrcolors() < 256)
    flags |= (FLAG_HIDE_GRAYSCALE | FLAG_HIDE_COLORCUBE);

  if (!(flags & FLAG_HIDE_ANSI))
    // default 16 colors
    addAnsi(defaultcolor);

  if (!(flags & FLAG_HIDE_GRAYSCALE))
    // grayscale ladder
    addGrayscale(defaultcolor);

  if (!(flags & FLAG_HIDE_COLORCUBE))
    // 6x6x6 color cube
    addColorCube(defaultcolor);
}

void ColorPickerPalette::onSelectColor(Button& activator)
{
  ColorPickerPaletteButton *button =
    dynamic_cast<ColorPickerPaletteButton*>(&activator);
  g_assert(button);

  signal_color_selected(*this, button->color);
}

void ColorPickerPalette::addButton(int x, int y, int color, int defaultcolor)
{
  ColorPickerPaletteButton *button = new ColorPickerPaletteButton(color);
  button->signal_activate.connect(sigc::mem_fun(this,
        &ColorPickerPalette::onSelectColor));
  addWidget(*button, x, y);

  if (color == defaultcolor)
    button->grabFocus();
}

void ColorPickerPalette::addAnsi(int defaultcolor)
{
  int w, h, x, y;

  // resize the ColorPickerPalette
  w = getWidth();
  h = y = getHeight();

  // there are 8 ANSI colors, or 16 when bright colors are supported
  w = MAX(w, Curses::NUM_DEFAULT_COLORS);
  h += 2;

  resize(w, h);

  // add the color picker buttons, in two lines
  // @todo Support terms with only 8 colors.
  int half = Curses::NUM_DEFAULT_COLORS / 2;
  for (x = 0; x < Curses::NUM_DEFAULT_COLORS; x++)
    if (x < half) {
      // the first line
      addButton(x * 2, y, x, defaultcolor);
    }
    else {
      // the second line
      addButton((x - half) * 2, y + 1, x, defaultcolor);
    }
}

void ColorPickerPalette::addGrayscale(int defaultcolor)
{
  int w, h, x, y, color;

  // resize the ColorPickerPalette
  w = getWidth();
  h = getHeight();

  // add space between this and previous section
  if (h)
    h++;

  y = h;
  w = MAX(w, (GRAYSCALE_END - GRAYSCALE_START + 1) * 2);
  h = h + 1;

  resize(w, h);

  // add the color picker buttons
  for (color = GRAYSCALE_START, x = 0; color <= GRAYSCALE_END;
      color++, x += 2)
    addButton(x, y, color, defaultcolor);

  addButton(x, y, Curses::Color::WHITE, defaultcolor);
}

void ColorPickerPalette::addColorCube(int defaultcolor)
{
  int w, h, x, y;

  // resize the ColorPickerPalette
  w = getWidth();
  h = getHeight();

  // add space between this and previous section
  if (h)
    h++;

  y = h;

  w = MAX(w, (6 * 6 * 2) + 5);
  h = h + 6;

  resize(w, h);

  // add the color picker buttons
  x = 0;
  for (int g = 0; g < 6; g++) {
    for (int r = 0; r < 6; r++) {
      for (int b = 0; b < 6; b++) {
        addButton(x, y, 16 + (r * 36) + (g * 6) + b, defaultcolor);
        x += 2;
      }

      x++;
    }

    y++;
    x = 0;
  }
}

ColorPickerPalette::ColorPickerPaletteButton::ColorPickerPaletteButton(
    int color)
: Button(2, 1, ""), color(color)
{
}

void ColorPickerPalette::ColorPickerPaletteButton::draw()
{
  proceedUpdateArea();

  if (!area)
    return;

  ColorScheme::Color c(Curses::Color::BLACK, color);
  int colorpair = COLORSCHEME->getColorPair(c);

  if (has_focus) {
    area->attron(Curses::Attr::REVERSE);
    area->mvaddstring(0, 0, "@@");
    area->attroff(Curses::Attr::REVERSE);
  }
  else
    area->fill(colorpair, 0, 0, 2, 1);
}

} // namespace CppConsUI

/* vim: set tabstop=2 shiftwidth=2 textwidth=78 expandtab : */
