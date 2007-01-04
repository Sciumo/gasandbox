// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

// Copyright 2007, Daniel Fontijne, University of Amsterdam -- fontijne@science.uva.nl

#ifndef _CHAP2_EX3_RENDER_H_
#define _CHAP2_EX3_RENDER_H_

#include <libgasandbox/e3ga.h>

extern bool g_makeNewList;
extern GLfloat lineColor[];

void drawCube(const e3ga::vector &p, float size);
void drawAll();


#endif /* _CHAP2_EX3_RENDER_H_ */
