#include "opticaldata.h"

using namespace h3ga;

/*
In homogeneous model:

line 1: P1 + d1 D1
line 2: P2 + d2 D2

What 'd1' and 'd2' for closest point on both lines?

// compute difference between starting points, and try to factor that in terms of 'P1' and 'P2'
dif = P2 - P1
Ii = inverse(D1 ^ D2)
// reciprocals:
rD1 = D2 . Ii
rD2 = D1 . Ii

solution:
d1 = rD1 . dif
d2 = rD2 . dif

Returns d1 and d2

Note: checks that P1 and P2 are not parallel, because then it won't work!
Returns true when lines are parallel. In that case, the values of d1 and d2
are left unchanged.
*/
bool closestPointsOnCrossingLines(
	const normalizedPoint &P1, const h3ga::vector &D1,
	const normalizedPoint &P2, const h3ga::vector &D2,
	mv::Float &d1, mv::Float &d2) {

	// compute difference between starting points, and try to factor that in terms of 'D1' and 'D2'
	h3ga::vector dif = _vector(P2 - P1);

	// compute inverse pseudoscalar of space spanned by D1 and D2
	bivector I = _bivector(D1 ^ D2);
	if (_Float(norm_e2(I)) == 0.0f) return true; // check parallel
	bivector Ii = _bivector(inverse(I));

	// compute reciprocals:
	h3ga::vector rD1 = _vector(D2 << Ii);
	h3ga::vector rD2 = _vector(D1 << Ii); // actually computes minus reciprocal of D2

	// solution:
	d1 = _Float(rD1 << dif);
	d2 = _Float(rD2 << dif);

	return false;
}

// *!*HTML_TAG*!* reconstruct
/**
Simplistic algorithm for reconstructing markers in optical motion capture.
We first try to reconstruct 3D markers using every possible combination of
two cameras. When a marker is reconstructed, we try if it is also visible in
other cameras.
*/
void OpticalCaptureData::reconstructFrame(int frameIdx,
					std::vector<normalizedPoint> &reconstructedMarkers,
					mv::Float epsilon, mv::Float markerSize,
					int minNbCameras) {
	// reconstructed markers go into 'R' first
	// (at the end of the function, they are copied into reconstructedMarkers).
	std::vector<point> R;

	for (unsigned int c1 = 0; c1 < m_cameraData.size()-1; c1++) {
		OpticalCaptureCameraData &C1 = m_cameraData[c1];
		normalizedPoint &P1 = C1.m_position; // camera position
		std::vector<normalizedPoint> &F1 = C1.m_2Dmarkers[frameIdx];

		for (unsigned int m1 = 0; m1 < F1.size(); m1++) {
			const normalizedPoint &M1 = F1[m1]; // position of marker in image plane
			h3ga::vector D1 = _vector(M1 - P1); // ray direction

			line L1 = _line(unit_r(P1 ^ M1)); // line from camera pinhole through marker

			for (unsigned int c2 = c1 + 1; c2 < m_cameraData.size(); c2++) {
				OpticalCaptureCameraData &C2 = m_cameraData[c2];
				const normalizedPoint &P2 = C2.m_position; // camera position
				std::vector<normalizedPoint> &F2 = C2.m_2Dmarkers[frameIdx];
				const plane &IP = C2.m_imagePlane; // image plane

				// project L1 onto image plane of camera 2:
				line L2 = _line(unit_r(dual(L1 ^ P2) << IP));

				for (unsigned int m2 = 0; m2 < F2.size(); m2++) {
					normalizedPoint &M2 = F2[m2]; // position of marker in image plane

					// check distance in image plane
					mv::Float dis = fabs(_Float((M2 << IP) << L2));
					if (dis > epsilon) continue;

					h3ga::vector D2 = _vector(M2 - P2); // ray direction

					// compute candidate for reconstructed marker
					mv::Float d1, d2;
					bool parallel = closestPointsOnCrossingLines(P1, D1, P2, D2, d1, d2);
					if (parallel) continue;
					else {
						// reconstruct initial match
						normalizedPoint RM1 = _normalizedPoint(P1 + d1 * D1);
						normalizedPoint RM2 = _normalizedPoint(P2 + d2 * D2);
						if (_Float(norm_e(RM1 - RM2)) < epsilon)
							R.push_back(_point(RM1 + RM2));
					}
				}
			}
		}
	}

	// merge 'close' markers:
	for (unsigned int i = 0; i < R.size(); i++) {
		point &M1 = R[i];
		for (unsigned int j = i+1; j < R.size(); j++) {
			point &M2 = R[j];
			if (_Float(norm_e(M1 * (1.0f / M1.e0()) - M2 * (1.0f / M2.e0()))) < markerSize) {
				// merge:
				R[i] = R[i] + R[j];

				// move last marker to position 'j'
				R[j] = R[R.size()-1];
				R.resize(R.size()-1);
				j--; // make sure we visit 'j' again, since it now has a new marker in it
			}
		}
	}

	// copy 'R' to 'reconstructedMarkers' when enough cameras have contributed to it:
	for (unsigned int i = 0; i < R.size(); i++) {
		// NOTE: we use e0 coordinates as a counter
		if ((int)R[i].e0() >= minNbCameras) {
			reconstructedMarkers.push_back(_normalizedPoint(R[i] * (1.0f / R[i].e0())));
		}
	}

}
