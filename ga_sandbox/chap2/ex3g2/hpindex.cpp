#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef WIN32
#include <windows.h>
#endif
#include "glwindow.h"
#include <GL/gl.h>

#include "e3ga.h"
#include "fields.h"
#include "main.h"

static int ncube=0;

const double leps = 1e-09;

const double seps = 1e-09;

static float gLineSing;
static float g_lrefine=0.1;

void zNormalize(const e3ga &v, e3ga &n, float &l) {
	l = (float)sqrt(v.norm_a());
	if (l > 10e-9f)
		n = v / l;
	else {
	  //	printf("l %g\n",l);
		n = v;
		l = 0.0f;
	}
}

// Store data for surface fields
static e3ga* Dvf[6]; // Save the vector field over one cube to display it later
static int* Rvf[6]; // Note which pieces are refined so we won't display them
static e3ga* RDvf[1000]; // Overflow fields - caution, fixed sized array!
static int sRDvf[1000]; // How big is each field?
static int nRDvf; // Keep track of current field
static e3ga Dcenter; // center of the cube selected
static float Dlength; // Radius of sphere 

// Store data for line fields
const int max_sampsize = 100;
static e3ga Dpvf[6][4][max_sampsize]; // Save the project vector fields - caution, fixed sized array!
static int Rpvf[6][4][max_sampsize]; // Note which pieces are refined so we won't display them
static e3ga* RDpvf[6][1000]; // Overflow fields - caution, fixed size array!
static int sRDpvf[6][1000]; // How big is each field?
static int nRDpvf[6];

int refineFace(const e3ga &p, const e3ga &v1, const e3ga &v2, 
	       const int gsi, e3ga &sum3d, 
	       e3ga & (*evalFunc)(const e3ga &p, e3ga &v),
	       int adap) {

	e3ga *vf; // normalized vector field evaluations are stored in here
	float *vfs; // the sizes of the original vector field evaluations are stored in here
	int nbvf = 0;
	float gs = (float)gsi, tmp;
	int i, i1, i2, vfIdx;
	e3ga cp; // current position
	e3ga v, *cvf; 

	nbvf = ((gsi+1) * (gsi+1));
	vf = new e3ga[nbvf];
	vfs = new float[nbvf];

	if ( ncube == g_Dcube ) {
	  if (sRDvf[nRDvf] < nbvf) {
	    if (RDvf[nRDvf]) delete[] RDvf[nRDvf];
	    RDvf[nRDvf] = new e3ga[nbvf];
	    sRDvf[nRDvf] = nbvf;
	  }
	}

	// evaluate the vector field over the entire face
	for (i1 = 0; i1 <= gsi; i1++) {
		for (i2 = 0; i2 <= gsi; i2++) {
		  float dummy;
		  const float* pp;
			vfIdx = i1 * (gsi + 1) + i2;
			// compute position; evaluate
			cp = p +  v1 * ((float)i1 / gs) +
			  v2 * ((float)i2 / gs);
			evalFunc(cp, v);

			// normalize
			zNormalize(v, vf[vfIdx], dummy);
			if ( g_Dcube == ncube ) {
			  RDvf[nRDvf][vfIdx] = vf[vfIdx];
			}
		}
	}


	if ( g_Dcube == ncube ) {
	  nRDvf++;
	}

	// sum over face to compute 3d sum
	sum3d.null();
	for (i1 = 0; i1 < gsi; i1++) {
		for (i2 = 0; i2 < gsi; i2++) {
			cvf = vf + i1 * (gsi + 1) + i2; // just a pointer to the current location in the face

			e3ga a = cvf[0] ^ cvf[gsi + 2] ^ cvf[gsi + 1];
			e3ga b = cvf[0] ^ cvf[1] ^ cvf[gsi + 2];
			e3ga c, d;
			if ( adap > 0 &&
			     (fabs((a[GRADE3])[0]) > g_refine ||
			      fabs((b[GRADE3])[0]) > g_refine )) {
			  e3ga tmpsum3d;

			  printf("refineFace: refining %d (%d)\n",ncube,adap);
			  cp = p + v1 * (float)i1 / gs + v2 * (float)i2 / gs;
			  refineFace(cp, c=v1/gs, d=v2/gs, gsi, 
				  tmpsum3d, evalFunc, adap-1);
			  sum3d += tmpsum3d;
			} else {
			  sum3d += a+b;
			}
			if (0 && ncube == g_Dcube) {
			  printf("%d: vol %g %g\n", ncube,
				 (a[GRADE3])[0],
				 (b[GRADE3])[0]); 
			}
		}
	}

	delete[] vf;
	delete[] vfs;
	return 0;
}

