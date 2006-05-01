#ifndef _MAIN_H_
#define _MAIN_H_

extern vector & (*g_evalFunc)(const vector &p, vector &v);
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
extern glwindow *g_GLWindow;

extern int g_Dcube;
extern int g_showSphere;
extern int g_showPSphere;
extern int g_showNSphere;
extern int g_showCirc;

extern int g_USphere;
extern int g_ISphere;
extern float g_hpvalue;

#endif /* _MAIN_H_ */
