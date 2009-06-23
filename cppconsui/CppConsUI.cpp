/*
 * Copyright (C) 2007 by Mark Pustjens <pustjens@dds.nl>
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

#include "CppConsUI.h"

#include <glibmm/ustring.h>
#include <wchar.h>
#include <cstring>

#if defined(USE_NCURSES) && !defined(RENAMED_NCURSES)
#include <ncurses.h>
#else
#include <curses.h>
#endif

//TODO getmaxx(stdscreen) just must have less overhead
int RealScreenWidth(void)
{
	int x, y;
	getmaxyx(stdscr, y, x);
	return x;
}

int RealScreenHeight(void)
{
	int x, y;
	getmaxyx(stdscr, y, x);
	return y;
}

Glib::ustring::size_type width(const Glib::ustring &string)
{
	return width(string.data(), string.data()+string.bytes());
}

/* NOTE: copied from pango/break.c, which has GNU GPL 2 or later
 * thank you pango team
 */
void find_paragraph_boundary (const gchar *text,
			       gint         length,
			       gint        *paragraph_delimiter_index,
			       gint        *next_paragraph_start)
{
  const gchar *p = text;
  const gchar *end;
  const gchar *start = NULL;
  const gchar *delimiter = NULL;

  /* Only one character has type G_UNICODE_PARAGRAPH_SEPARATOR in
   * Unicode 5.0; update the following code if that changes.
   */

  /* prev_sep is the first byte of the previous separator.  Since
   * the valid separators are \r, \n, and PARAGRAPH_SEPARATOR, the
   * first byte is enough to identify it.
   */
  gchar prev_sep;


  if (length < 0)
    length = strlen (text);

  end = text + length;

  if (paragraph_delimiter_index)
    *paragraph_delimiter_index = length;

  if (next_paragraph_start)
    *next_paragraph_start = length;

  if (length == 0)
    return;

  prev_sep = 0;


  while (p != end)
    {
      if (prev_sep == '\n' ||
	  prev_sep == PARAGRAPH_SEPARATOR_STRING[0])
	{
	  g_assert (delimiter);
	  start = p;
	  break;
	}
      else if (prev_sep == '\r')
	{
	  /* don't break between \r and \n */
	  if (*p != '\n')
	    {
	      g_assert (delimiter);
	      start = p;
	      break;
	    }
	}

      if (*p == '\n' ||
	   *p == '\r' ||
	   !strncmp(p, PARAGRAPH_SEPARATOR_STRING,
		    strlen(PARAGRAPH_SEPARATOR_STRING)))
	{
	  if (delimiter == NULL)
	    delimiter = p;
	  prev_sep = *p;
	}
      else
	prev_sep = 0;

      p = g_utf8_next_char (p);
    }

  if (delimiter && paragraph_delimiter_index)
    *paragraph_delimiter_index = delimiter - text;

  if (start && next_paragraph_start)
    *next_paragraph_start = start - text;
}

const gchar text_unknown_char_utf8[] = { '\xEF', '\xBF', '\xBC', '\0' };

//NOTE copied from libgnt/gntutils.c
//TODO should g_unichar_iszerowidth be used?
//TODO write a wrapper string class
//if so, then also include drawing functions and a way to store colours
//for a string.
Glib::ustring::size_type width(const char *start, const char *end)
{
        Glib::ustring::size_type width = 0;

        if (end == NULL)
                end = start + strlen(start);

        while (start < end) {
                width += g_unichar_iswide(g_utf8_get_char(start)) ? 2 : 1;
                start = g_utf8_next_char(start);
        }
        return width;
}

gchar* col_offset_to_pointer(gchar *str, glong offset)
{
	glong width = 0;

	while (width < offset) {
		width += g_unichar_iswide(g_utf8_get_char(str)) ? 2 : 1;
                str = g_utf8_next_char(str);
	}

	return str;
}

Point::Point()
: x(0)
, y(0)
{
}

Point::Point(int x, int y)
: x(x)
, y(y)
{
}

Rect::Rect()
: Point(0, 0)
, width(0)
, height(0)
{
}

Rect::Rect(int x, int y, int w, int h)
: Point(x, y)
, width(w)
, height(h)
{
}
