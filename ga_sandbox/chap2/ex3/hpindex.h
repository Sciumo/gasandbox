#ifndef _HP_INDEX_H_
#define _HP_INDEX_H_

int sumFace(const e3ga &p, const e3ga &v1, const e3ga &v2, 
	    const int gsi, e3ga &sum3d, int &lineSing, int &surfSing,
	    e3ga & (*evalFunc)(const e3ga &p, e3ga &v), int depth, 
	    int maxDepth, int face);

int sumCube(const e3ga &p, const e3ga dir[3],
		 const int gsi, int &pointSing, int &lineSing, int &surfSing,
		 e3ga & (*evalFunc)(const e3ga &p, e3ga &v), int depth, int maxDepth);

int	findSingularities(const e3ga &p, const e3ga dir[3],
		 const int gsi, e3ga & (*evalFunc)(const e3ga &p, e3ga &v), int depth, int maxDepth);

	// simple function to draw sphere of vectors around one cube
	void drawSphere(int gs, int type);
	void drawCirc(int gs, int type);

#endif /* _HP_INDEX_H_ */
