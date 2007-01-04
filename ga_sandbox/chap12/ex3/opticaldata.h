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

#ifndef _OPTICAL_DATA_
#define _OPTICAL_DATA_

#include <vector>

#include <libgasandbox/h3ga.h>
#include <libgasandbox/c3ga.h>

class OpticalCaptureCameraData {
public:
	OpticalCaptureCameraData() {}
	OpticalCaptureCameraData(const OpticalCaptureCameraData &CD) : 
		m_position(CD.m_position), 
		m_orientation(CD.m_orientation), 
		m_imagePlane(CD.m_imagePlane), 
		m_2Dmarkers(CD.m_2Dmarkers), 
		m_XF(CD.m_XF), 
		m_XFi(CD.m_XFi) {}

	OpticalCaptureCameraData &operator=(const OpticalCaptureCameraData &CD) {
		if (this != &CD) {
			m_position = CD.m_position;
			m_orientation = CD.m_orientation;
			m_imagePlane = CD.m_imagePlane;
			m_2Dmarkers = CD.m_2Dmarkers;
			m_XF = CD.m_XF;
			m_XFi = CD.m_XFi;
		}
		return *this;
	}

	/// position of camera (derived from m_XF)
	h3ga::normalizedPoint m_position;
	/// orientation of camera  (derived from m_XF)
	h3ga::rotor m_orientation;

	/// image plane in world frame
	h3ga::plane m_imagePlane;

	/**
	2D markers (represented as points in the image plane)
	First index is frame index.
	Second index is marker index, for that frame.
	*/
	std::vector<std::vector<h3ga::normalizedPoint> >m_2Dmarkers;

	/// the transform of the camera (conformal model versor)
	c3ga::TRversor m_XF;

	/// inverse transform of the camera (conformal model versor)
	c3ga::TRversor m_XFi;
};


class OpticalCaptureData {
public:
	OpticalCaptureData() {}
	OpticalCaptureData(const OpticalCaptureData &D) : m_cameraData(D.m_cameraData) {}
	OpticalCaptureData(const std::vector<OpticalCaptureCameraData> &CD) : m_cameraData(CD) {}

	OpticalCaptureData &operator=(const OpticalCaptureData &D) {
		if (this != &D) {
			m_cameraData = D.m_cameraData;
		}
		return *this;
	}


	/**
	Reconstructs the markers for frame 'frameIdx'.
	Results are returned in 'reconstructedMarkers'.

	'epsilon' determines the maximum distance in 
	the image plane between 2D points, before they are
	not matched anymore.

	'minNbCameras' specifies how many cameras should
	participate in a reconstructed marker before it is returned
	in 'econstructedMarkers'.
	*/
	void reconstructFrame(int frameIdx, std::vector<h3ga::normalizedPoint> &reconstructedMarkers,
		h3ga::mv::Float epsilon, h3ga::mv::Float close, int minNbCameras);

	/// the cameras (each camera holds its own data):
	std::vector<OpticalCaptureCameraData> m_cameraData;
};



#endif /* _OPTICAL_DATA_ */