int sumFace(const e3ga &p, const e3ga &v1, const e3ga &v2, 
	    const int gsi, e3ga &sum3d,
	    e3ga & (*evalFunc)(const e3ga &p, e3ga &v), 
	    float& maxVfs, float& minVfs,
	    int depth, int maxDepth, int Dface, int adap) {

	static e3ga *vf; // normalized vector field evaluations are stored in here
	static float *vfs; // the sizes of the original vector field evaluations are stored in here
	static e3ga *pvf[4]; // projected normalized (edge) vector field evaluations are stored in here
	static float *pvfs[4]; // todo: explain what is stored here
	e3ga sum3dUR; // keep track of unrefined sum
	static int nbvf = 0;
	float gs = (float)gsi, tmp;
	int i, i1, i2, vfIdx;
	e3ga cp; // current position
	e3ga v, face = v1 ^ v2, faceInv = face.inverse(), *cvf, pv; 
	float tmpFloat;
	int mf, pf;
	int rf; // true if we refine a face

	//	printf("Initially: minVfs = %g, maxVfs = %g\n",minVfs,maxVfs);
	// make sure we have enough memory to store vector field evaluations
	if ((gsi+1) * (gsi+1) > nbvf) {
		nbvf = ((gsi+1) * (gsi+1));
		if (vf) delete[] vf; vf = new e3ga[nbvf];
		for (i=0; i<6; i++) {
		  if (Dvf[i]) delete[] Dvf[i]; Dvf[i] = new e3ga[nbvf];
		  if (Rvf[i]) delete[] Rvf[i]; Rvf[i] = new int[nbvf];
		}
		vfs = (float*)realloc(vfs, sizeof(float) * nbvf);
		for (i = 0; i < 4; i++) {
			if (pvf[i]) delete[] pvf[i]; pvf[i] = new e3ga[gsi + 1];
			pvfs[i]  = (float*)realloc(pvfs[i], sizeof(float) * (gsi + 1));
		}
	}

	// evaluate the vector field over the entire face
	for (i1 = 0; i1 <= gsi; i1++) {
		for (i2 = 0; i2 <= gsi; i2++) {
			vfIdx = i1 * (gsi + 1) + i2;
			// compute position; evaluate
			cp = p + v1 * (float)i1 / gs + v2 * (float)i2 / gs;
			evalFunc(cp, v);

			// normalize
			zNormalize(v, vf[vfIdx], vfs[vfIdx]);

			// Save values if we want to display this cube's field
			if ( g_Dcube == ncube && adap == g_adap) {
			  Dvf[Dface][vfIdx] = vf[vfIdx];
			}

			// track minimum and maximum field value
			if (!(i1 || i2)) {
			  minVfs = maxVfs = vfs[vfIdx];
			  //			  printf("init minVfs, maxVfs, %g\n",minVfs);
			}
			else {
				if (vfs[vfIdx] < minVfs) {
				  minVfs = vfs[vfIdx];
				  //				  printf("update minVfs %g\n",minVfs);
				} else if (vfs[vfIdx] > maxVfs) {
				  maxVfs = vfs[vfIdx];
				  //				  printf("update maxVfs %g\n",maxVfs);
				}
			}
		}
	}

	// sum over face to compute 3d sum
	sum3d.null();
	sum3dUR.null();
	rf = 0;
	for (i1 = 0; i1 < gsi; i1++) {
		for (i2 = 0; i2 < gsi; i2++) {
			cvf = vf + i1 * (gsi + 1) + i2; // just a pointer to the current location in the face

			e3ga a = cvf[0] ^ cvf[gsi + 2] ^ cvf[gsi + 1];
			e3ga b = cvf[0] ^ cvf[1] ^ cvf[gsi + 2];
			e3ga c,d; // temps needed for gaigen
			if ( adap > 0 &&
			     (fabs((a[GRADE3])[0]) > g_refine ||
			      fabs((b[GRADE3])[0]) > g_refine )) {
			  e3ga tmpsum3d;
			  tmpsum3d.null();
			  int lsTmp, sfTmp;
			  rf = 1;
			  //printf("sumFace: refining %d (%d) %d, depth %d, %g %g\n",ncube,adap,gsi,depth,(a[GRADE3])[0],(b[GRADE3])[0]);
			  cp = p + v1 * (float)i1 / gs + v2 * (float)i2 / gs;

			  refineFace(cp, c=v1/gs, d=v2/gs, gsi, 
				  tmpsum3d, evalFunc, adap-1);
			  //printf("%g vs %g\n",((c=a+b)[GRADE3])[0], (tmpsum3d[GRADE3])[0]);
			  sum3d += tmpsum3d;
			  sum3dUR += a+b;

			  // Note if we refine a square
			  if ( g_Dcube == ncube ) {
			    Rvf[Dface][i1*(gsi+1) +i2] = 1;
			  }
			} else {
			  sum3d += a+b;
			  sum3dUR += a+b;

			  // Note if we don't refine a square
			  if ( g_Dcube == ncube ) {
			    Rvf[Dface][i1*(gsi+1) +i2] = 0;
			  }
			}
			if (0 && ncube == g_Dcube) {
			  printf("%d: vol %g %g\n", ncube,
				 (a[GRADE3])[0],
				 (b[GRADE3])[0]); 
			}
		}
	}
	if ( rf && 0 ) {
	  printf("Refined vs unrefined (%d): %g vs %g (%g)\n",ncube,(sum3d[GRADE3])[0], (sum3dUR[GRADE3])[0],(sum3d[GRADE3])[0]-(sum3dUR[GRADE3])[0]);
	}

	if ( rf ) {
	  extern int g_refines;
	  g_refines++;
	}
	return 0;
}

static e3ga g_sum2dUR; // Used to keep track of unrefined sum
static int g_2drf; // Used to keep track of whether we refine 2d

