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

#ifndef _MAIN_H_
#define _MAIN_H_

#include <libgasandbox/e3ga.h>


extern e3ga::vector & (*g_evalFunc)(const e3ga::vector &p, e3ga::vector &v);
extern int g_gs, g_vgs, g_maxDepth,g_adap;
extern double g_lastTiming;
extern int g_boxes;
extern float g_cubeSize;
extern int g_showField, g_showOctree, g_showResult, g_unitField, g_bottom;
extern int g_lineSing, g_surfSing;
extern int g_falseLineSing, g_falseSurfSing;
extern float g_vectorSize;
extern float g_sratio, g_lratio;
extern float g_psing, g_lsing;
extern float g_cx, g_cy, g_cz;
extern float g_refine;
extern float l_refine;
extern int g_lighting;

extern int g_Dcube;
extern int g_showSphere;
extern int g_showPSphere;
extern int g_showNSphere;
extern int g_showCirc;

extern int g_USphere;
extern int g_ISphere;
extern float g_hpvalue;

extern e3ga::rotor g_modelRotor;
extern float g_modelDistance;


#endif /* _MAIN_H_ */
