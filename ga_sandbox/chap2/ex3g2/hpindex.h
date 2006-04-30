#ifndef _HP_INDEX_H_
#define _HP_INDEX_H_

#include <libgasandbox/e3ga.h>

int sumFace(const vector &p, const vector &v1, const vector &v2, 
	    const int gsi, vector &sum3d, int &lineSing, int &surfSing,
	    vector & (*evalFunc)(const vector &p, vector &v), int depth, 
	    int maxDepth, int face);

int sumCube(const vector &p, const vector dir[3],
		 const int gsi, int &pointSing, int &lineSing, int &surfSing,
		 vector & (*evalFunc)(const vector &p, vector &v), int depth, int maxDepth);

int	findSingularities(const vector &p, const vector dir[3],
		 const int gsi, vector & (*evalFunc)(const vector &p, vector &v), int depth, int maxDepth);

	// simple function to draw sphere of vectors around one cube
	void drawSphere(int gs, int type);
	void drawCirc(int gs, int type);

#endif /* _HP_INDEX_H_ */