/*
 *----------------------------------------------------------------------
 *  Function:  sumEdge
 *	Sample an edge, projecting each sample onto the face.  Sum
 *  bivectors formed of adjacent projected vectors.  Also, test the
 *  positive/negative aspect of the edge (to be used elswhere for
 *  surface singularity detection).
 *----------------------------------------------------------------------
 */
e3ga sumEdge(const e3ga& p, const e3ga& v, const int gsi,
	     e3ga & (*evalFunc)(const e3ga &p, e3ga &v), 
	     float& minV, float& maxV,
	     const e3ga face, const e3ga faceInv, 
	     int& mf, int& pf, int Dface, int Dedge, int adap) {
  int i1;
  float gs=(float)gsi;
  float tmpFloat;
  e3ga pvf[1000];

  //  printf("sumEdge: Dface %d, Dedge %d\n",Dface,Dedge);

  if ( gsi >= 1000 ) {
    printf("sumEdge: %d samples on edge is too many.  Exiting.\n");
    exit(1);
  }

  if ( ncube == g_Dcube && g_adap != adap ) {
    if (sRDpvf[Dface][nRDpvf[Dface]] < gsi+1) {
      if (RDpvf[Dface][nRDpvf[Dface]]) delete[] RDpvf[Dface][nRDpvf[Dface]];
      RDpvf[Dface][nRDpvf[Dface]] = new e3ga[gsi+1];
      sRDpvf[Dface][nRDpvf[Dface]] = gsi+1;
    }
  }


  float tmpMin=100;
  for (i1=0; i1 <= gsi; i1++) {
    e3ga cp = p + v*(float)i1/gs;
    e3ga tmpv,tmpv2;
    evalFunc(cp, tmpv);
    zNormalize(tmpv, tmpv2, tmpFloat);
    if ( i1==0 ) {
      minV = maxV = tmpFloat;
    } else {
      if ( minV > tmpFloat ) minV = tmpFloat;
      if ( maxV < tmpFloat ) maxV = tmpFloat;
    }
    tmpv = (tmpv<<face)<<faceInv;
    zNormalize(tmpv, pvf[i1], tmpFloat);
    if ( tmpMin > tmpFloat ) tmpMin = tmpFloat;
    if ( ncube == g_Dcube  &&  adap == g_adap ) {
      Dpvf[Dface][Dedge][i1] = pvf[i1];
    } else if ( ncube == g_Dcube ) {
      RDpvf[Dface][nRDpvf[Dface]][i1] = pvf[i1];
    }
  }

  if ( 0 && tmpMin < 0.01 ) {
    printf("sumEdge %d: tmpMin = %g\n",ncube,tmpMin);
  }

  if ( g_Dcube == ncube && adap != g_adap ) {
    nRDpvf[Dface]++;
  }

  e3ga sum2d;
  tmpMin = 1000.0f;
  for (i1=0; i1<gsi; i1++) {
    e3ga a = pvf[i1] ^ pvf[i1+1];
    e3ga b = pvf[i1]<<pvf[i1+1];
    float tmpD=b.scalar();
    if ( tmpD < tmpMin ) {
      tmpMin = tmpD;
    }
    if ( tmpD < 0 ) {
      //      printf("tmpD %g, %d.%d, (%g,%g,%g).(%g,%g,%g)\n",tmpD,i1,i1+1,
      //	     ((pvf[i1])[GRADE1])[0],((pvf[i1])[GRADE1])[1],((pvf[i1])[GRADE1])[2],
      //	     ((pvf[i1+1])[GRADE1])[0],((pvf[i1+1])[GRADE1])[1],((pvf[i1+1])[GRADE1])[2]);
    }
    if ( adap > 0  &&  (fabs((a % a).scalar()) > g_lrefine*g_lrefine ||
			tmpD < 0.5) ) {
      float tmpMinV, tmpMaxV;
      e3ga cp = p + v * (float)i1 / gs;
      e3ga vtmp;
      e3ga tmpsum2d = sumEdge(cp, vtmp=v/gs, gsi, evalFunc, tmpMinV, tmpMaxV, 
		      face, faceInv,mf,pf,Dface,Dedge,adap-1);
      if ( minV > tmpMinV ) minV = tmpMinV;
      if ( maxV < tmpMaxV ) maxV = tmpMaxV;
      sum2d += tmpsum2d;
      g_sum2dUR += a;
      g_2drf = 1;
      if ( g_Dcube == ncube ) {
	Rpvf[Dface][Dedge][i1] = 1;
      }
    } else {
      sum2d += a;
      g_sum2dUR += a;
      if ( g_Dcube == ncube ) {
	Rpvf[Dface][Dedge][i1] = 0;
      }
    }
  }

  if ( tmpMin < 0 ) {
    //    printf("sumEdge %d (%d): min(tmpD) = %g\n",ncube,adap,tmpMin);
  }

  // test for surface singularity....
  for (i1 = 0; i1 <= gsi; i1++) {
    if ((pvf[i1] << v).scalar() < 0) mf = 1;
    else pf = 1;
  }
  return sum2d;
}

