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

#ifndef _EXT_CALIB_REFINE_H_
#define _EXT_CALIB_REFINE_H_

#include <vector>
#include <libgasandbox/e3ga.h>

namespace extCalibRefine {

/**
Implementation of Lasenby external calibration optimization algo.
*/

class Camera {
public:
	Camera();

	/**
	Creates camera for external calibration refinement.
	R = initial rotation
	t = initial translation
	visible = for each frame, is a marker visible?
	pt = point (in image plane) for each frame
	*/
	Camera(const e3ga::rotor &R, const e3ga::vector &t,
		const std::vector<bool> &visible,
		const std::vector<e3ga::vector> &pt); 

	Camera(const Camera&C);

	Camera &operator=(const Camera&C);

	void setR(const e3ga::rotor &R) {
		m_R = R;
		initRom();
	}

	unsigned int getNbFrames() const {
		return (unsigned int)m_visible.size();
	}

	void setNbFrames(unsigned int nb) {
		m_visible.resize(nb);
		m_pt.resize(nb);
		m_X3.resize(nb);
	}

	/// rotation
	e3ga::rotor m_R;
	/// rotation matrix 
	e3ga::om m_Rom;
	/// translation
	e3ga::vector m_t;
	/// for each frame, is a marker visible?
	std::vector<bool> m_visible;
	/// for each frame, the '2D' point in the image plane (normalized image coordinates, e3 = -1)
	std::vector<e3ga::vector> m_pt;
	/// for each frame the estimated multiplication factor of m_pt 
	std::vector<e3ga::mv::Float> m_X3;

protected:
	void initRom();

};

class State {
public:
	State();
	State(const std::vector<Camera> &cam);
	State(const State &S);

	State &operator=(const State &S);

	/// refine estimates for 'nb' loops
	void refineLoops(int nb);

	/// refine estimates for 't' seconds
	void refineSeconds(double t);

	/// the cameras
	std::vector<Camera> m_cam;

	/// the reconstructed points, for each frame
	std::vector<e3ga::vector> m_pt;
	/// is reconstruction of point valid?
	std::vector<bool> m_ptValid;

	int m_nbRefinements;

	double costFunction();

protected:
	void init();
	void refineOnce();

	void updateRotation();
	void updateTranslation();
	void updateX3();
	void updatePoints();
	void normalizeTranslation(bool updatePoints);
	void reconstructPoints();

	/// temp buffer, used by updateRotation()
	std::vector<e3ga::vector> m_v;
	/// temp buffer, used by updateRotation()
	std::vector<e3ga::vector> m_u;

	// the following not used anymore???
/*	e3ga::vector etYijk(int i, int j, int k) const;
	e3ga::vector etAijk(int i, int j, int k) const;
	e3ga::vector etPjk(int j, int k) const;
	void computeAsijk(int i, int j, int k, double Asijk[3]);*/

};


} /* end of namespace extCalibRefine */


#endif /* _EXT_CALIB_REFINE_H_ */
