/*
 * Copyright (C) 2007 by Mark Pustjens <pustjens@dds.nl>
 * Copyright (C) 2010-2011 by CenterIM developers
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

#include "CenterIM.h"
#include "gettext.h"

int main(int argc, char **argv)
{
  CenterIM* cim;

  g_set_prgname(PACKAGE_NAME);

#ifdef ENABLE_NLS
  bindtextdomain(PACKAGE_NAME, LOCALEDIR);
  bind_textdomain_codeset(PACKAGE_NAME, "UTF-8");
  textdomain(PACKAGE_NAME);
#endif

  setlocale(LC_ALL, "");

  cim = CenterIM::Instance();

  return cim->Run();
}