void sumEdges(const e3ga &p, const e3ga &v1, const e3ga &v2, 
	    const int gsi, int &lineSing, int &surfSing,
	    e3ga & (*evalFunc)(const e3ga &p, e3ga &v), int depth, 
	    int maxDepth, int Dface, int adap) {

	e3ga face = v1 ^ v2, faceInv = face.inverse();
	e3ga sum2d;
	int mf,pf;
	float minV,maxV;
	e3ga tmpP,tmpV; // Avoid gaigen problems

	mf = pf = 0;
	g_sum2dUR.null(); 
	g_2drf = 0;
	sum2d = sumEdge(p, v1, gsi, evalFunc, minV, maxV, 
			face, faceInv,mf,pf,Dface,0,adap);
	if ( mf==1 && pf==1 ) {
	  if ( minV < seps  ||  maxV/minV > g_sratio || !g_falseSurfSing) {
	    //	    printf("surfSing A %d: %g < %g || %g/%g=%g > %g\n",ncube,
	    //		   minV,seps,maxV,minV,maxV/minV,g_sratio);
	    surfSing = 1;
	  }
	}

	mf = pf = 0;
	sum2d += sumEdge(tmpP=p+v1,v2, gsi, evalFunc, minV, maxV, 
			 face, faceInv,mf,pf,Dface,1,adap);
	if ( mf==1 && pf==1 ) {
	  if ( minV < seps  ||  maxV/minV > g_sratio || !g_falseSurfSing) {
	    //	    printf("surfSing B %d: %g < %g || %g/%g=%g > %g\n",ncube,
	    //		   minV,seps,maxV,minV,maxV/minV,g_sratio);
	    surfSing = 1;
	  }
	}

	mf = pf = 0;
	sum2d += sumEdge(tmpP=p+v1+v2,tmpV= -v1, gsi, evalFunc, minV, maxV, 
			 face, faceInv,mf,pf,Dface,2,adap);
	if ( mf==1 && pf==1 ) {
	  if ( minV < seps  ||  maxV/minV > g_sratio || !g_falseSurfSing) {
	    //	    printf("surfSing C %d: %g < %g || %g/%g=%g > %g\n",ncube,
	    //		   minV,seps,maxV,minV,maxV/minV,g_sratio);
	    surfSing = 1;
	  }
	}

	mf = pf = 0;
	sum2d += sumEdge(tmpP=p+v2,tmpV= -v2, gsi, evalFunc, minV, maxV, 
			 face, faceInv,mf,pf,Dface,3,adap);
	if ( mf==1 && pf==1 ) {
	  if ( minV < seps  ||  maxV/minV > g_sratio || !g_falseSurfSing) {
	    //	    printf("surfSing D %d: %g < %g || %g/%g=%g > %g\n",ncube,
	    //		   minV,seps,maxV,minV,maxV/minV,g_sratio);
	    surfSing = 1;
	  }
	}


	// normalize 2d sum, set lineSing
	sum2d /= 3.1415f * 2.0f;

  if ( g_2drf ) {
    g_sum2dUR /= 3.1415f * 2.0f;
    //    printf("Refined vs unrefined 2d (%d): %g vs %g\n",
    //	   ncube, 
    //	   sqrt(fabs((sum2d % sum2d).scalar())), 
    //   sqrt(fabs((g_sum2dUR % g_sum2dUR).scalar())));
  }

	gLineSing = sqrt(fabs((sum2d % sum2d).scalar()));
	if (gLineSing > g_lsing) {
	  lineSing = 1;
	} else {
	  lineSing =0;
	}
	//	fprintf(stderr,"line sing is %g  %d\n",gLineSing,lineSing);
}

int sumCube(const e3ga &p, const e3ga dir[3],
		 const int gsi, int &pointSing, int &lineSing, int &surfSing,
		 e3ga & (*evalFunc)(const e3ga &p, e3ga &v), int depth, int maxDepth) {

	e3ga sum3d;
	int lsTmp = 0, sfTmp = 0;

	e3ga sum2d, tmpsum3d, v1, v2, cp;
	ncube++;

	if (ncube == g_Dcube) {
	  if ( g_USphere ) {
	    Dcenter = 0.0f*p;
	    Dlength=1.0f;
	  } else {
	    Dcenter = p + dir[0]/2 + dir[1]/2 + dir[2]/2;
	    if ( g_ISphere ) {
	      Dlength = sqrt((dir[0]/2).norm_a());
	    } else {
	      Dlength = sqrt((dir[0]/2 + dir[1]/2 + dir[2]/2).norm_a());
	    }
	  }
	}
	// these tables are used to evaluate all 6 faces of the cube
	static const int dirs[6][2] = // specifies which basis vectors (from 'dir') to use for each face
	{
		{0, 1}, // dir0 & dir1
		{2, 1}, // dir2 & dir1
		{0, 1}, // -dir0 & dir1
		{2, 1}, // -dir2 & dir1
		{0, 2}, // dir0 & dir2
		{0, 2}  // dir0 & -dir2
	};
	static const float signs[6][2] = // specifies the sign of the basis vector
	{
		{1, 1},
		{1, 1},
		{-1, 1},
		{-1, 1},
		{1, 1},
		{1, -1}
	};
	static const float offsets[6][3] = // specifies offset from p
	{
		{0, 0, 0},
		{1, 0, 0},
		{1, 0, 1},
		{0, 0, 1},
		{0, 1, 0},
		{0, 0, 1}
	};

	int i;

	// visit each of the 6 faces, compute the 3d sum, line & surface singularities
	for (i = 0; i < 6; i++) {
		float maxL,minL;
		int lsing=0,ssing=0;

		cp = p + offsets[i][0] * dir[0] + offsets[i][1] * dir[1] + 
		  offsets[i][2] * dir[2];
		v1 = signs[i][0] * dir[dirs[i][0]];
		v2 = signs[i][1] * dir[dirs[i][1]];
		tmpsum3d.null();
		sumFace(cp, v1, v2, gsi, tmpsum3d, evalFunc, maxL, minL,
			depth, maxDepth, i, g_adap);
		sum3d += tmpsum3d;

		sumEdges(cp, v1, v2, gsi, lsing, ssing,
			 evalFunc, depth, maxDepth, i, g_adap);
		// test for false line singularities
		if ( lsing ) {
		  //		  fprintf(stderr,"%d: %g<?%g, %g/%g=%g >? %g\n",
		  //  lsing,minL,leps,maxL,minL,maxL/minL,g_lratio);
		  if ( minL < leps  ||  maxL/minL > g_lratio  ||  !g_falseLineSing ) {
		    printf("lineSing %d %d/%d %g\n",ncube, depth,maxDepth,
			   gLineSing);
		    lineSing = 1;
		  } 
		}
		if ( ssing ) {
		  surfSing = 1;
		}
	}

	// normalize sum, detect point singularity
	sum3d /= 6.0f * 4.0f * 3.1415f / 3.0f;

	if ( g_Dcube == ncube  ||  sqrt(fabs((sum3d % sum3d).scalar())) > 0.1 ) {
	  const float* c = p[GRADE1];
	  const float* cc = (dir[0]+dir[1]+dir[2])[GRADE1];
	printf("%d: %g %d/%d (%g %g %g) (%g %g %g)\n",ncube, sqrt(fabs((sum3d % sum3d).scalar())),depth,maxDepth,c[0],c[1],c[2],c[0]+cc[0],c[1]+cc[1],c[2]+cc[2]);
	}
	if ( fabs((sum3d % sum3d).scalar()) > 1 ) {
			  printf("Point Sing > 1 (%g) %d\n",
				 sqrt(fabs((sum3d % sum3d).scalar())),depth);
	}
	if ( g_Dcube == ncube ) {
	  g_hpvalue = (sum3d[GRADE3])[0];
	}
	pointSing = (fabs((sum3d % sum3d).scalar()) > g_psing*g_psing);

	return 0;
}


/*
Finds & draws singularities
  */
int	findSingularities(const e3ga &p, const e3ga dir[3],
		 const int gsi, e3ga & (*evalFunc)(const e3ga &p, e3ga &v), int depth, int maxDepth) {
	int pointSing, lineSing, surfSing, sing;

	if ( depth == 0 ) {
	  ncube = 0;
	  nRDvf = 0;
	  nRDpvf[0] = nRDpvf[1] = nRDpvf[2] = nRDpvf[3] = nRDpvf[4] = nRDpvf[5] = 0;
	}
	g_boxes++;

	// evaluate current cube
	pointSing = lineSing = surfSing = 0;
	sumCube(p, dir, gsi, pointSing, lineSing, surfSing, evalFunc, depth, maxDepth);
	sing = pointSing | lineSing | surfSing;
	if ( sing && 0) {
	printf("sing %d (%d/%d) %d|%d|%d\n",ncube,
	       depth,maxDepth, pointSing,lineSing,surfSing);
	}

	// OpenGL drawing code...
	if ((depth == maxDepth) || g_showOctree) {
		GLfloat cRed[4] = {1.0f, 0.0f, 0.0f, 1.0f};
		GLfloat cGreen[4] = {0.0f, 1.0f, 0.0f, 1.0f};
		GLfloat cBlue[4] = {0.0f, 0.0f, 1.0f, 1.0f};
		GLfloat cWhite[4] = {1.0f, 1.0f, 1.0f, 1.0f};
		GLfloat cBlack[4] = {0.0f, 0.0f, 0.0f, 0.0f};
		GLfloat *color;
		if (pointSing) color = cRed;
		else if (lineSing) color = cGreen;
		else if (surfSing) color = cBlue;
		else color = cBlack;
		glColor3fv(color);
		glMaterialfv(GL_FRONT, GL_AMBIENT, color);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, color);

		glPolygonMode(GL_FRONT_AND_BACK, 
			      (sing  &&  depth == maxDepth) ? GL_FILL : GL_LINE);
		if (sing||g_bottom) {
			g_GLWindow->drawCube(p, g_cubeSize / (float)(1 << depth));
		}
	}

	// end of recursion
	if (depth == maxDepth) return 0;

	// if there was a singularity: descend down octree
	if (sing) {
		int i;
		// divide the size of the cube by two
		e3ga newDir[3], newP;
		for (i = 0; i < 3; i++)
			newDir[i] = 0.5f * dir[i];

		// go though all permutations of adding or not adding one of the 3 basis directions.
		// Descend octree
		for (i = 0; i < (1 << 3); i++) {
			newP = p + 
			(float)((i&1) != 0) * newDir[0] + 
			(float)((i&2) != 0) * newDir[1] + 
			(float)((i&4) != 0) * newDir[2];
			//			printf("subcube %d:%d\n",depth,i);
			findSingularities(newP, newDir, gsi, evalFunc, depth + 1, maxDepth);
		}
	}

	return 0;
}


// type==0 => lines, type==1 => positive, type==2 => negative
void drawSphere(int gs, int type) {
  //  static float origin[4] = {0.0f, 0.0f, 0.0f, 1.0f};
  int face;
  int i,i1,i2;
  int vfIdx;
  static GLfloat cRed[4] = {1.0f, 0.0f, 0.0f, 1.0f};
  static GLfloat cBlue[4] = {0.0f, 0.0f, 1.0f, 1.0f};

  switch (type) {
  case 0:
    glBegin(GL_LINES);
    glColor3fv(lineColor);
    for (face = 0; face<6; face++) {
      for (i1=0; i1<=gs; i1++) {
	for (i2=0; i2<=gs; i2++) {
	  glVertex3fv(Dcenter[GRADE1]);
	  vfIdx = i1 * (gs + 1) + i2;
	  glVertex3fv((Dlength*Dvf[face][vfIdx]+Dcenter)[GRADE1]);
	}
      }
    }
    for (i=0; i<nRDvf; i++) {
      for (i1=0; i1<=gs; i1++) {
	for (i2=0; i2<=gs; i2++) {
	  glVertex3fv(Dcenter[GRADE1]);
	  vfIdx = i1 * (gs + 1) + i2;
	  glVertex3fv((Dlength*RDvf[i][vfIdx]+Dcenter)[GRADE1]);
	}
      }
    }
    glEnd();
    break;
  case 1:
    glColor3fv(cRed);
    glMaterialfv(GL_FRONT, GL_AMBIENT, cRed);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cRed);

    glDisable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL );
    glBegin(GL_TRIANGLES);
    for (face = 0; face<6; face++) {
      for (i1=0; i1<gs; i1++) {
	for (i2=0; i2<gs; i2++) {
	  e3ga* cvf = Dvf[face] + i1 * (gs + 1) + i2; 
	  //		sum3d += (cvf[0] ^ cvf[gsi + 2] ^ cvf[gsi + 1]) + 
	  //		  (cvf[0] ^ cvf[1] ^ cvf[gsi + 2]);
	  if (!Rvf[face][i1*(gs+1) +i2] &&
	      ((cvf[0] ^ cvf[gs + 2] ^ cvf[gs + 1])[GRADE3])[0] >= 0 ) {
	    glVertex3fv((Dlength*cvf[0]+Dcenter)[GRADE1]);
	    glVertex3fv((Dlength*cvf[gs+2]+Dcenter)[GRADE1]);
	    glVertex3fv((Dlength*cvf[gs+1]+Dcenter)[GRADE1]);
	  }

	  if (!Rvf[face][i1*(gs+1) +i2] &&
	      ((cvf[0] ^ cvf[1] ^ cvf[gs + 2])[GRADE3])[0] >= 0 ) {
	    glVertex3fv((Dlength*cvf[0]+Dcenter)[GRADE1]);
	    glVertex3fv((Dlength*cvf[1]+Dcenter)[GRADE1]);
	    glVertex3fv((Dlength*cvf[gs+2]+Dcenter)[GRADE1]);
	  }
	}
      }
    }
    for (i=0; i<nRDvf; i++) {
      for (i1=0; i1<gs; i1++) {
	for (i2=0; i2<gs; i2++) {
	  e3ga* cvf = RDvf[i] + i1 * (gs + 1) + i2; 
	  //		sum3d += (cvf[0] ^ cvf[gsi + 2] ^ cvf[gsi + 1]) + 
	  //		  (cvf[0] ^ cvf[1] ^ cvf[gsi + 2]);
	  if ( ((cvf[0] ^ cvf[gs + 2] ^ cvf[gs + 1])[GRADE3])[0] >= 0 ) {
	    glVertex3fv((Dlength*cvf[0]+Dcenter)[GRADE1]);
	    glVertex3fv((Dlength*cvf[gs+2]+Dcenter)[GRADE1]);
	    glVertex3fv((Dlength*cvf[gs+1]+Dcenter)[GRADE1]);
	  }

	  if ( ((cvf[0] ^ cvf[1] ^ cvf[gs + 2])[GRADE3])[0] >= 0 ) {
	    glVertex3fv((Dlength*cvf[0]+Dcenter)[GRADE1]);
	    glVertex3fv((Dlength*cvf[1]+Dcenter)[GRADE1]);
	    glVertex3fv((Dlength*cvf[gs+2]+Dcenter)[GRADE1]);
	  }
	}
      }
    }
    glEnd();
    break;
  case 2:
    glColor3fv(cBlue);
    glMaterialfv(GL_FRONT, GL_AMBIENT, cBlue);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cBlue);

    glDisable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);
    for (face = 0; face<6; face++) {
      for (i1=0; i1<gs; i1++) {
	for (i2=0; i2<gs; i2++) {
	  e3ga* cvf = Dvf[face] + i1 * (gs + 1) + i2; 
	  //		sum3d += (cvf[0] ^ cvf[gs + 2] ^ cvf[gs + 1]) + 
	  //		  (cvf[0] ^ cvf[1] ^ cvf[gs + 2]);
	  if (!Rvf[face][i1*(gs+1) +i2] &&
	      ((cvf[0] ^ cvf[gs + 2] ^ cvf[gs + 1])[GRADE3])[0] <= 0 ) {
	    glVertex3fv((Dlength*cvf[0]+Dcenter)[GRADE1]);
	    glVertex3fv((Dlength*cvf[gs+2]+Dcenter)[GRADE1]);
	    glVertex3fv((Dlength*cvf[gs+1]+Dcenter)[GRADE1]);
	  } 

	  if (!Rvf[face][i1*(gs+1) +i2] &&
	      ((cvf[0] ^ cvf[1] ^ cvf[gs + 2])[GRADE3])[0] <= 0 ) {
	    glVertex3fv((Dlength*cvf[0]+Dcenter)[GRADE1]);
	    glVertex3fv((Dlength*cvf[1]+Dcenter)[GRADE1]);
	    glVertex3fv((Dlength*cvf[gs+2]+Dcenter)[GRADE1]);
	  }
	}
      }
    }
    for (i=0; i<nRDvf; i++) {
      for (i1=0; i1<gs; i1++) {
	for (i2=0; i2<gs; i2++) {
	  e3ga* cvf = RDvf[i] + i1 * (gs + 1) + i2; 
	  //		sum3d += (cvf[0] ^ cvf[gsi + 2] ^ cvf[gsi + 1]) + 
	  //		  (cvf[0] ^ cvf[1] ^ cvf[gsi + 2]);
	  if ( ((cvf[0] ^ cvf[gs + 2] ^ cvf[gs + 1])[GRADE3])[0] < 0 ) {
	    glVertex3fv((Dlength*cvf[0]+Dcenter)[GRADE1]);
	    glVertex3fv((Dlength*cvf[gs+2]+Dcenter)[GRADE1]);
	    glVertex3fv((Dlength*cvf[gs+1]+Dcenter)[GRADE1]);
	  }

	  if ( ((cvf[0] ^ cvf[1] ^ cvf[gs + 2])[GRADE3])[0] < 0 ) {
	    glVertex3fv((Dlength*cvf[0]+Dcenter)[GRADE1]);
	    glVertex3fv((Dlength*cvf[1]+Dcenter)[GRADE1]);
	    glVertex3fv((Dlength*cvf[gs+2]+Dcenter)[GRADE1]);
	  }
	}
      }
    }
    glEnd();
    break;
  }
}

// type==0 => lines, type==1 => positive, type==2 => negative
void drawCirc(int gs, int type) {
  //  static float origin[4] = {0.0f, 0.0f, 0.0f, 1.0f};
  int face;
  int i,i1,i2;
  int vfIdx;
  static GLfloat cRed[4] = {1.0f, 0.0f, 0.0f, 1.0f};
  static GLfloat cBlue[4] = {0.0f, 0.0f, 1.0f, 1.0f};
  static int dirs[6][3] = {
    {0,0,-1},
    {1,0,0},
    {0,0,1},
    {-1,0,0},
    {0,1,0},
    {0,-1,0}
  };

  switch (type) {
  case 0:
    glBegin(GL_LINES);
    glColor3fv(lineColor);
    for (face = 0; face<6; face++) {
      e3ga oCenter;
      oCenter = Dcenter+Dlength*dirs[face][0]*(e3ga)e3ga::e1 +
	Dlength*dirs[face][1]*(e3ga)e3ga::e2 +
	Dlength*dirs[face][2]*(e3ga)e3ga::e3;
      for (i1=0; i1<=gs; i1++) {
	glVertex3fv(oCenter[GRADE1]);
	glVertex3fv((Dlength*Dpvf[face][0][i1]+oCenter)[GRADE1]);
	glVertex3fv(oCenter[GRADE1]);
	glVertex3fv((Dlength*Dpvf[face][1][i1]+oCenter)[GRADE1]);
	glVertex3fv(oCenter[GRADE1]);
	glVertex3fv((Dlength*Dpvf[face][2][i1]+oCenter)[GRADE1]);
	glVertex3fv(oCenter[GRADE1]);
	glVertex3fv((Dlength*Dpvf[face][3][i1]+oCenter)[GRADE1]);
      }
#if 1
      for (i=0; i<nRDpvf[face]; i++) {
	for (i1=0; i1<=gs; i1++) {
	  glVertex3fv(oCenter[GRADE1]);
	  glVertex3fv((Dlength*RDpvf[face][i][i1]+oCenter)[GRADE1]);
	}
      }
#endif
    }
    glEnd();
    break;
  case 1:
    glColor3fv(cRed);
    glMaterialfv(GL_FRONT, GL_AMBIENT, cRed);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cRed);

    glDisable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL );
    glBegin(GL_TRIANGLES);
    for (face = 0; face<6; face++) {
      e3ga up=Dlength*dirs[face][0]*(e3ga)e3ga::e1 +
	Dlength*dirs[face][1]*(e3ga)e3ga::e2 +
	Dlength*dirs[face][2]*(e3ga)e3ga::e3;
      e3ga oCenter = Dcenter+up;
      e3ga faceB = up.dual();

      for (i1=0; i1<gs; i1++) {
	if ( !Rpvf[face][0][i1] &&
	     ((faceB<<(Dpvf[face][0][i1]^Dpvf[face][0][i1+1]))[GRADE0])[0] >= 0 ) {
	    glVertex3fv((oCenter)[GRADE1]);
	    glVertex3fv((Dlength*Dpvf[face][0][i1]+oCenter)[GRADE1]);
	    glVertex3fv((Dlength*Dpvf[face][0][i1+1]+oCenter)[GRADE1]);
	}

	if ( !Rpvf[face][1][i1] &&
	     ((faceB<<(Dpvf[face][1][i1]^Dpvf[face][1][i1+1]))[GRADE0])[0] >= 0 ) {
	    glVertex3fv((oCenter)[GRADE1]);
	    glVertex3fv((Dlength*Dpvf[face][1][i1]+oCenter)[GRADE1]);
	    glVertex3fv((Dlength*Dpvf[face][1][i1+1]+oCenter)[GRADE1]);
	}

	if ( !Rpvf[face][2][i1] &&
	     ((faceB<<(Dpvf[face][2][i1]^Dpvf[face][2][i1+1]))[GRADE0])[0] >= 0 ) {
	    glVertex3fv((oCenter)[GRADE1]);
	    glVertex3fv((Dlength*Dpvf[face][2][i1]+oCenter)[GRADE1]);
	    glVertex3fv((Dlength*Dpvf[face][2][i1+1]+oCenter)[GRADE1]);
	}

	if ( !Rpvf[face][3][i1] &&
	     ((faceB<<(Dpvf[face][3][i1]^Dpvf[face][3][i1+1]))[GRADE0])[0] >= 0 ) {
	    glVertex3fv((oCenter)[GRADE1]);
	    glVertex3fv((Dlength*Dpvf[face][3][i1]+oCenter)[GRADE1]);
	    glVertex3fv((Dlength*Dpvf[face][3][i1+1]+oCenter)[GRADE1]);
	}
      }
#if 1
      for (i=0; i<nRDpvf[face]; i++) {
	for (i1=0; i1<gs; i1++) {
	  if ( ((faceB<<(RDpvf[face][i][i1]^RDpvf[face][i][i1+1]))[GRADE0])[0] >= 0 ) {
	    glVertex3fv(oCenter[GRADE1]);
	    glVertex3fv((Dlength*RDpvf[face][i][i1]+oCenter)[GRADE1]);
	    glVertex3fv((Dlength*RDpvf[face][i][i1+1]+oCenter)[GRADE1]);
	  }
	}
      }
#endif
    }
    glEnd();
    break;
  case 2:
    glColor3fv(cBlue);
    glMaterialfv(GL_FRONT, GL_AMBIENT, cBlue);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cBlue);

    glDisable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);
    for (face = 0; face<6; face++) {
      e3ga up=Dlength*dirs[face][0]*(e3ga)e3ga::e1 +
	Dlength*dirs[face][1]*(e3ga)e3ga::e2 +
	Dlength*dirs[face][2]*(e3ga)e3ga::e3;
      e3ga oCenter = Dcenter+.995*up;
      e3ga faceB = up.dual();

      for (i1=0; i1<gs; i1++) {
	if (  !Rpvf[face][0][i1] &&
	      ((faceB<<(Dpvf[face][0][i1]^Dpvf[face][0][i1+1]))[GRADE0])[0] < 0 ) {
	    glVertex3fv((oCenter)[GRADE1]);
	    glVertex3fv((Dlength*Dpvf[face][0][i1]+oCenter)[GRADE1]);
	    glVertex3fv((Dlength*Dpvf[face][0][i1+1]+oCenter)[GRADE1]);
	}

	if ( !Rpvf[face][1][i1] &&
	     ((faceB<<(Dpvf[face][1][i1]^Dpvf[face][1][i1+1]))[GRADE0])[0] < 0 ) {
	    glVertex3fv((oCenter)[GRADE1]);
	    glVertex3fv((Dlength*Dpvf[face][1][i1]+oCenter)[GRADE1]);
	    glVertex3fv((Dlength*Dpvf[face][1][i1+1]+oCenter)[GRADE1]);
	}

	if ( !Rpvf[face][2][i1] &&
	     ((faceB<<(Dpvf[face][2][i1]^Dpvf[face][2][i1+1]))[GRADE0])[0] < 0 ) {
	    glVertex3fv((oCenter)[GRADE1]);
	    glVertex3fv((Dlength*Dpvf[face][2][i1]+oCenter)[GRADE1]);
	    glVertex3fv((Dlength*Dpvf[face][2][i1+1]+oCenter)[GRADE1]);
	}

	if ( !Rpvf[face][3][i1] &&
	     ((faceB<<(Dpvf[face][3][i1]^Dpvf[face][3][i1+1]))[GRADE0])[0] < 0 ) {
	    glVertex3fv((oCenter)[GRADE1]);
	    glVertex3fv((Dlength*Dpvf[face][3][i1]+oCenter)[GRADE1]);
	    glVertex3fv((Dlength*Dpvf[face][3][i1+1]+oCenter)[GRADE1]);
	}
      }
#if 1
      for (i=0; i<nRDpvf[face]; i++) {
	for (i1=0; i1<gs; i1++) {
	  if ( ((faceB<<(RDpvf[face][i][i1]^RDpvf[face][i][i1+1]))[GRADE0])[0] < 0 ) {
	    glVertex3fv(oCenter[GRADE1]);
	    glVertex3fv((Dlength*RDpvf[face][i][i1]+oCenter)[GRADE1]);
	    glVertex3fv((Dlength*RDpvf[face][i][i1+1]+oCenter)[GRADE1]);
	  }
	}
      }
#endif
    }

    glEnd();
    break;
  }
}
