
// Generated on 2007-01-08 14:06:33 by G2 0.1 from 'E:\ga\ga_sandbox\ga_sandbox\libgasandbox\e3ga.gs2'

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


#include <stdio.h> /* required to save profile */
#include <stdlib.h> /* required to save profile */
	#include <time.h> /* required to save profile */

	#ifdef WIN32
	#include <winsock2.h>
	#else /* UNIX */
	#include <errno.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <unistd.h>
	#include <netdb.h>
	#include <sys/time.h>
	#include <arpa/inet.h>
	#include <netinet/in.h>
	#include <netinet/tcp.h>
	#include <fcntl.h>
	#endif // WIN32 / UNIX?


	#include <string.h>
	#include "e3ga.h"

	// pre_cpp_include


	namespace e3ga {

	// The dimension of the space:
	const int mv_spaceDim = 3;

	// Is the metric of the space Euclidean?
	const bool mv_metricEuclidean = true;


	// This array can be used to lookup the number of coordinates for a grade part of a general multivector
	const int mv_gradeSize[4] = {
		1, 3, 3, 1 
	};

	// This array can be used to lookup the number of coordinates based on a grade usage bitmap
	const int mv_size[16] = {
		0, 1, 3, 4, 3, 4, 6, 7, 1, 2, 4, 5, 4, 5, 7, 8 
	};

	// This array of ASCIIZ strings contains the names of the basis vectors
	const char *mv_basisVectorNames[3] = {
		"e1", "e2", "e3" 
	};

	// This array of integers contains the order of basis elements in the general multivector
	const int mv_basisElements[8][4] = {
		{-1}
		, {0, -1}
		, {1, -1}
		, {2, -1}
		, {0, 1, -1}
		, {1, 2, -1}
		, {0, 2, -1}
		, {0, 1, 2, -1}
	};

	// This array of integers contains the 'sign' (even/odd permutation of the canonical order) of basis elements in the general multivector
	const double mv_basisElementSign[8] = {
		1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0, 1.0 
	};

	// This array of integers contains the order of basis elements in the general multivector
	// Use it to answer: 'at what index do I find basis element [x] (x = basis vector bitmap)?
	const int mv_basisElementIndexByBitmap[8] = {
		0, 1, 2, 4, 3, 6, 5, 7 
	};

	// This array of integers contains the indices of basis elements in the general multivector
	// Use it to answer: 'what basis element do I find at index [x]'?
	const int mv_basisElementBitmapByIndex[8] = {
		0, 1, 2, 4, 3, 6, 5, 7 
	};




	// These strings determine how the output of string() is formatted.
	// You can alter them at runtime using mv_setStringFormat().

	const char *mv_string_fp = "%2.2f"; 
	const char *mv_string_start = ""; 
	const char *mv_string_end = ""; 
	const char *mv_string_mul = "*"; 
	const char *mv_string_wedge = "^"; 
	const char *mv_string_plus = " + "; 
	const char *mv_string_minus = " - "; 

	void mv_setStringFormat(const char *what, const char *format) {

		if (!strcmp(what, "fp")) 
			mv_string_fp = (format) ? format : "%2.2f"; 
		else if (!strcmp(what, "start")) 
			mv_string_start = (format) ? format : ""; 
		else if (!strcmp(what, "end")) 
			mv_string_end = (format) ? format : ""; 
		else if (!strcmp(what, "mul")) 
			mv_string_mul = (format) ? format : "*"; 
		else if (!strcmp(what, "wedge")) 
			mv_string_wedge = (format) ? format : "^"; 
		else if (!strcmp(what, "plus")) 
			mv_string_plus = (format) ? format : " + "; 
		else if (!strcmp(what, "minus")) 
			mv_string_minus = (format) ? format : " - ";	else {
			char msg[1024];
			sprintf(msg, "invalid argument to mv_setStringFormat(): %s", what);
			mv_throw_exception(msg, MV_EXCEPTION_WARNING);
		}

	}


	namespace g2Net {
		void closeSocket(int *sock) {
			if (*sock == -1) return;
			#ifdef WIN32
				closesocket(*sock);
			#else
				close(*sock);
			#endif
				*sock = -1;
		}

		void  setSocketNonBlocking(int sock) {
			#ifdef WIN32
				u_long arg = 1;
			ioctlsocket(sock, FIONBIO, &arg);
			#else
				int currentValue;
			currentValue = fcntl(sock, F_GETFL, 0);
			fcntl(sock, F_SETFL, currentValue | O_NONBLOCK);
			#endif
		}

		bool wouldBlock() {
			#ifdef WIN32
				return ((WSAGetLastError() == WSAEWOULDBLOCK) ? true : false);
			#else
				return ((errno == EWOULDBLOCK) ? true : false);
			#endif
		}

		// this function disables the Nagle algorithm for the given port
		void disableNagle(int sock) {
			int nodelay = 1;
			setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char*)&nodelay, sizeof(int));
		}

		// this function sets the TCP send/receive buffer to some size
		void setRecvBuffer(int sock, int size) {
			setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char*)&size, sizeof(int));
		}
		// this function sets the TCP send/receive buffer to some size
		void setSendBuffer(int sock, int size) {
			setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (char*)&size, sizeof(int));
		}

		int recvN(int sock, const unsigned char *buf, int n) {
			int idx = 0;
			while (idx < n) {
				int nbRecv = (int)recv(sock, (char*)buf + idx, n-idx, 0);
				if (nbRecv < 0) return nbRecv;
				else idx += nbRecv;
			}
			return n;
		}

		int sendN(int sock, const unsigned char *buf, int n) {
			int idx = 0;
			while (idx < n) {
				int nbSent = (int)send(sock, (char*)buf + idx, n-idx, 0);
				if (nbSent < 0) return nbSent;
				else idx += nbSent;
			}
			return n;
		}

		int serialize_uint(int forReal, unsigned char *dest, unsigned int idx, unsigned int value) {
			int i;
			if (forReal) {
				int wordSize = sizeof(unsigned int);
				for (i = 0; i < wordSize; i++)
				dest[idx + i] = (value >> ((wordSize - i - 1) << 3)) & 0xff;
			}
			return sizeof(unsigned int);
		}

		int serialize_ushort(int forReal, unsigned char *dest, unsigned int idx, unsigned short value) {
			int i;
			if (forReal) {
				int wordSize = sizeof(unsigned short);
				for (i = 0; i < wordSize; i++)
				dest[idx + i] = (value >> ((wordSize - i - 1) << 3)) & 0xff;
			}
			return sizeof(unsigned short);
		}

		int deserialize_uint(const unsigned char *source, unsigned int idx, unsigned int *value) {
			int i;
			int wordSize = sizeof(unsigned int);
			*value = 0;
			for (i = 0; i < wordSize; i++)
			*value |= (source[idx + i] << ((wordSize - i - 1) << 3));
			return sizeof(unsigned int);
		}

		int deserialize_ushort(const unsigned char *source, unsigned int idx, unsigned short *value) {
			int i;
			int wordSize = sizeof(unsigned short);
			*value = 0;
			for (i = 0; i < wordSize; i++)
			*value |= (unsigned short)(source[idx + i] << ((wordSize - i - 1) << 3));
			return sizeof(unsigned short);
		}


		void init() {
			#ifdef WIN32
				WORD wVersionRequested;
			WSADATA wsaData;
			int WSAerr; 

			static bool initDone = false;
			if (initDone) return;
			initDone = true;
			#endif /* WIN32 */

				#ifdef WIN32
				wVersionRequested = MAKEWORD( 2, 0 ); 
			WSAerr = WSAStartup( wVersionRequested, &wsaData );
			if ( WSAerr != 0 )
				throw std::string("init(): an error occured during WSAStartup() (%d)", WSAerr);
			#endif /* WIN32 */
		}

	} // end of namespace g2Net


	namespace g2Profiling {
		namespace { // anonymous namespace for profiling code:

			// todo: multithreading (mutex, etc)


			const char *g_functionNames[] = {
				// function names of G2 functions:
				"", // 0 
					"mv lcont(mv x, mv y)", // 1 
					"mv scp(mv x, mv y)", // 2 
					"mv gp(mv x, mv y)", // 3 
					"mv op(mv x, mv y)", // 4 
					"mv add(mv x, mv y)", // 5 
					"mv subtract(mv x, mv y)", // 6 
					"scalar norm_e2(mv x)", // 7 
					"scalar norm_e(mv x)", // 8 
					"mv unit_e(mv x)", // 9 
					"scalar norm_r2(mv x)", // 10 
					"scalar norm_r(mv x)", // 11 
					"mv unit_r(mv x)", // 12 
					"mv reverse(mv x)", // 13 
					"mv negate(mv x)", // 14 
					"mv dual(mv x)", // 15 
					"mv undual(mv x)", // 16 
					"mv inverse(mv x)", // 17 
					"mv apply_om(om x, mv y)", // 18 
					"mv gradeInvolution(mv x)", // 19 
					"void set(om __x__, vector __image_of_e1__, vector __image_of_e2__, vector __image_of_e3__)", // 20 
					// function names for underscore constructors for specialized types
					"__NON_G2__ _e1_t(mv arg1)", // 21 
					"__NON_G2__ _e2_t(mv arg1)", // 22 
					"__NON_G2__ _e3_t(mv arg1)", // 23 
					"__NON_G2__ _scalar(mv arg1)", // 24 
					"__NON_G2__ _vector2D(mv arg1)", // 25 
					"__NON_G2__ _vector(mv arg1)", // 26 
					"__NON_G2__ _bivector(mv arg1)", // 27 
					"__NON_G2__ _trivector(mv arg1)", // 28 
					"__NON_G2__ _rotor(mv arg1)", // 29 
					"__NON_G2__ ___e1_ct__(mv arg1)", // 30 
					"__NON_G2__ ___e2_ct__(mv arg1)", // 31 
					"__NON_G2__ ___e3_ct__(mv arg1)", // 32 
					"__NON_G2__ ___I3_ct__(mv arg1)", // 33 
					"__NON_G2__ ___I3i_ct__(mv arg1)", // 34 
					"__NON_G2__ ___syn_smv___e1_e2_e3_e1e2e3(mv arg1)", // 35 
					"__NON_G2__ ___syn_smv___e1e2f1_0(mv arg1)", // 36 
					"__NON_G2__ ___syn_smv___e1e2(mv arg1)", // 37 
					"__NON_G2__ ___syn_smv___scalar_e1e2(mv arg1)", // 38 
					"__NON_G2__ ___syn_smv___e3f_1_0(mv arg1)", // 39 
					"__NON_G2__ ___syn_smv___e1e3_e2e3(mv arg1)", // 40 
					"__NON_G2__ ___syn_smv___scalar_e1e3_e2e3(mv arg1)", // 41 
					"__NON_G2__ ___syn_smv___e1e2_e1e3_e2e3_e1e2e3(mv arg1)", // 42 
					"__NON_G2__ ___syn_smv___e1e3f_1_0(mv arg1)", // 43 
					"__NON_G2__ ___syn_smv___e1e3(mv arg1)", // 44 
					"__NON_G2__ ___syn_smv___scalar_e1e3(mv arg1)", // 45 
					"__NON_G2__ ___syn_smv___e2e3f1_0(mv arg1)", // 46 
					"__NON_G2__ ___syn_smv___e2e3(mv arg1)", // 47 
					"__NON_G2__ ___syn_smv___scalar_e2e3(mv arg1)", // 48 
					"__NON_G2__ ___syn_smv___e2_e3(mv arg1)", // 49 
					"__NON_G2__ ___syn_smv___e1_e3(mv arg1)", // 50 
					"__NON_G2__ ___syn_smv___e2_e3_e1e2e3(mv arg1)", // 51 
					"__NON_G2__ ___syn_smv___e1_e3_e1e2e3(mv arg1)", // 52 
					"__NON_G2__ ___syn_smv___e1_e2_e1e2e3(mv arg1)", // 53 
					"__NON_G2__ ___syn_smv___scalar_e1e2_e1e3(mv arg1)", // 54 
					"__NON_G2__ ___syn_smv___scalar_e1e2_e2e3(mv arg1)", // 55 
					"__NON_G2__ ___syn_smv___e2f_1_0(mv arg1)", // 56 
					"__NON_G2__ ___syn_smv___e1e2_e1e3(mv arg1)", // 57 
					"__NON_G2__ ___syn_smv___e1e2_e2e3(mv arg1)", // 58 
					"__NON_G2__ ___syn_smv___e1f1_0_e2f1_0(mv arg1)", // 59 
					"__NON_G2__ ___syn_smv___e1f1_0_e2f1_0_e3f1_0(mv arg1)", // 60 
					"__NON_G2__ ___syn_smv___e2_e1f1_0(mv arg1)", // 61 
					// function names for underscore constructors for floats
					"__NON_G2__ _float(mv arg1)", // 62 
					"__NON_G2__ _double(mv arg1)", // 63 
					"__NON_G2__ _Float(mv arg1)", // 64 
					""
			};

			const char *g_typeNames[] = {
				"", // 0 
					"void", // 1 
					"bool", // 2 
					"char", // 3 
					"short", // 4 
					"int", // 5 
					"float", // 6 
					"double", // 7 
					"mv", // 8 
					"om", // 9 
					"e1_t", // 10 
					"e2_t", // 11 
					"e3_t", // 12 
					"scalar", // 13 
					"vector2D", // 14 
					"vector", // 15 
					"bivector", // 16 
					"trivector", // 17 
					"rotor", // 18 
					"__e1_ct__", // 19 
					"__e2_ct__", // 20 
					"__e3_ct__", // 21 
					"__I3_ct__", // 22 
					"__I3i_ct__", // 23 
					"__syn_smv___e1_e2_e3_e1e2e3", // 24 
					"__syn_smv___e1e2f1_0", // 25 
					"__syn_smv___e1e2", // 26 
					"__syn_smv___scalar_e1e2", // 27 
					"__syn_smv___e3f_1_0", // 28 
					"__syn_smv___e1e3_e2e3", // 29 
					"__syn_smv___scalar_e1e3_e2e3", // 30 
					"__syn_smv___e1e2_e1e3_e2e3_e1e2e3", // 31 
					"__syn_smv___e1e3f_1_0", // 32 
					"__syn_smv___e1e3", // 33 
					"__syn_smv___scalar_e1e3", // 34 
					"__syn_smv___e2e3f1_0", // 35 
					"__syn_smv___e2e3", // 36 
					"__syn_smv___scalar_e2e3", // 37 
					"__syn_smv___e2_e3", // 38 
					"__syn_smv___e1_e3", // 39 
					"__syn_smv___e2_e3_e1e2e3", // 40 
					"__syn_smv___e1_e3_e1e2e3", // 41 
					"__syn_smv___e1_e2_e1e2e3", // 42 
					"__syn_smv___scalar_e1e2_e1e3", // 43 
					"__syn_smv___scalar_e1e2_e2e3", // 44 
					"__syn_smv___e2f_1_0", // 45 
					"__syn_smv___e1e2_e1e3", // 46 
					"__syn_smv___e1e2_e2e3", // 47 
					"__syn_smv___e1f1_0_e2f1_0", // 48 
					"__syn_smv___e1f1_0_e2f1_0_e3f1_0", // 49 
					"__syn_smv___e2_e1f1_0", // 50 
					""
			};

			const char *g_storageTypeNames[] = {
				"float"
			};

			// each entry records the use of a specific G2 type (profile() sets them to true)
			bool g_usedTypes[] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};

			// when the profile is saved, we also save all synthetic types that we used
			// these strings describe what to save:
			const char *g_synMVTypeGS2Strings[] = {
				NULL, // 0 
					NULL, // 1 
					NULL, // 2 
					NULL, // 3 
					NULL, // 4 
					NULL, // 5 
					NULL, // 6 
					NULL, // 7 
					NULL, // 8 
					NULL, // 9 
					NULL, // 10 
					NULL, // 11 
					NULL, // 12 
					NULL, // 13 
					NULL, // 14 
					NULL, // 15 
					NULL, // 16 
					NULL, // 17 
					NULL, // 18 
					NULL, // 19 
					NULL, // 20 
					NULL, // 21 
					NULL, // 22 
					NULL, // 23 
					"float : float;\nspecialization: __syn_smv___e1_e2_e3_e1e2e3(e1, e2, e3, e1^e2^e3);\n",
					"float : float;\nspecialization: __syn_smv___e1e2f1_0(e1^e2 = 1.0);\n",
					"float : float;\nspecialization: __syn_smv___e1e2(e1^e2);\n",
					"float : float;\nspecialization: __syn_smv___scalar_e1e2(1.0, e1^e2);\n",
					"float : float;\nspecialization: __syn_smv___e3f_1_0(e3 = -1.0);\n",
					"float : float;\nspecialization: __syn_smv___e1e3_e2e3(e1^e3, e2^e3);\n",
					"float : float;\nspecialization: __syn_smv___scalar_e1e3_e2e3(1.0, e1^e3, e2^e3);\n",
					"float : float;\nspecialization: __syn_smv___e1e2_e1e3_e2e3_e1e2e3(e1^e2, e1^e3, e2^e3, e1^e2^e3);\n",
					"float : float;\nspecialization: __syn_smv___e1e3f_1_0(e1^e3 = -1.0);\n",
					"float : float;\nspecialization: __syn_smv___e1e3(e1^e3);\n",
					"float : float;\nspecialization: __syn_smv___scalar_e1e3(1.0, e1^e3);\n",
					"float : float;\nspecialization: __syn_smv___e2e3f1_0(e2^e3 = 1.0);\n",
					"float : float;\nspecialization: __syn_smv___e2e3(e2^e3);\n",
					"float : float;\nspecialization: __syn_smv___scalar_e2e3(1.0, e2^e3);\n",
					"float : float;\nspecialization: __syn_smv___e2_e3(e2, e3);\n",
					"float : float;\nspecialization: __syn_smv___e1_e3(e1, e3);\n",
					"float : float;\nspecialization: __syn_smv___e2_e3_e1e2e3(e2, e3, e1^e2^e3);\n",
					"float : float;\nspecialization: __syn_smv___e1_e3_e1e2e3(e1, e3, e1^e2^e3);\n",
					"float : float;\nspecialization: __syn_smv___e1_e2_e1e2e3(e1, e2, e1^e2^e3);\n",
					"float : float;\nspecialization: __syn_smv___scalar_e1e2_e1e3(1.0, e1^e2, e1^e3);\n",
					"float : float;\nspecialization: __syn_smv___scalar_e1e2_e2e3(1.0, e1^e2, e2^e3);\n",
					"float : float;\nspecialization: __syn_smv___e2f_1_0(e2 = -1.0);\n",
					"float : float;\nspecialization: __syn_smv___e1e2_e1e3(e1^e2, e1^e3);\n",
					"float : float;\nspecialization: __syn_smv___e1e2_e2e3(e1^e2, e2^e3);\n",
					"float : float;\nspecialization: __syn_smv___e1f1_0_e2f1_0(e1 = 1.0, e2 = 1.0);\n",
					"float : float;\nspecialization: __syn_smv___e1f1_0_e2f1_0_e3f1_0(e1 = 1.0, e2 = 1.0, e3 = 1.0);\n",
					"float : float;\nspecialization: __syn_smv___e2_e1f1_0(e2, e1 = 1.0);\n",
					NULL
			};	


			class entry {
				friend bool operator==(const entry &E1, const entry &E2);
				public:
					inline entry(unsigned int funcIdx, unsigned short storageTypeIdx, unsigned short nbArg, unsigned short argType[]) : // custom init constructor
					m_count(1), m_funcIdx(funcIdx), m_storageTypeIdx(storageTypeIdx), m_nbArg(nbArg), m_argType(argType), m_deleteArgType(false),
					m_returnType(NULL), m_nbReturnTypes(0) {
				}
				inline entry(unsigned int funcIdx, unsigned short storageTypeIdx, unsigned short nbArg, unsigned short argType[], 
				unsigned short nbReturnType, unsigned short returnType[]) : // custom init constructor
					m_count(1), m_funcIdx(funcIdx), m_storageTypeIdx(storageTypeIdx), m_nbArg(nbArg), m_argType(argType), m_deleteArgType(false),
					m_returnType(NULL), m_nbReturnTypes(nbReturnType) {
					if (nbReturnType != NULL) {
						m_returnType = new unsigned short[m_nbReturnTypes];
						memcpy(m_returnType, returnType, m_nbReturnTypes * sizeof(unsigned short));			
					}
				}

				inline entry(const entry &E) : // copy constructor
				m_count(E.m_count), m_funcIdx(E.m_funcIdx), m_storageTypeIdx(E.m_storageTypeIdx), m_nbArg(E.m_nbArg), m_deleteArgType(true), m_nbReturnTypes(E.m_nbReturnTypes) {
					m_argType = new unsigned short[m_nbArg];
					memcpy(m_argType, E.m_argType, m_nbArg * sizeof(unsigned short));

					if (m_nbReturnTypes) {
						m_returnType = new unsigned short[m_nbReturnTypes];
						memcpy(m_returnType, E.m_returnType, m_nbReturnTypes * sizeof(unsigned short));
					}
					else m_returnType = NULL;
				}

				inline ~entry() {
					if (m_argType && m_deleteArgType) delete[] m_argType;
					if (m_returnType) delete[] m_returnType;
				}

				inline unsigned int hashIndex() const {
					// m_returnType does not contribute to hashIndex!
					unsigned int idx = m_funcIdx ^ ((unsigned int)m_storageTypeIdx << 12) ^ ((unsigned int)m_nbArg << 14);
					for (unsigned int i = 0; i < m_nbArg; i++)
					idx ^= m_argType[i] << (((i+2) & 3) * 8);
					return idx;
				}

				inline unsigned int count() const {
					return m_count;
				}

				inline void addCount(unsigned int count) {
					if ((m_count + count) < count) return; // prevent overflow
					m_count += count;
				}


				inline unsigned int funcIdx() const {return m_funcIdx;}
				inline unsigned short storageTypeIdx() const {return m_storageTypeIdx;}
				inline unsigned short nbArg() const {return m_nbArg;}
				inline unsigned short argType(unsigned int idx) const {
					if (idx >= nbArg()) {
						mv_throw_exception("g2Profiling::entry::argType(): Index out of range", MV_EXCEPTION_ERROR);
						return 0;
					}
					else return m_argType[idx];
				}

				inline void deleteArgType(bool d) {
					m_deleteArgType = d;
				}

				inline unsigned short *returnType() {
					return m_returnType;
				}
				inline unsigned short returnType(int idx) {
					return m_returnType[idx];
				}
				inline unsigned short nbReturnTypes() const {return m_nbReturnTypes;}

				private:
					unsigned int m_funcIdx;
				unsigned short m_storageTypeIdx;
				unsigned short m_nbArg;
				bool m_deleteArgType; // the copy constructor allocates mem for m_argType, the 'custom init' constructor doesn't
				unsigned short *m_argType; // memory allocated with new[], or from stack/caller (in that case, m_deleteArgType is false!) (todo: allocator)
				unsigned int m_count;

				unsigned short m_nbReturnTypes;
				unsigned short *m_returnType; // memory allocated with new[] (or NULL)
			};

			inline bool operator==(const entry &E1, const entry &E2) {
				if (E1.m_nbArg != E2.m_nbArg) return false;
				for (unsigned int i = 0; i < E1.m_nbArg; i++)
				if (E1.m_argType[i] != E2.m_argType[i])
					return false;

				return ((E1.m_funcIdx == E2.m_funcIdx) &&
					(E1.m_storageTypeIdx == E2.m_storageTypeIdx));
			}

			unsigned int g_hashCount = 0; // number of entries in hash table (hash table size is ~doubled when hash table is 'half full')

			class hashBucket {
				public:
					hashBucket() : m_nbEntries(0), m_maxEntries(4) {
					m_entry = new entry*[m_maxEntries];
				}

				~hashBucket() {
					for (unsigned int i = 0; i < m_nbEntries; i++)
					if (m_entry[i]) delete m_entry[i];
					delete[] m_entry;
				}

				entry *findEntry(const entry &E) {
					for (unsigned int i = 0; i < m_nbEntries; i++) {
						if (*(m_entry[i]) == E) {
							return m_entry[i];
						}
					}
					return NULL;
				}


				entry *addEntry(const entry &E) {
					// check if already present:
					{
						entry *X = findEntry(E);
						if (X != NULL) {
							X->addCount(E.count());
							return X;
						}
					}

					// not found: add a new entry:
					{
						// if bucket if full: resize
						if (m_maxEntries == m_nbEntries) {
							m_maxEntries = (m_maxEntries) ? m_maxEntries * 2 : 4;
							entry **oldEntry = m_entry;
							m_entry = new entry*[m_maxEntries];
							memcpy(m_entry, oldEntry, m_nbEntries * sizeof(entry*));
							if (m_entry) {
								delete[] m_entry;
							}
						}

						// add entry to bucket, increment hash count
						entry *X = m_entry[m_nbEntries] = new entry(E);
						m_nbEntries++;
						g_hashCount++;
						return X;
					}
				}

				unsigned int nbEntries() const {return m_nbEntries;}
				inline const entry&operator[](unsigned int idx) {
					if (idx >= m_nbEntries) {
						mv_throw_exception("g2Profiling::hashBucket::operator[](): Index out of range", MV_EXCEPTION_ERROR);
						static entry tmp(0, 0, 0, NULL);
						return tmp;
					}
					else return *(m_entry[idx]);
				}

				private:
				unsigned int m_maxEntries;
				unsigned int m_nbEntries;
				entry **m_entry; // the entries that life in this bucket
			};

			// table of primes, ~*2 each entry ('0' marks the start of the table, '1' marks the end of the table)
			unsigned int g_primes[] = {0, 101, 211, 401, 809, 1601, 3203, 6421, 12809, 25601, 51203, 102407, 204803,  409609,  819229,  1638431,  3276803,  6553621, 1};
			unsigned int g_hashTableSize = 0; // number of buckets in hash table
			hashBucket *g_hashTable = NULL; // memory allocated with new[] (todo: allocator)

			void increaseHashTableSize();
			void reinsertHashTableEntries(unsigned int hashTableSize, hashBucket *hashTable);

			entry *addEntry(const entry &E) {

				if ((g_hashCount+1) * 2 > g_hashTableSize) {
					increaseHashTableSize();
				}

				unsigned int idx = E.hashIndex() % g_hashTableSize;	
				return g_hashTable[idx].addEntry(E);
			}

			entry *findEntry(const entry &E) {
				if (g_hashTableSize == 0) return NULL;
				unsigned int idx = E.hashIndex() % g_hashTableSize;	
				return g_hashTable[idx].findEntry(E);
			}

			void increaseHashTableSize() {
				// find the current idx in the table:
				unsigned int i = 0;
				while ((g_primes[i] != g_hashTableSize) && (g_primes[i] != 1)) i++;

				// get new size (or double capacity when out of primes (unlikely to happen)
				unsigned int newSize = (g_primes[i] == 1) ? g_hashTableSize * 2 : g_primes[i+1];

				// remember old hash talbe:
				unsigned int hashTableSize = g_hashTableSize;
				hashBucket *hashTable = g_hashTable;

				// resize:
				g_hashTableSize = newSize;
				g_hashTable = new hashBucket[g_hashTableSize];

				// reinsert:
				g_hashCount = 0;
				reinsertHashTableEntries(hashTableSize, hashTable); 

				// delete old
				if (hashTable) delete[] hashTable;
			}

			void reinsertHashTableEntries(unsigned int hashTableSize,  hashBucket *hashTable) {
				for (unsigned int i = 0; i < hashTableSize; i++)
				for (unsigned int j = 0; j < hashTable[i].nbEntries(); j++)
				addEntry(hashTable[i][j]);
			}

		} // end of anonymous namespace for profiling code

		int getReturnTypesFromServer(const entry &E, unsigned short returnType[4]);
		// external entry point:
		void profile(unsigned int funcIdx, unsigned short storageTypeIdx, unsigned short nbArg, 
			unsigned short argType[], int nbReturnType, unsigned short returnType[]) {
			// todo: multithreading (lock mutex, etc)
			// mark types as used:
			bool usedGMV = false;
			unsigned short usedGMVtype = 0;
			for (int i = 0; i < nbArg; i++) {
				if (argType[i] < 51)
					g_usedTypes[argType[i]] = true;

				if (argType[i] == MVT_NONE) usedGMV = true; // is this line required?
				if (argType[i] == MVT_MV) {
					usedGMV = true;
					usedGMVtype = argType[i];
				}
			}
			if (usedGMV) { //  a DSL function that is invoked with GMV argument can never be specialized / optimized
				for (int i = 0; i < nbReturnType; i++) {
					returnType[i] = usedGMVtype;
				}
				return;
			}

			entry *E; // E gets set either by findEntry() or by addEntry()
			entry tempEntry(funcIdx, storageTypeIdx, nbArg, argType);
			if ( (E = findEntry(tempEntry)) == NULL) {
				unsigned short nbReturnTypeServer = 0;
				unsigned short returnTypeServer[4] = {(unsigned short)MVT_NONE, (unsigned short)MVT_NONE, (unsigned short)MVT_NONE, (unsigned short)MVT_NONE};
				nbReturnTypeServer = getReturnTypesFromServer(tempEntry, returnTypeServer);


				// ask server for return types
				// add entry
				E = addEntry(entry(funcIdx, storageTypeIdx, nbArg, argType, nbReturnTypeServer, returnTypeServer));
			}

			if (returnType == NULL) return;
			else {
				int maxNbR = (E == NULL) ? 0 : E->nbReturnTypes();
				for (int i = 0; i < nbReturnType; i++) {
					if (i < maxNbR)
						returnType[i] = E->returnType(i);
					else returnType[i] = (unsigned short)MVT_NONE;
				}
			}
			// todo: multithreading (release mutex, etc)
		}

		// external entry point:
		void reset() {
			// todo: multithreading (lock mutex, etc)	
			g_hashCount = 0;
			g_hashTableSize = 0;
			if (g_hashTable) {
				delete[] g_hashTable;
				g_hashTable = NULL;
			}
			// todo: multithreading (release mutex, etc)
		}

		int g_profileNetSocket = -1;
		/** must be called in order for network profiling to work */
		void init(const char *gp2Filename /*= "E:\\ga\\ga_sandbox\\ga_sandbox\\libgasandbox\\e3ga.gp2"*/,
			const char *hostName /* = "localhost" */, int port /* = 7693 */) {
			// todo: multithreading (lock mutex, etc)
			// also todo: IPv6

			if (g_profileNetSocket >= 0) return; // already initialized
			g2Net::init();	

			{ // initialize socket	
				struct hostent *HostEnt;
				struct sockaddr_in ServerAddress;
				struct in_addr InAddr;
				struct in_addr **List;

				if ( (InAddr.s_addr = inet_addr(hostName)) == INADDR_NONE) {
					/* getting address with 'inet_addr()' failed; try a normal 'gethostbyname()' */
					if ( (HostEnt = gethostbyname(hostName)) == NULL)
						throw std::string("Could not gethostbyname() ") + hostName;
					List = (struct in_addr **)HostEnt->h_addr_list;
					InAddr.s_addr = List[0]->s_addr;
				}

				g_profileNetSocket = (int)socket(AF_INET, SOCK_STREAM, 0);
				if (g_profileNetSocket == -1)
					throw std::string("Could not create socket");

				/* setup server address struct; connect to server */
				memset((void*)&ServerAddress, 0, sizeof(ServerAddress));
				ServerAddress.sin_family = AF_INET;
				ServerAddress.sin_addr.s_addr = InAddr.s_addr;
				ServerAddress.sin_port = htons((short)port);
				if (connect(g_profileNetSocket, (struct sockaddr *)&ServerAddress, sizeof(ServerAddress)) == -1) {
					g2Net::closeSocket(&g_profileNetSocket);
					throw std::string("could not connect to server ") + hostName;
				}

				/* disable nagle algorithm */
				g2Net::disableNagle(g_profileNetSocket);
			}

			{ // send opening message:
				const char *gs2Filename = "E:\\ga\\ga_sandbox\\ga_sandbox\\libgasandbox\\e3ga.gs2";
				int n = g2Net::sendN(g_profileNetSocket, (const unsigned char*)gs2Filename, (int)strlen(gs2Filename) + 1);
				n = g2Net::sendN(g_profileNetSocket, (const unsigned char*)gp2Filename, (int)strlen(gp2Filename) + 1);

				unsigned char buf[256];
				bool forReal = true;

				// send number of profile function ids:
				{
					int bufIdx = 0;
					unsigned short nbFunctionsIds = 21;
					bufIdx += g2Net::serialize_ushort(forReal, buf, bufIdx, nbFunctionsIds);
					n = g2Net::sendN(g_profileNetSocket, buf, bufIdx);
				}


				// sen number of specialized types:
				{
					int bufIdx = 0;
					unsigned short nbFunctionsIds = 41;
					bufIdx += g2Net::serialize_ushort(forReal, buf, bufIdx, nbFunctionsIds);
					n = g2Net::sendN(g_profileNetSocket, buf, bufIdx);
				}


				// send know types / ids
				// message format:
				// unsigned int ID
				// char name[], 0
				int nbTypes = 51;
				for (int i = 0; i < nbTypes; i++) {
					// send id;
					int bufIdx = 0;
					bufIdx += g2Net::serialize_uint(forReal, buf, bufIdx, (unsigned int)i);
					n = g2Net::sendN(g_profileNetSocket, buf, bufIdx);

					// send type:
					if (g_typeNames[i]) {
						n = g2Net::sendN(g_profileNetSocket, (const unsigned char*)g_typeNames[i], (int)strlen(g_typeNames[i]) + 1);
					}
					else {
						unsigned char tmp[1] = {0};
						n = g2Net::sendN(g_profileNetSocket, tmp, 1);
					}
				}

				// send 'end of ids' (0xFFFFFFFF)
				{
					int bufIdx = 0;
					bufIdx += g2Net::serialize_uint(forReal, buf, bufIdx, (unsigned int)0xFFFFFFFF);
					n = (int)g2Net::sendN(g_profileNetSocket, buf, bufIdx);
				}

				// wait for one byte ('specification & profile loaded')
				{
					n = g2Net::recvN(g_profileNetSocket, buf, 1);
					if (n < 0) {
						g_profileNetSocket = -1;
						return;
					}
				}
			}
			printf("Connected to profiling server %s:%d\n", hostName, port);
			// todo: multithreading (release mutex, etc)	
		}

		/** gets return type(s) from server, returns nb args */
		int getReturnTypesFromServer(const entry &E, unsigned short returnType[4]) {
			if (g_profileNetSocket < 0) return 0;

			unsigned short nbReturnTypes = 0; // set at the end of the function (read from recv-ed message)

			unsigned char messageBuf[1024];
			unsigned short messageLength = 0;

			// compose message
			{
				// message format:
				// unsigned short messageID = 1
				// unsigned short messageLength
				// unsigned int m_funcIdx
				// unsigned short storageTypeIdx
				// unsigned short nbArg
				// unsigned short argTypes[nbArg]
				int idx = 0;

				{
					bool forReal = true;

					// 'header':
					unsigned short messageID = 1;
					messageLength = 0; // set again later on, when message length is known
					idx += g2Net::serialize_ushort(forReal, messageBuf, idx, messageID);
					int mlIdx = idx; // remember index used for message length so we can overwrite it later on:
					idx += g2Net::serialize_ushort(forReal, messageBuf, idx, messageLength);

					// content:
					idx += g2Net::serialize_uint(forReal, messageBuf, idx, E.funcIdx());
					idx += g2Net::serialize_ushort(forReal, messageBuf, idx, E.storageTypeIdx());
					idx += g2Net::serialize_ushort(forReal, messageBuf, idx, E.nbArg());
					for (unsigned short i = 0; i < E.nbArg(); i++)
					idx += g2Net::serialize_ushort(forReal, messageBuf, idx, E.argType(i));

					// overwrite message length
					messageLength = (unsigned short)idx;
					g2Net::serialize_ushort(forReal, messageBuf, mlIdx, messageLength);

					messageLength = idx;
				}

				// send message	
				{
					int n = g2Net::sendN(g_profileNetSocket, messageBuf, messageLength);
					if (n < 0) throw std::string("getReturnTypesFromServer(): could not send data to net profiling server");
					//			printf("Sent %d\n", n);
				}

				// recv answer:
				{	
					// message format:
					// unsigned short messageID = 2
					// unsigned short messageLength
					// unsigned short nbReturnTypes
					// unsigned short returnType[nbReturnTypes]

					int idx = 0;

					// first 'header' (get ID + length)
					int n = g2Net::recvN(g_profileNetSocket, messageBuf, 4);
					if (n < 0) throw std::string("getReturnTypesFromServer(): could not recv data from profiling server");

					// parse 'header':
					unsigned short messageID, messageLength;
					idx += g2Net::deserialize_ushort(messageBuf, idx, &messageID);
					idx += g2Net::deserialize_ushort(messageBuf, idx, &messageLength);

					if (messageLength < (4 + 2)) throw std::string("getReturnTypesFromServer(): bad message profiling server");

					// get nb return types
					n = g2Net::recvN(g_profileNetSocket, messageBuf + idx, 2);
					if (n < 0) throw std::string("getReturnTypesFromServer(): could not recv data from profiling server");
					idx += g2Net::deserialize_ushort(messageBuf, idx, &nbReturnTypes);

					if (messageLength != (4 + 2 + nbReturnTypes * 2)) 
						throw std::string("getReturnTypesFromServer(): bad message profiling server");
					if (nbReturnTypes > 4)
						throw std::string("getReturnTypesFromServer(): bad message profiling server");

					// get return types
					n = g2Net::recvN(g_profileNetSocket, messageBuf + idx, nbReturnTypes * 2);
					if (n < 0) throw std::string("getReturnTypesFromServer(): could not recv data from profiling server");

					for (int i = 0; i < nbReturnTypes; i++) {
						idx += g2Net::deserialize_ushort(messageBuf, idx, returnType + i);
					}
				}
			}



			return nbReturnTypes;
		}

		void save(const char *filename /*= "E:\\ga\\ga_sandbox\\ga_sandbox\\libgasandbox\\e3ga.gp2"*/, bool append /*= false*/) {
			// when 'net profiling' is enabled, no need to save profile
			return;
		}




	} // end of namespace g2Profiling







	// todo: for all storage formats, generate constants






	// set to 0
	void mv::set() {
		// set grade usage
		gu(0);
		// set type (used for profiling)
		type(MVT_MV);

	}

	// set to copy 
	void mv::set(const mv &arg1) {
		// copy grade usage
		gu(arg1.gu());
		// copy type (used for profiling)
		type(arg1.type());
		// copy coordinates
		mv_memcpy(m_c, arg1.m_c, mv_size[gu()]);

	}

	// set to scalar
	void mv::set(Float scalarVal) {
		// set grade usage
		gu(1);
		// set type (if profile)
		// set type (used for profiling)
		type(MVT_SCALAR);
		// set coordinate
		m_c[0] = scalarVal;

	}


	// set to coordinates 
	void mv::set(unsigned int gradeUsage, const Float *coordinates, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// set coordinates
		mv_memcpy(m_c, coordinates, mv_size[gu()]);

	}


	// set to 1 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 1)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;

	}

	// set to 2 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 2)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;

	}

	// set to 3 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 3)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;

	}

	// set to 4 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 4)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;

	}

	// set to 5 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 5)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;

	}

	// set to 6 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 6)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;

	}

	// set to 7 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 7)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;

	}

	// set to 8 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 8)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;

	}



	// set to e1_t 
	void mv::set(const e1_t & arg1) {

		// set grade usage 
		gu(2);

		// set type (used for profiling)
		type(MVT_E1_T);

		m_c[0] = arg1.m_c[0] ;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;


	}
	// set to e2_t 
	void mv::set(const e2_t & arg1) {

		// set grade usage 
		gu(2);

		// set type (used for profiling)
		type(MVT_E2_T);

		m_c[0] = (Float)0;
		m_c[1] = arg1.m_c[0] ;
		m_c[2] = (Float)0;


	}
	// set to e3_t 
	void mv::set(const e3_t & arg1) {

		// set grade usage 
		gu(2);

		// set type (used for profiling)
		type(MVT_E3_T);

		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = arg1.m_c[0] ;


	}
	// set to scalar 
	void mv::set(const scalar & arg1) {

		// set grade usage 
		gu(1);

		// set type (used for profiling)
		type(MVT_SCALAR);

		m_c[0] = arg1.m_c[0] ;


	}
	// set to vector2D 
	void mv::set(const vector2D & arg1) {

		// set grade usage 
		gu(2);

		// set type (used for profiling)
		type(MVT_VECTOR2D);

		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[1] ;
		m_c[2] = (Float)0;


	}
	// set to vector 
	void mv::set(const vector & arg1) {

		// set grade usage 
		gu(2);

		// set type (used for profiling)
		type(MVT_VECTOR);

		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[1] ;
		m_c[2] = arg1.m_c[2] ;


	}
	// set to bivector 
	void mv::set(const bivector & arg1) {

		// set grade usage 
		gu(4);

		// set type (used for profiling)
		type(MVT_BIVECTOR);

		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[1] ;
		m_c[2] = arg1.m_c[2] ;


	}
	// set to trivector 
	void mv::set(const trivector & arg1) {

		// set grade usage 
		gu(8);

		// set type (used for profiling)
		type(MVT_TRIVECTOR);

		m_c[0] = arg1.m_c[0] ;


	}
	// set to rotor 
	void mv::set(const rotor & arg1) {

		// set grade usage 
		gu(5);

		// set type (used for profiling)
		type(MVT_ROTOR);

		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[1] ;
		m_c[2] = arg1.m_c[2] ;
		m_c[3] = arg1.m_c[3] ;


	}
	// set to __e1_ct__ 
	void mv::set(const __e1_ct__ & arg1) {

		// set grade usage 
		gu(2);

		// set type (used for profiling)
		type(MVT___E1_CT__);

		m_c[0] = (Float)1.0f; 
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;


	}
	// set to __e2_ct__ 
	void mv::set(const __e2_ct__ & arg1) {

		// set grade usage 
		gu(2);

		// set type (used for profiling)
		type(MVT___E2_CT__);

		m_c[0] = (Float)0;
		m_c[1] = (Float)1.0f; 
		m_c[2] = (Float)0;


	}
	// set to __e3_ct__ 
	void mv::set(const __e3_ct__ & arg1) {

		// set grade usage 
		gu(2);

		// set type (used for profiling)
		type(MVT___E3_CT__);

		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = (Float)1.0f; 


	}
	// set to __I3_ct__ 
	void mv::set(const __I3_ct__ & arg1) {

		// set grade usage 
		gu(8);

		// set type (used for profiling)
		type(MVT___I3_CT__);

		m_c[0] = (Float)1.0f; 


	}
	// set to __I3i_ct__ 
	void mv::set(const __I3i_ct__ & arg1) {

		// set grade usage 
		gu(8);

		// set type (used for profiling)
		type(MVT___I3I_CT__);

		m_c[0] = (Float)-1.0f; 


	}
	// set to __syn_smv___e1_e2_e3_e1e2e3 
	void mv::set(const __syn_smv___e1_e2_e3_e1e2e3 & arg1) {

		// set grade usage 
		gu(10);

		// set type (used for profiling)
		type(MVT___SYN_SMV___E1_E2_E3_E1E2E3);

		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[1] ;
		m_c[2] = arg1.m_c[2] ;
		m_c[3] = arg1.m_c[3] ;


	}
	// set to __syn_smv___e1e2f1_0 
	void mv::set(const __syn_smv___e1e2f1_0 & arg1) {

		// set grade usage 
		gu(4);

		// set type (used for profiling)
		type(MVT___SYN_SMV___E1E2F1_0);

		m_c[0] = (Float)1.0f; 
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;


	}
	// set to __syn_smv___e1e2 
	void mv::set(const __syn_smv___e1e2 & arg1) {

		// set grade usage 
		gu(4);

		// set type (used for profiling)
		type(MVT___SYN_SMV___E1E2);

		m_c[0] = arg1.m_c[0] ;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;


	}
	// set to __syn_smv___scalar_e1e2 
	void mv::set(const __syn_smv___scalar_e1e2 & arg1) {

		// set grade usage 
		gu(5);

		// set type (used for profiling)
		type(MVT___SYN_SMV___SCALAR_E1E2);

		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[1] ;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;


	}
	// set to __syn_smv___e3f_1_0 
	void mv::set(const __syn_smv___e3f_1_0 & arg1) {

		// set grade usage 
		gu(2);

		// set type (used for profiling)
		type(MVT___SYN_SMV___E3F_1_0);

		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = (Float)-1.0f; 


	}
	// set to __syn_smv___e1e3_e2e3 
	void mv::set(const __syn_smv___e1e3_e2e3 & arg1) {

		// set grade usage 
		gu(4);

		// set type (used for profiling)
		type(MVT___SYN_SMV___E1E3_E2E3);

		m_c[0] = (Float)0;
		m_c[1] = arg1.m_c[1] ;
		m_c[2] = arg1.m_c[0] * (Float)-1.0;


	}
	// set to __syn_smv___scalar_e1e3_e2e3 
	void mv::set(const __syn_smv___scalar_e1e3_e2e3 & arg1) {

		// set grade usage 
		gu(5);

		// set type (used for profiling)
		type(MVT___SYN_SMV___SCALAR_E1E3_E2E3);

		m_c[0] = arg1.m_c[0] ;
		m_c[1] = (Float)0;
		m_c[2] = arg1.m_c[2] ;
		m_c[3] = arg1.m_c[1] * (Float)-1.0;


	}
	// set to __syn_smv___e1e2_e1e3_e2e3_e1e2e3 
	void mv::set(const __syn_smv___e1e2_e1e3_e2e3_e1e2e3 & arg1) {

		// set grade usage 
		gu(12);

		// set type (used for profiling)
		type(MVT___SYN_SMV___E1E2_E1E3_E2E3_E1E2E3);

		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[2] ;
		m_c[2] = arg1.m_c[1] * (Float)-1.0;
		m_c[3] = arg1.m_c[3] ;


	}
	// set to __syn_smv___e1e3f_1_0 
	void mv::set(const __syn_smv___e1e3f_1_0 & arg1) {

		// set grade usage 
		gu(4);

		// set type (used for profiling)
		type(MVT___SYN_SMV___E1E3F_1_0);

		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = (Float)1.0f; 


	}
	// set to __syn_smv___e1e3 
	void mv::set(const __syn_smv___e1e3 & arg1) {

		// set grade usage 
		gu(4);

		// set type (used for profiling)
		type(MVT___SYN_SMV___E1E3);

		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = arg1.m_c[0] * (Float)-1.0;


	}
	// set to __syn_smv___scalar_e1e3 
	void mv::set(const __syn_smv___scalar_e1e3 & arg1) {

		// set grade usage 
		gu(5);

		// set type (used for profiling)
		type(MVT___SYN_SMV___SCALAR_E1E3);

		m_c[0] = arg1.m_c[0] ;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = arg1.m_c[1] * (Float)-1.0;


	}
	// set to __syn_smv___e2e3f1_0 
	void mv::set(const __syn_smv___e2e3f1_0 & arg1) {

		// set grade usage 
		gu(4);

		// set type (used for profiling)
		type(MVT___SYN_SMV___E2E3F1_0);

		m_c[0] = (Float)0;
		m_c[1] = (Float)1.0f; 
		m_c[2] = (Float)0;


	}
	// set to __syn_smv___e2e3 
	void mv::set(const __syn_smv___e2e3 & arg1) {

		// set grade usage 
		gu(4);

		// set type (used for profiling)
		type(MVT___SYN_SMV___E2E3);

		m_c[0] = (Float)0;
		m_c[1] = arg1.m_c[0] ;
		m_c[2] = (Float)0;


	}
	// set to __syn_smv___scalar_e2e3 
	void mv::set(const __syn_smv___scalar_e2e3 & arg1) {

		// set grade usage 
		gu(5);

		// set type (used for profiling)
		type(MVT___SYN_SMV___SCALAR_E2E3);

		m_c[0] = arg1.m_c[0] ;
		m_c[1] = (Float)0;
		m_c[2] = arg1.m_c[1] ;
		m_c[3] = (Float)0;


	}
	// set to __syn_smv___e2_e3 
	void mv::set(const __syn_smv___e2_e3 & arg1) {

		// set grade usage 
		gu(2);

		// set type (used for profiling)
		type(MVT___SYN_SMV___E2_E3);

		m_c[0] = (Float)0;
		m_c[1] = arg1.m_c[0] ;
		m_c[2] = arg1.m_c[1] ;


	}
	// set to __syn_smv___e1_e3 
	void mv::set(const __syn_smv___e1_e3 & arg1) {

		// set grade usage 
		gu(2);

		// set type (used for profiling)
		type(MVT___SYN_SMV___E1_E3);

		m_c[0] = arg1.m_c[0] ;
		m_c[1] = (Float)0;
		m_c[2] = arg1.m_c[1] ;


	}
	// set to __syn_smv___e2_e3_e1e2e3 
	void mv::set(const __syn_smv___e2_e3_e1e2e3 & arg1) {

		// set grade usage 
		gu(10);

		// set type (used for profiling)
		type(MVT___SYN_SMV___E2_E3_E1E2E3);

		m_c[0] = (Float)0;
		m_c[1] = arg1.m_c[0] ;
		m_c[2] = arg1.m_c[1] ;
		m_c[3] = arg1.m_c[2] ;


	}
	// set to __syn_smv___e1_e3_e1e2e3 
	void mv::set(const __syn_smv___e1_e3_e1e2e3 & arg1) {

		// set grade usage 
		gu(10);

		// set type (used for profiling)
		type(MVT___SYN_SMV___E1_E3_E1E2E3);

		m_c[0] = arg1.m_c[0] ;
		m_c[1] = (Float)0;
		m_c[2] = arg1.m_c[1] ;
		m_c[3] = arg1.m_c[2] ;


	}
	// set to __syn_smv___e1_e2_e1e2e3 
	void mv::set(const __syn_smv___e1_e2_e1e2e3 & arg1) {

		// set grade usage 
		gu(10);

		// set type (used for profiling)
		type(MVT___SYN_SMV___E1_E2_E1E2E3);

		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[1] ;
		m_c[2] = (Float)0;
		m_c[3] = arg1.m_c[2] ;


	}
	// set to __syn_smv___scalar_e1e2_e1e3 
	void mv::set(const __syn_smv___scalar_e1e2_e1e3 & arg1) {

		// set grade usage 
		gu(5);

		// set type (used for profiling)
		type(MVT___SYN_SMV___SCALAR_E1E2_E1E3);

		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[1] ;
		m_c[2] = (Float)0;
		m_c[3] = arg1.m_c[2] * (Float)-1.0;


	}
	// set to __syn_smv___scalar_e1e2_e2e3 
	void mv::set(const __syn_smv___scalar_e1e2_e2e3 & arg1) {

		// set grade usage 
		gu(5);

		// set type (used for profiling)
		type(MVT___SYN_SMV___SCALAR_E1E2_E2E3);

		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[1] ;
		m_c[2] = arg1.m_c[2] ;
		m_c[3] = (Float)0;


	}
	// set to __syn_smv___e2f_1_0 
	void mv::set(const __syn_smv___e2f_1_0 & arg1) {

		// set grade usage 
		gu(2);

		// set type (used for profiling)
		type(MVT___SYN_SMV___E2F_1_0);

		m_c[0] = (Float)0;
		m_c[1] = (Float)-1.0f; 
		m_c[2] = (Float)0;


	}
	// set to __syn_smv___e1e2_e1e3 
	void mv::set(const __syn_smv___e1e2_e1e3 & arg1) {

		// set grade usage 
		gu(4);

		// set type (used for profiling)
		type(MVT___SYN_SMV___E1E2_E1E3);

		m_c[0] = arg1.m_c[0] ;
		m_c[1] = (Float)0;
		m_c[2] = arg1.m_c[1] * (Float)-1.0;


	}
	// set to __syn_smv___e1e2_e2e3 
	void mv::set(const __syn_smv___e1e2_e2e3 & arg1) {

		// set grade usage 
		gu(4);

		// set type (used for profiling)
		type(MVT___SYN_SMV___E1E2_E2E3);

		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[1] ;
		m_c[2] = (Float)0;


	}
	// set to __syn_smv___e1f1_0_e2f1_0 
	void mv::set(const __syn_smv___e1f1_0_e2f1_0 & arg1) {

		// set grade usage 
		gu(2);

		// set type (used for profiling)
		type(MVT___SYN_SMV___E1F1_0_E2F1_0);

		m_c[0] = (Float)1.0f; 
		m_c[1] = (Float)1.0f; 
		m_c[2] = (Float)0;


	}
	// set to __syn_smv___e1f1_0_e2f1_0_e3f1_0 
	void mv::set(const __syn_smv___e1f1_0_e2f1_0_e3f1_0 & arg1) {

		// set grade usage 
		gu(2);

		// set type (used for profiling)
		type(MVT___SYN_SMV___E1F1_0_E2F1_0_E3F1_0);

		m_c[0] = (Float)1.0f; 
		m_c[1] = (Float)1.0f; 
		m_c[2] = (Float)1.0f; 


	}
	// set to __syn_smv___e2_e1f1_0 
	void mv::set(const __syn_smv___e2_e1f1_0 & arg1) {

		// set grade usage 
		gu(2);

		// set type (used for profiling)
		type(MVT___SYN_SMV___E2_E1F1_0);

		m_c[0] = (Float)1.0f; 
		m_c[1] = arg1.m_c[0] ;
		m_c[2] = (Float)0;


	}






	// assign copy
	mv& mv::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}


	// assign scalar
	mv& mv::operator=(Float s) {
		set(s);
		return *this;
	}

	// assign e1_t 
	mv& mv::operator=(const e1_t& arg1) {
		set(arg1);
		return *this;
	}
	// assign e2_t 
	mv& mv::operator=(const e2_t& arg1) {
		set(arg1);
		return *this;
	}
	// assign e3_t 
	mv& mv::operator=(const e3_t& arg1) {
		set(arg1);
		return *this;
	}
	// assign scalar 
	mv& mv::operator=(const scalar& arg1) {
		set(arg1);
		return *this;
	}
	// assign vector2D 
	mv& mv::operator=(const vector2D& arg1) {
		set(arg1);
		return *this;
	}
	// assign vector 
	mv& mv::operator=(const vector& arg1) {
		set(arg1);
		return *this;
	}
	// assign bivector 
	mv& mv::operator=(const bivector& arg1) {
		set(arg1);
		return *this;
	}
	// assign trivector 
	mv& mv::operator=(const trivector& arg1) {
		set(arg1);
		return *this;
	}
	// assign rotor 
	mv& mv::operator=(const rotor& arg1) {
		set(arg1);
		return *this;
	}
	// assign __e1_ct__ 
	mv& mv::operator=(const __e1_ct__& arg1) {
		set(arg1);
		return *this;
	}
	// assign __e2_ct__ 
	mv& mv::operator=(const __e2_ct__& arg1) {
		set(arg1);
		return *this;
	}
	// assign __e3_ct__ 
	mv& mv::operator=(const __e3_ct__& arg1) {
		set(arg1);
		return *this;
	}
	// assign __I3_ct__ 
	mv& mv::operator=(const __I3_ct__& arg1) {
		set(arg1);
		return *this;
	}
	// assign __I3i_ct__ 
	mv& mv::operator=(const __I3i_ct__& arg1) {
		set(arg1);
		return *this;
	}
	// assign __syn_smv___e1_e2_e3_e1e2e3 
	mv& mv::operator=(const __syn_smv___e1_e2_e3_e1e2e3& arg1) {
		set(arg1);
		return *this;
	}
	// assign __syn_smv___e1e2f1_0 
	mv& mv::operator=(const __syn_smv___e1e2f1_0& arg1) {
		set(arg1);
		return *this;
	}
	// assign __syn_smv___e1e2 
	mv& mv::operator=(const __syn_smv___e1e2& arg1) {
		set(arg1);
		return *this;
	}
	// assign __syn_smv___scalar_e1e2 
	mv& mv::operator=(const __syn_smv___scalar_e1e2& arg1) {
		set(arg1);
		return *this;
	}
	// assign __syn_smv___e3f_1_0 
	mv& mv::operator=(const __syn_smv___e3f_1_0& arg1) {
		set(arg1);
		return *this;
	}
	// assign __syn_smv___e1e3_e2e3 
	mv& mv::operator=(const __syn_smv___e1e3_e2e3& arg1) {
		set(arg1);
		return *this;
	}
	// assign __syn_smv___scalar_e1e3_e2e3 
	mv& mv::operator=(const __syn_smv___scalar_e1e3_e2e3& arg1) {
		set(arg1);
		return *this;
	}
	// assign __syn_smv___e1e2_e1e3_e2e3_e1e2e3 
	mv& mv::operator=(const __syn_smv___e1e2_e1e3_e2e3_e1e2e3& arg1) {
		set(arg1);
		return *this;
	}
	// assign __syn_smv___e1e3f_1_0 
	mv& mv::operator=(const __syn_smv___e1e3f_1_0& arg1) {
		set(arg1);
		return *this;
	}
	// assign __syn_smv___e1e3 
	mv& mv::operator=(const __syn_smv___e1e3& arg1) {
		set(arg1);
		return *this;
	}
	// assign __syn_smv___scalar_e1e3 
	mv& mv::operator=(const __syn_smv___scalar_e1e3& arg1) {
		set(arg1);
		return *this;
	}
	// assign __syn_smv___e2e3f1_0 
	mv& mv::operator=(const __syn_smv___e2e3f1_0& arg1) {
		set(arg1);
		return *this;
	}
	// assign __syn_smv___e2e3 
	mv& mv::operator=(const __syn_smv___e2e3& arg1) {
		set(arg1);
		return *this;
	}
	// assign __syn_smv___scalar_e2e3 
	mv& mv::operator=(const __syn_smv___scalar_e2e3& arg1) {
		set(arg1);
		return *this;
	}
	// assign __syn_smv___e2_e3 
	mv& mv::operator=(const __syn_smv___e2_e3& arg1) {
		set(arg1);
		return *this;
	}
	// assign __syn_smv___e1_e3 
	mv& mv::operator=(const __syn_smv___e1_e3& arg1) {
		set(arg1);
		return *this;
	}
	// assign __syn_smv___e2_e3_e1e2e3 
	mv& mv::operator=(const __syn_smv___e2_e3_e1e2e3& arg1) {
		set(arg1);
		return *this;
	}
	// assign __syn_smv___e1_e3_e1e2e3 
	mv& mv::operator=(const __syn_smv___e1_e3_e1e2e3& arg1) {
		set(arg1);
		return *this;
	}
	// assign __syn_smv___e1_e2_e1e2e3 
	mv& mv::operator=(const __syn_smv___e1_e2_e1e2e3& arg1) {
		set(arg1);
		return *this;
	}
	// assign __syn_smv___scalar_e1e2_e1e3 
	mv& mv::operator=(const __syn_smv___scalar_e1e2_e1e3& arg1) {
		set(arg1);
		return *this;
	}
	// assign __syn_smv___scalar_e1e2_e2e3 
	mv& mv::operator=(const __syn_smv___scalar_e1e2_e2e3& arg1) {
		set(arg1);
		return *this;
	}
	// assign __syn_smv___e2f_1_0 
	mv& mv::operator=(const __syn_smv___e2f_1_0& arg1) {
		set(arg1);
		return *this;
	}
	// assign __syn_smv___e1e2_e1e3 
	mv& mv::operator=(const __syn_smv___e1e2_e1e3& arg1) {
		set(arg1);
		return *this;
	}
	// assign __syn_smv___e1e2_e2e3 
	mv& mv::operator=(const __syn_smv___e1e2_e2e3& arg1) {
		set(arg1);
		return *this;
	}
	// assign __syn_smv___e1f1_0_e2f1_0 
	mv& mv::operator=(const __syn_smv___e1f1_0_e2f1_0& arg1) {
		set(arg1);
		return *this;
	}
	// assign __syn_smv___e1f1_0_e2f1_0_e3f1_0 
	mv& mv::operator=(const __syn_smv___e1f1_0_e2f1_0_e3f1_0& arg1) {
		set(arg1);
		return *this;
	}
	// assign __syn_smv___e2_e1f1_0 
	mv& mv::operator=(const __syn_smv___e2_e1f1_0& arg1) {
		set(arg1);
		return *this;
	}




	float mv::largestCoordinate() const {
		int nc = mv_size[gu()], i;
		Float maxC = -1.0, C;

		for (i = 0; i < nc; i++) {
			C = (m_c[i] < (Float)0.0) ? -m_c[i] : m_c[i];
			if (C > maxC) maxC = C;
		}

		return maxC;
	}

	float mv::largestBasisBlade(unsigned int &bm) const {
		int nc = mv_size[gu()];
		Float maxC = -1.0, C;

		int idx = 0;
		int grade = 0;
		int i = 0;

		while (i < nc) {
			if (gu() & (1 << grade)) {
				for (int j = 0; j < mv_gradeSize[grade]; j++) {
					C = (m_c[i] < (Float)0.0) ? -m_c[i] : m_c[i];
					if (C > maxC) {
						maxC = C;
						bm = mv_basisElementBitmapByIndex[idx];
					}
					idx++;
					i++;
				}
			}
			else idx += mv_gradeSize[grade];
			grade++;
		}

		return maxC;
	}








	// set to mv 
	void e1_t::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 0];
		}
		else {
			m_c[0] = (Float)0.0;
		}


	}




	float e1_t::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];

		return maxC;
	}

	float e1_t::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		bm = 1;

		return maxC;
	}




	// set to mv 
	void e2_t::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 1];
		}
		else {
			m_c[0] = (Float)0.0;
		}


	}




	float e2_t::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];

		return maxC;
	}

	float e2_t::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		bm = 2;

		return maxC;
	}




	// set to mv 
	void e3_t::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 2];
		}
		else {
			m_c[0] = (Float)0.0;
		}


	}




	float e3_t::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];

		return maxC;
	}

	float e3_t::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		bm = 4;

		return maxC;
	}




	// set to mv 
	void scalar::set(const mv & arg1) {


		if (arg1.gu() & 1) {
			m_c[0] = arg1.m_c[0];
		}
		else {
			m_c[0] = (Float)0.0;
		}


	}




	float scalar::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];

		return maxC;
	}

	float scalar::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		bm = 0;

		return maxC;
	}




	// set to mv 
	void vector2D::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 0];
			m_c[1] = arg1.m_c[gidx + 1];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
		}


	}




	float vector2D::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float vector2D::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 1;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 2;
		}
		return maxC;
	}




	// set to mv 
	void vector::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 0];
			m_c[1] = arg1.m_c[gidx + 1];
			m_c[2] = arg1.m_c[gidx + 2];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
		}


	}




	float vector::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float vector::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 1;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 2;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 4;
		}
		return maxC;
	}




	// set to mv 
	void bivector::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 3;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[0] = arg1.m_c[gidx + 0];
			m_c[1] = arg1.m_c[gidx + 1];
			m_c[2] = arg1.m_c[gidx + 2];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
		}


	}




	float bivector::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float bivector::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 3;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 6;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 5;
		}
		return maxC;
	}




	// set to mv 
	void trivector::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 3;		}
		else {
		}

		if (arg1.gu() & 4) {
			gidx += 3;		}
		else {
		}

		if (arg1.gu() & 8) {
			m_c[0] = arg1.m_c[gidx + 0];
		}
		else {
			m_c[0] = (Float)0.0;
		}


	}




	float trivector::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];

		return maxC;
	}

	float trivector::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		bm = 7;

		return maxC;
	}




	// set to mv 
	void rotor::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			m_c[0] = arg1.m_c[gidx + 0];
			gidx += 1;		}
		else {
			m_c[0] = (Float)0.0;
		}

		if (arg1.gu() & 2) {
			gidx += 3;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[1] = arg1.m_c[gidx + 0];
			m_c[2] = arg1.m_c[gidx + 1];
			m_c[3] = arg1.m_c[gidx + 2];
		}
		else {
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
		}


	}




	float rotor::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float rotor::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 0;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 3;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 6;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 5;
		}
		return maxC;
	}




	// set to mv 
	void __e1_ct__::set(const mv & arg1) {



	}




	float __e1_ct__::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __e1_ct__::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 1;

		return maxC;
	}




	// set to mv 
	void __e2_ct__::set(const mv & arg1) {



	}




	float __e2_ct__::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __e2_ct__::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 2;

		return maxC;
	}




	// set to mv 
	void __e3_ct__::set(const mv & arg1) {



	}




	float __e3_ct__::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __e3_ct__::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 4;

		return maxC;
	}




	// set to mv 
	void __I3_ct__::set(const mv & arg1) {



	}




	float __I3_ct__::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __I3_ct__::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 7;

		return maxC;
	}




	// set to mv 
	void __I3i_ct__::set(const mv & arg1) {



	}




	float __I3i_ct__::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __I3i_ct__::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 7;

		return maxC;
	}




	// set to mv 
	void __syn_smv___e1_e2_e3_e1e2e3::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 0];
			m_c[1] = arg1.m_c[gidx + 1];
			m_c[2] = arg1.m_c[gidx + 2];
			gidx += 3;		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
		}

		if (arg1.gu() & 4) {
			gidx += 3;		}
		else {
		}

		if (arg1.gu() & 8) {
			m_c[3] = arg1.m_c[gidx + 0];
		}
		else {
			m_c[3] = (Float)0.0;
		}


	}




	float __syn_smv___e1_e2_e3_e1e2e3::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float __syn_smv___e1_e2_e3_e1e2e3::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 1;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 2;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 4;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 7;
		}
		return maxC;
	}




	// set to mv 
	void __syn_smv___e1e2f1_0::set(const mv & arg1) {



	}




	float __syn_smv___e1e2f1_0::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __syn_smv___e1e2f1_0::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 3;

		return maxC;
	}




	// set to mv 
	void __syn_smv___e1e2::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 3;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[0] = arg1.m_c[gidx + 0];
		}
		else {
			m_c[0] = (Float)0.0;
		}


	}




	float __syn_smv___e1e2::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];

		return maxC;
	}

	float __syn_smv___e1e2::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		bm = 3;

		return maxC;
	}




	// set to mv 
	void __syn_smv___scalar_e1e2::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			m_c[0] = arg1.m_c[gidx + 0];
			gidx += 1;		}
		else {
			m_c[0] = (Float)0.0;
		}

		if (arg1.gu() & 2) {
			gidx += 3;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[1] = arg1.m_c[gidx + 0];
		}
		else {
			m_c[1] = (Float)0.0;
		}


	}




	float __syn_smv___scalar_e1e2::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float __syn_smv___scalar_e1e2::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 0;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 3;
		}
		return maxC;
	}




	// set to mv 
	void __syn_smv___e3f_1_0::set(const mv & arg1) {



	}




	float __syn_smv___e3f_1_0::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __syn_smv___e3f_1_0::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 4;

		return maxC;
	}




	// set to mv 
	void __syn_smv___e1e3_e2e3::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 3;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[0] = arg1.m_c[gidx + 2]* (Float)-1.0;
			m_c[1] = arg1.m_c[gidx + 1];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
		}


	}




	float __syn_smv___e1e3_e2e3::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float __syn_smv___e1e3_e2e3::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 5;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 6;
		}
		return maxC;
	}




	// set to mv 
	void __syn_smv___scalar_e1e3_e2e3::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			m_c[0] = arg1.m_c[gidx + 0];
			gidx += 1;		}
		else {
			m_c[0] = (Float)0.0;
		}

		if (arg1.gu() & 2) {
			gidx += 3;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[1] = arg1.m_c[gidx + 2]* (Float)-1.0;
			m_c[2] = arg1.m_c[gidx + 1];
		}
		else {
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
		}


	}




	float __syn_smv___scalar_e1e3_e2e3::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float __syn_smv___scalar_e1e3_e2e3::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 0;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 5;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 6;
		}
		return maxC;
	}




	// set to mv 
	void __syn_smv___e1e2_e1e3_e2e3_e1e2e3::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 3;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[0] = arg1.m_c[gidx + 0];
			m_c[1] = arg1.m_c[gidx + 2]* (Float)-1.0;
			m_c[2] = arg1.m_c[gidx + 1];
			gidx += 3;		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
		}

		if (arg1.gu() & 8) {
			m_c[3] = arg1.m_c[gidx + 0];
		}
		else {
			m_c[3] = (Float)0.0;
		}


	}




	float __syn_smv___e1e2_e1e3_e2e3_e1e2e3::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float __syn_smv___e1e2_e1e3_e2e3_e1e2e3::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 3;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 5;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 6;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 7;
		}
		return maxC;
	}




	// set to mv 
	void __syn_smv___e1e3f_1_0::set(const mv & arg1) {



	}




	float __syn_smv___e1e3f_1_0::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __syn_smv___e1e3f_1_0::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 5;

		return maxC;
	}




	// set to mv 
	void __syn_smv___e1e3::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 3;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[0] = arg1.m_c[gidx + 2]* (Float)-1.0;
		}
		else {
			m_c[0] = (Float)0.0;
		}


	}




	float __syn_smv___e1e3::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];

		return maxC;
	}

	float __syn_smv___e1e3::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		bm = 5;

		return maxC;
	}




	// set to mv 
	void __syn_smv___scalar_e1e3::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			m_c[0] = arg1.m_c[gidx + 0];
			gidx += 1;		}
		else {
			m_c[0] = (Float)0.0;
		}

		if (arg1.gu() & 2) {
			gidx += 3;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[1] = arg1.m_c[gidx + 2]* (Float)-1.0;
		}
		else {
			m_c[1] = (Float)0.0;
		}


	}




	float __syn_smv___scalar_e1e3::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float __syn_smv___scalar_e1e3::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 0;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 5;
		}
		return maxC;
	}




	// set to mv 
	void __syn_smv___e2e3f1_0::set(const mv & arg1) {



	}




	float __syn_smv___e2e3f1_0::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __syn_smv___e2e3f1_0::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 6;

		return maxC;
	}




	// set to mv 
	void __syn_smv___e2e3::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 3;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[0] = arg1.m_c[gidx + 1];
		}
		else {
			m_c[0] = (Float)0.0;
		}


	}




	float __syn_smv___e2e3::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];

		return maxC;
	}

	float __syn_smv___e2e3::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		bm = 6;

		return maxC;
	}




	// set to mv 
	void __syn_smv___scalar_e2e3::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			m_c[0] = arg1.m_c[gidx + 0];
			gidx += 1;		}
		else {
			m_c[0] = (Float)0.0;
		}

		if (arg1.gu() & 2) {
			gidx += 3;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[1] = arg1.m_c[gidx + 1];
		}
		else {
			m_c[1] = (Float)0.0;
		}


	}




	float __syn_smv___scalar_e2e3::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float __syn_smv___scalar_e2e3::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 0;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 6;
		}
		return maxC;
	}




	// set to mv 
	void __syn_smv___e2_e3::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 1];
			m_c[1] = arg1.m_c[gidx + 2];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
		}


	}




	float __syn_smv___e2_e3::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float __syn_smv___e2_e3::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 2;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 4;
		}
		return maxC;
	}




	// set to mv 
	void __syn_smv___e1_e3::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 0];
			m_c[1] = arg1.m_c[gidx + 2];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
		}


	}




	float __syn_smv___e1_e3::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float __syn_smv___e1_e3::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 1;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 4;
		}
		return maxC;
	}




	// set to mv 
	void __syn_smv___e2_e3_e1e2e3::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 1];
			m_c[1] = arg1.m_c[gidx + 2];
			gidx += 3;		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
		}

		if (arg1.gu() & 4) {
			gidx += 3;		}
		else {
		}

		if (arg1.gu() & 8) {
			m_c[2] = arg1.m_c[gidx + 0];
		}
		else {
			m_c[2] = (Float)0.0;
		}


	}




	float __syn_smv___e2_e3_e1e2e3::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float __syn_smv___e2_e3_e1e2e3::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 2;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 4;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 7;
		}
		return maxC;
	}




	// set to mv 
	void __syn_smv___e1_e3_e1e2e3::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 0];
			m_c[1] = arg1.m_c[gidx + 2];
			gidx += 3;		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
		}

		if (arg1.gu() & 4) {
			gidx += 3;		}
		else {
		}

		if (arg1.gu() & 8) {
			m_c[2] = arg1.m_c[gidx + 0];
		}
		else {
			m_c[2] = (Float)0.0;
		}


	}




	float __syn_smv___e1_e3_e1e2e3::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float __syn_smv___e1_e3_e1e2e3::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 1;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 4;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 7;
		}
		return maxC;
	}




	// set to mv 
	void __syn_smv___e1_e2_e1e2e3::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 0];
			m_c[1] = arg1.m_c[gidx + 1];
			gidx += 3;		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
		}

		if (arg1.gu() & 4) {
			gidx += 3;		}
		else {
		}

		if (arg1.gu() & 8) {
			m_c[2] = arg1.m_c[gidx + 0];
		}
		else {
			m_c[2] = (Float)0.0;
		}


	}




	float __syn_smv___e1_e2_e1e2e3::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float __syn_smv___e1_e2_e1e2e3::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 1;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 2;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 7;
		}
		return maxC;
	}




	// set to mv 
	void __syn_smv___scalar_e1e2_e1e3::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			m_c[0] = arg1.m_c[gidx + 0];
			gidx += 1;		}
		else {
			m_c[0] = (Float)0.0;
		}

		if (arg1.gu() & 2) {
			gidx += 3;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[1] = arg1.m_c[gidx + 0];
			m_c[2] = arg1.m_c[gidx + 2]* (Float)-1.0;
		}
		else {
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
		}


	}




	float __syn_smv___scalar_e1e2_e1e3::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float __syn_smv___scalar_e1e2_e1e3::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 0;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 3;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 5;
		}
		return maxC;
	}




	// set to mv 
	void __syn_smv___scalar_e1e2_e2e3::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			m_c[0] = arg1.m_c[gidx + 0];
			gidx += 1;		}
		else {
			m_c[0] = (Float)0.0;
		}

		if (arg1.gu() & 2) {
			gidx += 3;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[1] = arg1.m_c[gidx + 0];
			m_c[2] = arg1.m_c[gidx + 1];
		}
		else {
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
		}


	}




	float __syn_smv___scalar_e1e2_e2e3::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float __syn_smv___scalar_e1e2_e2e3::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 0;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 3;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 6;
		}
		return maxC;
	}




	// set to mv 
	void __syn_smv___e2f_1_0::set(const mv & arg1) {



	}




	float __syn_smv___e2f_1_0::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __syn_smv___e2f_1_0::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 2;

		return maxC;
	}




	// set to mv 
	void __syn_smv___e1e2_e1e3::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 3;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[0] = arg1.m_c[gidx + 0];
			m_c[1] = arg1.m_c[gidx + 2]* (Float)-1.0;
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
		}


	}




	float __syn_smv___e1e2_e1e3::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float __syn_smv___e1e2_e1e3::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 3;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 5;
		}
		return maxC;
	}




	// set to mv 
	void __syn_smv___e1e2_e2e3::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 3;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[0] = arg1.m_c[gidx + 0];
			m_c[1] = arg1.m_c[gidx + 1];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
		}


	}




	float __syn_smv___e1e2_e2e3::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float __syn_smv___e1e2_e2e3::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 3;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 6;
		}
		return maxC;
	}




	// set to mv 
	void __syn_smv___e1f1_0_e2f1_0::set(const mv & arg1) {



	}




	float __syn_smv___e1f1_0_e2f1_0::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __syn_smv___e1f1_0_e2f1_0::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 2;

		return maxC;
	}




	// set to mv 
	void __syn_smv___e1f1_0_e2f1_0_e3f1_0::set(const mv & arg1) {



	}




	float __syn_smv___e1f1_0_e2f1_0_e3f1_0::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __syn_smv___e1f1_0_e2f1_0_e3f1_0::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 4;

		return maxC;
	}




	// set to mv 
	void __syn_smv___e2_e1f1_0::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 1];
		}
		else {
			m_c[0] = (Float)0.0;
		}


	}




	float __syn_smv___e2_e1f1_0::largestCoordinate() const {

		Float maxC = (Float)1.0f, C;

		C = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float __syn_smv___e2_e1f1_0::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f, C;
		bm = 1;

		C = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		if (C > maxC) {
			maxC = C;
			bm = 2;
		}
		return maxC;
	}






	// set to identity 'I'
	void om::set() {
		// simplify forward call to set(scalar)
		set(1.0);
	}

	// set to copy
	void om::set(const om &arg1) {
		mv_memcpy(m_c, arg1.m_c, 19);
		// set type (used for profiling)
		type(OMT_OM);
	}

	// set to scalar
	void om::set(Float scalarVal) {
		e3ga::__G2_GENERATED__::set(*this, vector(vector_e1_e2_e3, scalarVal, (Float)0, (Float)0), vector(vector_e1_e2_e3, (Float)0, scalarVal, (Float)0), vector(vector_e1_e2_e3, (Float)0, (Float)0, scalarVal));
		// set type (used for profiling)
		type(OMT_OM);
	}

	// set to coordinates 
	void om::set(const Float *coordinates) {
		mv_memcpy(m_c, coordinates, 19);
		// set type (used for profiling)
		type(OMT_OM);
	}

	// set from basis vectors array
	void om::set(const vector *vectors) {
		e3ga::__G2_GENERATED__::set(*this, vectors[0], vectors[1], vectors[2]);
		// set type (used for profiling)
		type(OMT_OM);
	}


	// set from basis vectors 
	void om::set(const vector & image_of_e1, const vector & image_of_e2, const vector & image_of_e3) {
		e3ga::__G2_GENERATED__::set(*this, image_of_e1, image_of_e2, image_of_e3);
		// set type (used for profiling)
		type(OMT_OM);
	}


	// set by coordinates, transpose
	void om::set(const Float *coordinates, bool transpose) {
		if (transpose) {
			m_c[0] = coordinates[0];
			m_c[3] = coordinates[1];
			m_c[6] = coordinates[2];
			m_c[1] = coordinates[3];
			m_c[4] = coordinates[4];
			m_c[7] = coordinates[5];
			m_c[2] = coordinates[6];
			m_c[5] = coordinates[7];
			m_c[8] = coordinates[8];
			m_c[9] = coordinates[9];
			m_c[12] = coordinates[10];
			m_c[15] = coordinates[11];
			m_c[10] = coordinates[12];
			m_c[13] = coordinates[13];
			m_c[16] = coordinates[14];
			m_c[11] = coordinates[15];
			m_c[14] = coordinates[16];
			m_c[17] = coordinates[17];
			m_c[18] = coordinates[18];
			// set type (used for profiling)
			type(OMT_OM);
		}
		else set(coordinates);
	}




	// assign copy
	om &om::operator=(const om &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar (creates scalar * 'I' outermorphism)
	om &om::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}

	/// assign specialization:






	// G2 functions:
	mv lcont(const mv& x, const mv& y) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type(), y.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)1), ((unsigned short)-1), ((unsigned short)2), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		mv __temp_var_1__;
		float __tmp_coord_array_1__[8] ;
		mv_zero(__tmp_coord_array_1__, 8);
		const float* __y_xpd__[4] ;
		y.expand(__y_xpd__, true);
		const float* __x_xpd__[4] ;
		x.expand(__x_xpd__, true);
		if (((y.m_gu & 1) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_1__[0] += (__x_xpd__[0][0] * __y_xpd__[0][0]);

			}

		}
		if (((y.m_gu & 2) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_1__[1] += (__y_xpd__[1][0] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[2] += (__y_xpd__[1][1] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[3] += (__y_xpd__[1][2] * __x_xpd__[0][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_1__[0] += ((__x_xpd__[1][2] * __y_xpd__[1][2]) + (__x_xpd__[1][0] * __y_xpd__[1][0]) + (__x_xpd__[1][1] * __y_xpd__[1][1]));

			}

		}
		if (((y.m_gu & 4) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_1__[4] += (__y_xpd__[2][0] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[5] += (__y_xpd__[2][1] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[6] += (__y_xpd__[2][2] * __x_xpd__[0][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_1__[1] += ((__x_xpd__[1][2] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[2][0]));
				__tmp_coord_array_1__[2] += ((__x_xpd__[1][0] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[2][1]));
				__tmp_coord_array_1__[3] += ((-1.0f * __x_xpd__[1][0] * __y_xpd__[2][2]) + (__x_xpd__[1][1] * __y_xpd__[2][1]));

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_1__[0] += ((-1.0f * __x_xpd__[2][0] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[2][2]));

			}

		}
		if (((y.m_gu & 8) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_1__[7] += (__y_xpd__[3][0] * __x_xpd__[0][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_1__[4] += (__x_xpd__[1][2] * __y_xpd__[3][0]);
				__tmp_coord_array_1__[5] += (__x_xpd__[1][0] * __y_xpd__[3][0]);
				__tmp_coord_array_1__[6] += (__x_xpd__[1][1] * __y_xpd__[3][0]);

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_1__[1] += (-1.0f * __x_xpd__[2][1] * __y_xpd__[3][0]);
				__tmp_coord_array_1__[2] += (-1.0f * __x_xpd__[2][2] * __y_xpd__[3][0]);
				__tmp_coord_array_1__[3] += (-1.0f * __x_xpd__[2][0] * __y_xpd__[3][0]);

			}
			if (((x.m_gu & 8) != 0)) {
				__tmp_coord_array_1__[0] += (-1.0f * __x_xpd__[3][0] * __y_xpd__[3][0]);

			}

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_1__);
		__temp_var_1__.type(((g2Type)((short)__returnTypes__[0])));
		return __temp_var_1__;
	}
	scalar scp(const mv& x, const mv& y) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type(), y.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)2), ((unsigned short)-1), ((unsigned short)2), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		scalar __temp_var_1__;
		const float* __y_xpd__[4] ;
		y.expand(__y_xpd__, true);
		const float* __x_xpd__[4] ;
		x.expand(__x_xpd__, true);
		if (((y.m_gu & 1) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__temp_var_1__.m_c[0] += (__x_xpd__[0][0] * __y_xpd__[0][0]);

			}

		}
		if (((y.m_gu & 2) != 0)) {
			if (((x.m_gu & 2) != 0)) {
				__temp_var_1__.m_c[0] += ((__x_xpd__[1][0] * __y_xpd__[1][0]) + (__x_xpd__[1][2] * __y_xpd__[1][2]) + (__x_xpd__[1][1] * __y_xpd__[1][1]));

			}

		}
		if (((y.m_gu & 4) != 0)) {
			if (((x.m_gu & 4) != 0)) {
				__temp_var_1__.m_c[0] += ((-1.0f * __x_xpd__[2][0] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[2][1]));

			}

		}
		if (((y.m_gu & 8) != 0)) {
			if (((x.m_gu & 8) != 0)) {
				__temp_var_1__.m_c[0] += (-1.0f * __x_xpd__[3][0] * __y_xpd__[3][0]);

			}

		}
		return __temp_var_1__;
	}
	mv gp(const mv& x, const mv& y) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type(), y.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)3), ((unsigned short)-1), ((unsigned short)2), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		mv __temp_var_1__;
		float __tmp_coord_array_2__[8] ;
		mv_zero(__tmp_coord_array_2__, 8);
		const float* __x_xpd__[4] ;
		x.expand(__x_xpd__, true);
		const float* __y_xpd__[4] ;
		y.expand(__y_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__tmp_coord_array_2__[0] += (__x_xpd__[0][0] * __y_xpd__[0][0]);

			}
			if (((y.m_gu & 2) != 0)) {
				__tmp_coord_array_2__[1] += (__x_xpd__[0][0] * __y_xpd__[1][0]);
				__tmp_coord_array_2__[2] += (__x_xpd__[0][0] * __y_xpd__[1][1]);
				__tmp_coord_array_2__[3] += (__x_xpd__[0][0] * __y_xpd__[1][2]);

			}
			if (((y.m_gu & 4) != 0)) {
				__tmp_coord_array_2__[4] += (__x_xpd__[0][0] * __y_xpd__[2][0]);
				__tmp_coord_array_2__[5] += (__x_xpd__[0][0] * __y_xpd__[2][1]);
				__tmp_coord_array_2__[6] += (__x_xpd__[0][0] * __y_xpd__[2][2]);

			}
			if (((y.m_gu & 8) != 0)) {
				__tmp_coord_array_2__[7] += (__x_xpd__[0][0] * __y_xpd__[3][0]);

			}

		}
		if (((x.m_gu & 2) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__tmp_coord_array_2__[1] += (__x_xpd__[1][0] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[2] += (__x_xpd__[1][1] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[3] += (__x_xpd__[1][2] * __y_xpd__[0][0]);

			}
			if (((y.m_gu & 2) != 0)) {
				__tmp_coord_array_2__[0] += ((__x_xpd__[1][1] * __y_xpd__[1][1]) + (__x_xpd__[1][2] * __y_xpd__[1][2]) + (__x_xpd__[1][0] * __y_xpd__[1][0]));
				__tmp_coord_array_2__[4] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[1][0]) + (__x_xpd__[1][0] * __y_xpd__[1][1]));
				__tmp_coord_array_2__[5] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[1][1]) + (__x_xpd__[1][1] * __y_xpd__[1][2]));
				__tmp_coord_array_2__[6] += ((__x_xpd__[1][2] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[1][2]));

			}
			if (((y.m_gu & 4) != 0)) {
				__tmp_coord_array_2__[1] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[2][0]) + (__x_xpd__[1][2] * __y_xpd__[2][2]));
				__tmp_coord_array_2__[2] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[2][1]) + (__x_xpd__[1][0] * __y_xpd__[2][0]));
				__tmp_coord_array_2__[3] += ((-1.0f * __x_xpd__[1][0] * __y_xpd__[2][2]) + (__x_xpd__[1][1] * __y_xpd__[2][1]));
				__tmp_coord_array_2__[7] += ((__x_xpd__[1][0] * __y_xpd__[2][1]) + (__x_xpd__[1][2] * __y_xpd__[2][0]) + (__x_xpd__[1][1] * __y_xpd__[2][2]));

			}
			if (((y.m_gu & 8) != 0)) {
				__tmp_coord_array_2__[4] += (__x_xpd__[1][2] * __y_xpd__[3][0]);
				__tmp_coord_array_2__[5] += (__x_xpd__[1][0] * __y_xpd__[3][0]);
				__tmp_coord_array_2__[6] += (__x_xpd__[1][1] * __y_xpd__[3][0]);

			}

		}
		if (((x.m_gu & 4) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__tmp_coord_array_2__[4] += (__x_xpd__[2][0] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[5] += (__x_xpd__[2][1] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[6] += (__x_xpd__[2][2] * __y_xpd__[0][0]);

			}
			if (((y.m_gu & 2) != 0)) {
				__tmp_coord_array_2__[1] += ((-1.0f * __x_xpd__[2][2] * __y_xpd__[1][2]) + (__x_xpd__[2][0] * __y_xpd__[1][1]));
				__tmp_coord_array_2__[2] += ((__x_xpd__[2][1] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[1][0]));
				__tmp_coord_array_2__[3] += ((-1.0f * __x_xpd__[2][1] * __y_xpd__[1][1]) + (__x_xpd__[2][2] * __y_xpd__[1][0]));
				__tmp_coord_array_2__[7] += ((__x_xpd__[2][2] * __y_xpd__[1][1]) + (__x_xpd__[2][1] * __y_xpd__[1][0]) + (__x_xpd__[2][0] * __y_xpd__[1][2]));

			}
			if (((y.m_gu & 4) != 0)) {
				__tmp_coord_array_2__[0] += ((-1.0f * __x_xpd__[2][0] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[2][1]));
				__tmp_coord_array_2__[4] += ((-1.0f * __x_xpd__[2][1] * __y_xpd__[2][2]) + (__x_xpd__[2][2] * __y_xpd__[2][1]));
				__tmp_coord_array_2__[5] += ((__x_xpd__[2][0] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[2][0]));
				__tmp_coord_array_2__[6] += ((-1.0f * __x_xpd__[2][0] * __y_xpd__[2][1]) + (__x_xpd__[2][1] * __y_xpd__[2][0]));

			}
			if (((y.m_gu & 8) != 0)) {
				__tmp_coord_array_2__[1] += (-1.0f * __x_xpd__[2][1] * __y_xpd__[3][0]);
				__tmp_coord_array_2__[2] += (-1.0f * __x_xpd__[2][2] * __y_xpd__[3][0]);
				__tmp_coord_array_2__[3] += (-1.0f * __x_xpd__[2][0] * __y_xpd__[3][0]);

			}

		}
		if (((x.m_gu & 8) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__tmp_coord_array_2__[7] += (__x_xpd__[3][0] * __y_xpd__[0][0]);

			}
			if (((y.m_gu & 2) != 0)) {
				__tmp_coord_array_2__[4] += (__x_xpd__[3][0] * __y_xpd__[1][2]);
				__tmp_coord_array_2__[5] += (__x_xpd__[3][0] * __y_xpd__[1][0]);
				__tmp_coord_array_2__[6] += (__x_xpd__[3][0] * __y_xpd__[1][1]);

			}
			if (((y.m_gu & 4) != 0)) {
				__tmp_coord_array_2__[1] += (-1.0f * __x_xpd__[3][0] * __y_xpd__[2][1]);
				__tmp_coord_array_2__[2] += (-1.0f * __x_xpd__[3][0] * __y_xpd__[2][2]);
				__tmp_coord_array_2__[3] += (-1.0f * __x_xpd__[3][0] * __y_xpd__[2][0]);

			}
			if (((y.m_gu & 8) != 0)) {
				__tmp_coord_array_2__[0] += (-1.0f * __x_xpd__[3][0] * __y_xpd__[3][0]);

			}

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_2__);
		__temp_var_1__.type(((g2Type)((short)__returnTypes__[0])));
		return __temp_var_1__;
	}
	mv op(const mv& x, const mv& y) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type(), y.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)4), ((unsigned short)-1), ((unsigned short)2), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		mv __temp_var_1__;
		float __tmp_coord_array_3__[8] ;
		mv_zero(__tmp_coord_array_3__, 8);
		const float* __x_xpd__[4] ;
		x.expand(__x_xpd__, true);
		const float* __y_xpd__[4] ;
		y.expand(__y_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__tmp_coord_array_3__[0] += (__x_xpd__[0][0] * __y_xpd__[0][0]);

			}
			if (((y.m_gu & 2) != 0)) {
				__tmp_coord_array_3__[1] += (__x_xpd__[0][0] * __y_xpd__[1][0]);
				__tmp_coord_array_3__[2] += (__x_xpd__[0][0] * __y_xpd__[1][1]);
				__tmp_coord_array_3__[3] += (__x_xpd__[0][0] * __y_xpd__[1][2]);

			}
			if (((y.m_gu & 4) != 0)) {
				__tmp_coord_array_3__[4] += (__x_xpd__[0][0] * __y_xpd__[2][0]);
				__tmp_coord_array_3__[5] += (__x_xpd__[0][0] * __y_xpd__[2][1]);
				__tmp_coord_array_3__[6] += (__x_xpd__[0][0] * __y_xpd__[2][2]);

			}
			if (((y.m_gu & 8) != 0)) {
				__tmp_coord_array_3__[7] += (__x_xpd__[0][0] * __y_xpd__[3][0]);

			}

		}
		if (((x.m_gu & 2) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__tmp_coord_array_3__[1] += (__x_xpd__[1][0] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[2] += (__x_xpd__[1][1] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[3] += (__x_xpd__[1][2] * __y_xpd__[0][0]);

			}
			if (((y.m_gu & 2) != 0)) {
				__tmp_coord_array_3__[4] += ((__x_xpd__[1][0] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[1][0]));
				__tmp_coord_array_3__[5] += ((__x_xpd__[1][1] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[1][1]));
				__tmp_coord_array_3__[6] += ((__x_xpd__[1][2] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[1][2]));

			}
			if (((y.m_gu & 4) != 0)) {
				__tmp_coord_array_3__[7] += ((__x_xpd__[1][0] * __y_xpd__[2][1]) + (__x_xpd__[1][1] * __y_xpd__[2][2]) + (__x_xpd__[1][2] * __y_xpd__[2][0]));

			}

		}
		if (((x.m_gu & 4) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__tmp_coord_array_3__[4] += (__x_xpd__[2][0] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[5] += (__x_xpd__[2][1] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[6] += (__x_xpd__[2][2] * __y_xpd__[0][0]);

			}
			if (((y.m_gu & 2) != 0)) {
				__tmp_coord_array_3__[7] += ((__x_xpd__[2][2] * __y_xpd__[1][1]) + (__x_xpd__[2][0] * __y_xpd__[1][2]) + (__x_xpd__[2][1] * __y_xpd__[1][0]));

			}

		}
		if (((x.m_gu & 8) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__tmp_coord_array_3__[7] += (__x_xpd__[3][0] * __y_xpd__[0][0]);

			}

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_3__);
		__temp_var_1__.type(((g2Type)((short)__returnTypes__[0])));
		return __temp_var_1__;
	}
	mv add(const mv& x, const mv& y) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type(), y.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)5), ((unsigned short)-1), ((unsigned short)2), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		mv __temp_var_1__;
		float __tmp_coord_array_4__[8] ;
		mv_zero(__tmp_coord_array_4__, 8);
		const float* __x_xpd__[4] ;
		x.expand(__x_xpd__, true);
		const float* __y_xpd__[4] ;
		y.expand(__y_xpd__, true);
		if (((y.m_gu & 1) != 0)) {
			__tmp_coord_array_4__[0] += __y_xpd__[0][0];

		}
		if (((y.m_gu & 2) != 0)) {
			__tmp_coord_array_4__[1] += __y_xpd__[1][0];
			__tmp_coord_array_4__[2] += __y_xpd__[1][1];
			__tmp_coord_array_4__[3] += __y_xpd__[1][2];

		}
		if (((y.m_gu & 4) != 0)) {
			__tmp_coord_array_4__[4] += __y_xpd__[2][0];
			__tmp_coord_array_4__[5] += __y_xpd__[2][1];
			__tmp_coord_array_4__[6] += __y_xpd__[2][2];

		}
		if (((y.m_gu & 8) != 0)) {
			__tmp_coord_array_4__[7] += __y_xpd__[3][0];

		}
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_4__[0] += __x_xpd__[0][0];

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_4__[1] += __x_xpd__[1][0];
			__tmp_coord_array_4__[2] += __x_xpd__[1][1];
			__tmp_coord_array_4__[3] += __x_xpd__[1][2];

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_4__[4] += __x_xpd__[2][0];
			__tmp_coord_array_4__[5] += __x_xpd__[2][1];
			__tmp_coord_array_4__[6] += __x_xpd__[2][2];

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_4__[7] += __x_xpd__[3][0];

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_4__);
		__temp_var_1__.type(((g2Type)((short)__returnTypes__[0])));
		return __temp_var_1__;
	}
	mv subtract(const mv& x, const mv& y) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type(), y.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)6), ((unsigned short)-1), ((unsigned short)2), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		mv __temp_var_1__;
		float __tmp_coord_array_5__[8] ;
		mv_zero(__tmp_coord_array_5__, 8);
		const float* __x_xpd__[4] ;
		x.expand(__x_xpd__, true);
		const float* __y_xpd__[4] ;
		y.expand(__y_xpd__, true);
		if (((y.m_gu & 1) != 0)) {
			__tmp_coord_array_5__[0] += (-1.0f * __y_xpd__[0][0]);

		}
		if (((y.m_gu & 2) != 0)) {
			__tmp_coord_array_5__[1] += (-1.0f * __y_xpd__[1][0]);
			__tmp_coord_array_5__[2] += (-1.0f * __y_xpd__[1][1]);
			__tmp_coord_array_5__[3] += (-1.0f * __y_xpd__[1][2]);

		}
		if (((y.m_gu & 4) != 0)) {
			__tmp_coord_array_5__[4] += (-1.0f * __y_xpd__[2][0]);
			__tmp_coord_array_5__[5] += (-1.0f * __y_xpd__[2][1]);
			__tmp_coord_array_5__[6] += (-1.0f * __y_xpd__[2][2]);

		}
		if (((y.m_gu & 8) != 0)) {
			__tmp_coord_array_5__[7] += (-1.0f * __y_xpd__[3][0]);

		}
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_5__[0] += __x_xpd__[0][0];

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_5__[1] += __x_xpd__[1][0];
			__tmp_coord_array_5__[2] += __x_xpd__[1][1];
			__tmp_coord_array_5__[3] += __x_xpd__[1][2];

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_5__[4] += __x_xpd__[2][0];
			__tmp_coord_array_5__[5] += __x_xpd__[2][1];
			__tmp_coord_array_5__[6] += __x_xpd__[2][2];

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_5__[7] += __x_xpd__[3][0];

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_5__);
		__temp_var_1__.type(((g2Type)((short)__returnTypes__[0])));
		return __temp_var_1__;
	}
	scalar norm_e2(const mv& x) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)7), ((unsigned short)-1), ((unsigned short)1), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		scalar __temp_var_1__;
		const float* __x_xpd__[4] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__temp_var_1__.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__temp_var_1__.m_c[0] += ((__x_xpd__[1][1] * __x_xpd__[1][1]) + (__x_xpd__[1][0] * __x_xpd__[1][0]) + (__x_xpd__[1][2] * __x_xpd__[1][2]));

		}
		if (((x.m_gu & 4) != 0)) {
			__temp_var_1__.m_c[0] += ((__x_xpd__[2][0] * __x_xpd__[2][0]) + (__x_xpd__[2][1] * __x_xpd__[2][1]) + (__x_xpd__[2][2] * __x_xpd__[2][2]));

		}
		if (((x.m_gu & 8) != 0)) {
			__temp_var_1__.m_c[0] += (__x_xpd__[3][0] * __x_xpd__[3][0]);

		}
		return __temp_var_1__;
	}
	scalar norm_e(const mv& x) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)8), ((unsigned short)-1), ((unsigned short)1), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		scalar e2;
		const float* __x_xpd__[4] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			e2.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			e2.m_c[0] += ((__x_xpd__[1][2] * __x_xpd__[1][2]) + (__x_xpd__[1][0] * __x_xpd__[1][0]) + (__x_xpd__[1][1] * __x_xpd__[1][1]));

		}
		if (((x.m_gu & 4) != 0)) {
			e2.m_c[0] += ((__x_xpd__[2][2] * __x_xpd__[2][2]) + (__x_xpd__[2][1] * __x_xpd__[2][1]) + (__x_xpd__[2][0] * __x_xpd__[2][0]));

		}
		if (((x.m_gu & 8) != 0)) {
			e2.m_c[0] += (__x_xpd__[3][0] * __x_xpd__[3][0]);

		}
		return scalar(scalar_scalar, sqrt(e2.m_c[0]));
	}
	mv unit_e(const mv& x) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)9), ((unsigned short)-1), ((unsigned short)1), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		scalar e2;
		const float* __x_xpd__[4] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			e2.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			e2.m_c[0] += ((__x_xpd__[1][2] * __x_xpd__[1][2]) + (__x_xpd__[1][0] * __x_xpd__[1][0]) + (__x_xpd__[1][1] * __x_xpd__[1][1]));

		}
		if (((x.m_gu & 4) != 0)) {
			e2.m_c[0] += ((__x_xpd__[2][1] * __x_xpd__[2][1]) + (__x_xpd__[2][0] * __x_xpd__[2][0]) + (__x_xpd__[2][2] * __x_xpd__[2][2]));

		}
		if (((x.m_gu & 8) != 0)) {
			e2.m_c[0] += (__x_xpd__[3][0] * __x_xpd__[3][0]);

		}
		scalar ie;
		ie.m_c[0] = ((char)1 / sqrt(e2.m_c[0]));
		mv __temp_var_1__;
		float __tmp_coord_array_6__[8] ;
		mv_zero(__tmp_coord_array_6__, 8);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_6__[0] += (__x_xpd__[0][0] * ie.m_c[0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_6__[1] += (__x_xpd__[1][0] * ie.m_c[0]);
			__tmp_coord_array_6__[2] += (__x_xpd__[1][1] * ie.m_c[0]);
			__tmp_coord_array_6__[3] += (__x_xpd__[1][2] * ie.m_c[0]);

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_6__[4] += (__x_xpd__[2][0] * ie.m_c[0]);
			__tmp_coord_array_6__[5] += (__x_xpd__[2][1] * ie.m_c[0]);
			__tmp_coord_array_6__[6] += (__x_xpd__[2][2] * ie.m_c[0]);

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_6__[7] += (__x_xpd__[3][0] * ie.m_c[0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_6__);
		__temp_var_1__.type(((g2Type)((short)__returnTypes__[0])));
		return __temp_var_1__;
	}
	scalar norm_r2(const mv& x) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)10), ((unsigned short)-1), ((unsigned short)1), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		scalar __temp_var_1__;
		const float* __x_xpd__[4] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__temp_var_1__.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__temp_var_1__.m_c[0] += ((__x_xpd__[1][2] * __x_xpd__[1][2]) + (__x_xpd__[1][1] * __x_xpd__[1][1]) + (__x_xpd__[1][0] * __x_xpd__[1][0]));

		}
		if (((x.m_gu & 4) != 0)) {
			__temp_var_1__.m_c[0] += ((__x_xpd__[2][2] * __x_xpd__[2][2]) + (__x_xpd__[2][1] * __x_xpd__[2][1]) + (__x_xpd__[2][0] * __x_xpd__[2][0]));

		}
		if (((x.m_gu & 8) != 0)) {
			__temp_var_1__.m_c[0] += (__x_xpd__[3][0] * __x_xpd__[3][0]);

		}
		return __temp_var_1__;
	}
	scalar norm_r(const mv& x) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)11), ((unsigned short)-1), ((unsigned short)1), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		scalar r2;
		const float* __x_xpd__[4] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			r2.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			r2.m_c[0] += ((__x_xpd__[1][0] * __x_xpd__[1][0]) + (__x_xpd__[1][1] * __x_xpd__[1][1]) + (__x_xpd__[1][2] * __x_xpd__[1][2]));

		}
		if (((x.m_gu & 4) != 0)) {
			r2.m_c[0] += ((__x_xpd__[2][1] * __x_xpd__[2][1]) + (__x_xpd__[2][2] * __x_xpd__[2][2]) + (__x_xpd__[2][0] * __x_xpd__[2][0]));

		}
		if (((x.m_gu & 8) != 0)) {
			r2.m_c[0] += (__x_xpd__[3][0] * __x_xpd__[3][0]);

		}
		return scalar(scalar_scalar, ((((r2.m_c[0] < (char)0)) ? (char)-1 : ((((r2.m_c[0] > (char)0)) ? (char)1 : (char)0))) * sqrt((((r2.m_c[0] < (char)0)) ? ((-r2.m_c[0])) : (r2.m_c[0])))));
	}
	mv unit_r(const mv& x) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)12), ((unsigned short)-1), ((unsigned short)1), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		scalar r2;
		const float* __x_xpd__[4] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			r2.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			r2.m_c[0] += ((__x_xpd__[1][1] * __x_xpd__[1][1]) + (__x_xpd__[1][2] * __x_xpd__[1][2]) + (__x_xpd__[1][0] * __x_xpd__[1][0]));

		}
		if (((x.m_gu & 4) != 0)) {
			r2.m_c[0] += ((__x_xpd__[2][1] * __x_xpd__[2][1]) + (__x_xpd__[2][0] * __x_xpd__[2][0]) + (__x_xpd__[2][2] * __x_xpd__[2][2]));

		}
		if (((x.m_gu & 8) != 0)) {
			r2.m_c[0] += (__x_xpd__[3][0] * __x_xpd__[3][0]);

		}
		scalar ir;
		ir.m_c[0] = ((char)1 / sqrt((((r2.m_c[0] < (char)0)) ? ((-r2.m_c[0])) : (r2.m_c[0]))));
		mv __temp_var_1__;
		float __tmp_coord_array_7__[8] ;
		mv_zero(__tmp_coord_array_7__, 8);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_7__[0] += (__x_xpd__[0][0] * ir.m_c[0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_7__[1] += (__x_xpd__[1][0] * ir.m_c[0]);
			__tmp_coord_array_7__[2] += (__x_xpd__[1][1] * ir.m_c[0]);
			__tmp_coord_array_7__[3] += (__x_xpd__[1][2] * ir.m_c[0]);

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_7__[4] += (__x_xpd__[2][0] * ir.m_c[0]);
			__tmp_coord_array_7__[5] += (__x_xpd__[2][1] * ir.m_c[0]);
			__tmp_coord_array_7__[6] += (__x_xpd__[2][2] * ir.m_c[0]);

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_7__[7] += (__x_xpd__[3][0] * ir.m_c[0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_7__);
		__temp_var_1__.type(((g2Type)((short)__returnTypes__[0])));
		return __temp_var_1__;
	}
	mv reverse(const mv& x) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)13), ((unsigned short)-1), ((unsigned short)1), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		mv __temp_var_1__;
		float __tmp_coord_array_8__[8] ;
		mv_zero(__tmp_coord_array_8__, 8);
		const float* __x_xpd__[4] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_8__[0] += __x_xpd__[0][0];

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_8__[1] += __x_xpd__[1][0];
			__tmp_coord_array_8__[2] += __x_xpd__[1][1];
			__tmp_coord_array_8__[3] += __x_xpd__[1][2];

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_8__[4] += (-1.0f * __x_xpd__[2][0]);
			__tmp_coord_array_8__[5] += (-1.0f * __x_xpd__[2][1]);
			__tmp_coord_array_8__[6] += (-1.0f * __x_xpd__[2][2]);

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_8__[7] += (-1.0f * __x_xpd__[3][0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_8__);
		__temp_var_1__.type(((g2Type)((short)__returnTypes__[0])));
		return __temp_var_1__;
	}
	mv negate(const mv& x) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)14), ((unsigned short)-1), ((unsigned short)1), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		mv __temp_var_1__;
		float __tmp_coord_array_9__[8] ;
		mv_zero(__tmp_coord_array_9__, 8);
		const float* __x_xpd__[4] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_9__[0] += (-1.0f * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_9__[1] += (-1.0f * __x_xpd__[1][0]);
			__tmp_coord_array_9__[2] += (-1.0f * __x_xpd__[1][1]);
			__tmp_coord_array_9__[3] += (-1.0f * __x_xpd__[1][2]);

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_9__[4] += (-1.0f * __x_xpd__[2][0]);
			__tmp_coord_array_9__[5] += (-1.0f * __x_xpd__[2][1]);
			__tmp_coord_array_9__[6] += (-1.0f * __x_xpd__[2][2]);

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_9__[7] += (-1.0f * __x_xpd__[3][0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_9__);
		__temp_var_1__.type(((g2Type)((short)__returnTypes__[0])));
		return __temp_var_1__;
	}
	mv dual(const mv& x) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)15), ((unsigned short)-1), ((unsigned short)1), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		mv __temp_var_1__;
		float __tmp_coord_array_10__[8] ;
		mv_zero(__tmp_coord_array_10__, 8);
		const float* __x_xpd__[4] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_10__[7] += (-1.0f * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_10__[4] += (-1.0f * __x_xpd__[1][2]);
			__tmp_coord_array_10__[5] += (-1.0f * __x_xpd__[1][0]);
			__tmp_coord_array_10__[6] += (-1.0f * __x_xpd__[1][1]);

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_10__[1] += __x_xpd__[2][1];
			__tmp_coord_array_10__[2] += __x_xpd__[2][2];
			__tmp_coord_array_10__[3] += __x_xpd__[2][0];

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_10__[0] += __x_xpd__[3][0];

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_10__);
		__temp_var_1__.type(((g2Type)((short)__returnTypes__[0])));
		return __temp_var_1__;
	}
	mv undual(const mv& x) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)16), ((unsigned short)-1), ((unsigned short)1), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		mv __temp_var_1__;
		float __tmp_coord_array_11__[8] ;
		mv_zero(__tmp_coord_array_11__, 8);
		const float* __x_xpd__[4] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_11__[7] += __x_xpd__[0][0];

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_11__[4] += __x_xpd__[1][2];
			__tmp_coord_array_11__[5] += __x_xpd__[1][0];
			__tmp_coord_array_11__[6] += __x_xpd__[1][1];

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_11__[1] += (-1.0f * __x_xpd__[2][1]);
			__tmp_coord_array_11__[2] += (-1.0f * __x_xpd__[2][2]);
			__tmp_coord_array_11__[3] += (-1.0f * __x_xpd__[2][0]);

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_11__[0] += (-1.0f * __x_xpd__[3][0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_11__);
		__temp_var_1__.type(((g2Type)((short)__returnTypes__[0])));
		return __temp_var_1__;
	}
	mv inverse(const mv& x) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)17), ((unsigned short)-1), ((unsigned short)1), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		scalar n;
		const float* __x_xpd__[4] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			n.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			n.m_c[0] += ((__x_xpd__[1][2] * __x_xpd__[1][2]) + (__x_xpd__[1][1] * __x_xpd__[1][1]) + (__x_xpd__[1][0] * __x_xpd__[1][0]));

		}
		if (((x.m_gu & 4) != 0)) {
			n.m_c[0] += ((__x_xpd__[2][0] * __x_xpd__[2][0]) + (__x_xpd__[2][2] * __x_xpd__[2][2]) + (__x_xpd__[2][1] * __x_xpd__[2][1]));

		}
		if (((x.m_gu & 8) != 0)) {
			n.m_c[0] += (__x_xpd__[3][0] * __x_xpd__[3][0]);

		}
		scalar in;
		in.m_c[0] = ((char)1 / n.m_c[0]);
		mv __temp_var_1__;
		float __tmp_coord_array_12__[8] ;
		mv_zero(__tmp_coord_array_12__, 8);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_12__[0] += (__x_xpd__[0][0] * in.m_c[0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_12__[1] += (__x_xpd__[1][0] * in.m_c[0]);
			__tmp_coord_array_12__[2] += (__x_xpd__[1][1] * in.m_c[0]);
			__tmp_coord_array_12__[3] += (__x_xpd__[1][2] * in.m_c[0]);

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_12__[4] += (-1.0f * __x_xpd__[2][0] * in.m_c[0]);
			__tmp_coord_array_12__[5] += (-1.0f * __x_xpd__[2][1] * in.m_c[0]);
			__tmp_coord_array_12__[6] += (-1.0f * __x_xpd__[2][2] * in.m_c[0]);

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_12__[7] += (-1.0f * __x_xpd__[3][0] * in.m_c[0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_12__);
		__temp_var_1__.type(((g2Type)((short)__returnTypes__[0])));
		return __temp_var_1__;
	}
	mv gradeInvolution(const mv& x) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)19), ((unsigned short)-1), ((unsigned short)1), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		mv __temp_var_1__;
		float __tmp_coord_array_13__[8] ;
		mv_zero(__tmp_coord_array_13__, 8);
		const float* __x_xpd__[4] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_13__[0] += __x_xpd__[0][0];

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_13__[1] += (-1.0f * __x_xpd__[1][0]);
			__tmp_coord_array_13__[2] += (-1.0f * __x_xpd__[1][1]);
			__tmp_coord_array_13__[3] += (-1.0f * __x_xpd__[1][2]);

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_13__[4] += __x_xpd__[2][0];
			__tmp_coord_array_13__[5] += __x_xpd__[2][1];
			__tmp_coord_array_13__[6] += __x_xpd__[2][2];

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_13__[7] += (-1.0f * __x_xpd__[3][0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_13__);
		__temp_var_1__.type(((g2Type)((short)__returnTypes__[0])));
		return __temp_var_1__;
	}

	// G2 functions:
	mv apply_om(const om& x, const mv& y) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type(), y.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)18), ((unsigned short)-1), ((unsigned short)2), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		mv __temp_var_1__;
		float __tmp_coord_array_14__[8] ;
		mv_zero(__tmp_coord_array_14__, 8);
		const float* __y_xpd__[4] ;
		y.expand(__y_xpd__, true);
		if (((y.m_gu & 2) != 0)) {
			__tmp_coord_array_14__[1] += ((x.m_c[1] * __y_xpd__[1][1]) + (x.m_c[0] * __y_xpd__[1][0]) + (x.m_c[2] * __y_xpd__[1][2]));
			__tmp_coord_array_14__[2] += ((x.m_c[5] * __y_xpd__[1][2]) + (x.m_c[4] * __y_xpd__[1][1]) + (x.m_c[3] * __y_xpd__[1][0]));
			__tmp_coord_array_14__[3] += ((x.m_c[8] * __y_xpd__[1][2]) + (x.m_c[6] * __y_xpd__[1][0]) + (x.m_c[7] * __y_xpd__[1][1]));

		}
		if (((y.m_gu & 4) != 0)) {
			__tmp_coord_array_14__[4] += ((x.m_c[9] * __y_xpd__[2][0]) + (x.m_c[11] * __y_xpd__[2][2]) + (x.m_c[10] * __y_xpd__[2][1]));
			__tmp_coord_array_14__[5] += ((x.m_c[13] * __y_xpd__[2][1]) + (x.m_c[12] * __y_xpd__[2][0]) + (x.m_c[14] * __y_xpd__[2][2]));
			__tmp_coord_array_14__[6] += ((x.m_c[15] * __y_xpd__[2][0]) + (x.m_c[16] * __y_xpd__[2][1]) + (x.m_c[17] * __y_xpd__[2][2]));

		}
		if (((y.m_gu & 8) != 0)) {
			__tmp_coord_array_14__[7] += (x.m_c[18] * __y_xpd__[3][0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_14__);
		__temp_var_1__.type(((g2Type)((short)__returnTypes__[0])));
		return __temp_var_1__;
	}
	namespace __G2_GENERATED__ {
		void set(om& __x__, const vector& __image_of_e1__, const vector& __image_of_e2__, const vector& __image_of_e3__) {
			__x__.m_c[0] = __image_of_e1__.m_c[0];
			__x__.m_c[3] = __image_of_e1__.m_c[1];
			__x__.m_c[6] = __image_of_e1__.m_c[2];
			__x__.m_c[1] = __image_of_e2__.m_c[0];
			__x__.m_c[4] = __image_of_e2__.m_c[1];
			__x__.m_c[7] = __image_of_e2__.m_c[2];
			__x__.m_c[2] = __image_of_e3__.m_c[0];
			__x__.m_c[5] = __image_of_e3__.m_c[1];
			__x__.m_c[8] = __image_of_e3__.m_c[2];
			__x__.m_c[9] = ((-1.0f * __x__.m_c[1] * __x__.m_c[3]) + (__x__.m_c[4] * __x__.m_c[0]));
			__x__.m_c[12] = ((-1.0f * __x__.m_c[4] * __x__.m_c[6]) + (__x__.m_c[7] * __x__.m_c[3]));
			__x__.m_c[15] = ((-1.0f * __x__.m_c[7] * __x__.m_c[0]) + (__x__.m_c[1] * __x__.m_c[6]));
			__x__.m_c[10] = ((-1.0f * __x__.m_c[2] * __x__.m_c[4]) + (__x__.m_c[5] * __x__.m_c[1]));
			__x__.m_c[13] = ((__x__.m_c[8] * __x__.m_c[4]) + (-1.0f * __x__.m_c[5] * __x__.m_c[7]));
			__x__.m_c[16] = ((__x__.m_c[2] * __x__.m_c[7]) + (-1.0f * __x__.m_c[8] * __x__.m_c[1]));
			__x__.m_c[11] = ((__x__.m_c[2] * __x__.m_c[3]) + (-1.0f * __x__.m_c[5] * __x__.m_c[0]));
			__x__.m_c[14] = ((-1.0f * __x__.m_c[8] * __x__.m_c[3]) + (__x__.m_c[5] * __x__.m_c[6]));
			__x__.m_c[17] = ((__x__.m_c[8] * __x__.m_c[0]) + (-1.0f * __x__.m_c[2] * __x__.m_c[6]));
			__x__.m_c[18] = ((__x__.m_c[17] * __x__.m_c[4]) + (__x__.m_c[14] * __x__.m_c[1]) + (__x__.m_c[11] * __x__.m_c[7]));
		}
	} /* end of namespace __G2_GENERATED__ */
	vector apply_om(const om& x, const vector& y) {
		return vector(vector_e1_e2_e3, ((x.m_c[2] * y.m_c[2]) + (x.m_c[0] * y.m_c[0]) + (x.m_c[1] * y.m_c[1])), ((x.m_c[5] * y.m_c[2]) + (x.m_c[4] * y.m_c[1]) + (x.m_c[3] * y.m_c[0])), ((x.m_c[6] * y.m_c[0]) + (x.m_c[7] * y.m_c[1]) + (x.m_c[8] * y.m_c[2])));
	}
	bivector apply_om(const om& x, const bivector& y) {
		return bivector(bivector_e1e2_e2e3_e3e1, ((x.m_c[11] * y.m_c[2]) + (x.m_c[10] * y.m_c[1]) + (x.m_c[9] * y.m_c[0])), ((x.m_c[14] * y.m_c[2]) + (x.m_c[12] * y.m_c[0]) + (x.m_c[13] * y.m_c[1])), ((x.m_c[15] * y.m_c[0]) + (x.m_c[17] * y.m_c[2]) + (x.m_c[16] * y.m_c[1])));
	}


	// algebra / user constants:
	__I3i_ct__ I3i;
	__e3_ct__ e3;
	__I3_ct__ I3;
	__e1_ct__ e1;
	__e2_ct__ e2;

	char *string(const mv & obj, char *str, int maxLength, const char *fp /* = NULL */) {
		int stdIdx = 0, l;
		char tmpBuf[256], tmpFloatBuf[256]; 
		int i, j, k = 0, bei, ia = 0, s = mv_size[obj.gu()], p = 0, cnt = 0;

		// set up the floating point precision
		if (fp == NULL) fp = mv_string_fp;

		// start the string
		l = sprintf(tmpBuf, "%s", mv_string_start);
		if (stdIdx + l <= maxLength) {
			strcpy(str + stdIdx, tmpBuf);
			stdIdx += l;
		}
		else mv_throw_exception("Buffer supplied to string() is too small", MV_EXCEPTION_ERROR);

		// print all coordinates
		for (i = 0; i <= 3; i++) {
			if (obj.gu() & (1 << i)) {
				for (j = 0; j < mv_gradeSize[i]; j++) {
					float coord = (float)mv_basisElementSign[ia] * obj.m_c[k];
					/* goal: print [+|-]obj.m_c[k][* basisVector1 ^ ... ^ basisVectorN] */			
					sprintf(tmpFloatBuf, fp, fabs(coord));
					if (atof(tmpFloatBuf) != 0.0) {
						l = 0;

						// print [+|-]
						l += sprintf(tmpBuf + l, "%s", (coord >= 0.0) 
							? (cnt ? mv_string_plus : "")
							: mv_string_minus);
						// print obj.m_c[k]
						l += sprintf(tmpBuf + l, tmpFloatBuf);

						if (i) { // if not grade 0, print [* basisVector1 ^ ... ^ basisVectorN]
							l += sprintf(tmpBuf + l, "%s", mv_string_mul);

							// print all basis vectors
							bei = 0;
							while (mv_basisElements[ia][bei] >= 0) {
								l += sprintf(tmpBuf + l, "%s%s", (bei) ? mv_string_wedge : "", 
									mv_basisVectorNames[mv_basisElements[ia][bei]]);
								bei++;
							}
						}

						//copy all to 'str'
						if (stdIdx + l <= maxLength) {
							strcpy(str + stdIdx, tmpBuf);
							stdIdx += l;
						}
						else mv_throw_exception("Buffer supplied to string() is too small", MV_EXCEPTION_ERROR);
						cnt++;
					}
					k++; ia++;
				}
			}
			else ia += mv_gradeSize[i];
		}

		// if no coordinates printed: 0
		l = 0;
		if (cnt == 0) {
			l += sprintf(tmpBuf + l, "0");
		}

		// end the string
		l += sprintf(tmpBuf + l, "%s", mv_string_end);
		if (stdIdx + l <= maxLength) {
			strcpy(str + stdIdx, tmpBuf);
			stdIdx += l;
		}
		else mv_throw_exception("Buffer supplied to string() is too small", MV_EXCEPTION_ERROR);

		return str;
	}

	// this function should be deprecated (conflicts with C++ stdlib)
	char *string(const mv & obj, const char *fp /* = NULL */) {
		// not multithreading safe, but not fatal either.
		static char str[2048];
		return string(obj, str, 2047, fp);
	}

	char *c_str(const mv & obj, const char *fp /* = NULL */) {
		return string(obj, fp);
	}

	std::string toString(const mv & obj, const char *fp /* = NULL */) {
		std::string str;
		const int SIZE = 2048;
		str.resize(SIZE);
		string(obj, &(str[0]), SIZE-1, fp);
		str.resize(strlen(&(str[0])));
		return str;
	}






	/** This function is not for external use. It compressed arrays of floats for storage in multivectors. */
	void compress(const float *c, float *cc, int &cgu, float epsilon /*= 0.0*/, int gu /*= ...*/) {
		int i, j, ia = 0, ib = 0, f, s;
		cgu = 0;

		// for all grade parts...
		for (i = 0; i <= 3; i++) {
			// check if grade part has memory use:
			if (!(gu & (1 << i))) continue;

			// check if abs coordinates of grade part are all < epsilon
			s = mv_gradeSize[i];
			j = ia + s;
			f = 0;
			for (; ia < j; ia++)
			if (mv_absLessThan(c[ia], epsilon)) {f = 1; break;}
			ia = j;
			if (f) {
				mv_memcpy(cc + ib, c + ia - s, s);
				ib += s;
				cgu |= (1 << i);
			}
		}	
	}

	mv mv_compress(const float *c, float epsilon/*= 0.0*/, int gu /*= ...*/) {
		float cc[8];
		int cgu;
		compress(c, cc, cgu, epsilon, gu);
		return mv(cgu, cc);
	}

	mv compress(const mv & arg1, float epsilon /*= 0.0*/) {
		return mv_compress(arg1.m_c, epsilon, arg1.m_gu);
	}

	void mv::compress(float epsilon /*= 0.0*/) {
		float cc[8];
		int cgu;
		e3ga::compress(m_c, cc, cgu, epsilon, m_gu);
		set(cgu, cc);
	}



	/** This function is not for external use. It decompresses the coordinates stored in this */
	void mv::expand(const Float *ptrs[], bool nulls /* = true */) const {
		const Float *c(m_c);
		const Float *null = (nulls) ? NULL : nullFloats();

		if (m_gu & 1) {
			ptrs[0] =  c;
			c += 1;
		}
		else ptrs[0] = null;	
		if (m_gu & 2) {
			ptrs[1] =  c;
			c += 3;
		}
		else ptrs[1] = null;	
		if (m_gu & 4) {
			ptrs[2] =  c;
			c += 3;
		}
		else ptrs[2] = null;	
		if (m_gu & 8) {
			ptrs[3] =  c;
			c += 1;
		}
		else ptrs[3] = null;	
	}


	void mvType::init(const mv &X, mv::Float epsilon) {
		m_type = MULTIVECTOR;

		// first of all determine grade usage & parity
		mv cX = X;
		cX.compress(epsilon);
		m_gradeUsage = (int)cX.gu();
		int cnt[2] = {0,0}; // nb even, odd grade parts in use
		{
			// count grade part usage:
			int cntIdx = 0;
			int gu = m_gradeUsage;
			while (gu != 0) {
				if ((gu & 1) != 0)
					cnt[cntIdx & 1]++;
				gu >>= 1;
				m_grade = cntIdx;
				cntIdx++;
			}

			// if no grade part in use: zero blade
			if ((cnt[0] == 0) && (cnt[1] == 0)) {
				// multivector = zero blade, case closed
				m_zero = true;
				m_type = BLADE;
				m_parity = 0;
				m_grade = 0; // forced to grade 0, but actually, does not really have a grade
				return;
			}
			else {
				m_zero = false;
				// if both even and odd grade parts in use: multivector
				if ((cnt[0] != 0) && (cnt[1] != 0)) {
					// X = multivector, case closed
					m_parity = -1;
					return;
				}
				else // more work to do, but parity is known:
				// either a blade, or a versor, TBD below
				m_parity = (cnt[1] != 0) ? 1 : 0;
			}
		}

		// first test for versor:
		bool useAlgebraMetric = true;
		init(X, epsilon, useAlgebraMetric, cnt[0] + cnt[1]);

	}


	void mvType::init(const mv &X, mv::Float epsilon, bool useAlgebraMetric, int guCnt) {
		mv rX = reverse(X);

		// test if null:
		mv Sq = (useAlgebraMetric) ? scp(X, rX) : scp(X, rX);
		Sq.compress(epsilon);
		if (_Float(Sq) == 0) {
			// X = multivector, case closed
			m_type = MULTIVECTOR;
			return;
		}

		// versor inverse must be true inverse:
		mv Xvi = (useAlgebraMetric) ? inverse(X) : inverse(X);
		mv Xgi = gradeInvolution(X);

		// check if (Xgi Xvi) is a scalar:
		mv XgiXvi = (useAlgebraMetric) ? gp(Xgi, Xvi) : gp(Xgi, Xvi);
		{
			mv tmp = XgiXvi;
			tmp.compress(epsilon);
			if (tmp.gu() != GRADE_0) { // if not scalar:
				// X = multivector, case closed
				m_type = MULTIVECTOR;
				return;
			}
		}

		// check if Xgi Xvi == Xvi Xgi
		mv XviXgi = (useAlgebraMetric) ? gp(Xvi, Xgi) : gp(Xvi, Xgi);
		{
			mv tmp = XviXgi - XgiXvi;
			tmp.compress(epsilon); // this should result in 0
			if (tmp.gu()) {
				// if not:
				// X = multivector, case closed
				m_type = MULTIVECTOR;
				return;
			}
		}

		// check if grade preserving for all basis vectors:
		{
			{
				// test e1		
				mv tmp = (useAlgebraMetric) ? gp(gp(Xvi, e1), Xgi) : gp(gp(Xvi, e1), Xgi);
				tmp.compress(epsilon);
				if (tmp.gu() != GRADE_1) { // X = multivector, case closed
					m_type = MULTIVECTOR;
					return;
				}
			}
			{
				// test e2		
				mv tmp = (useAlgebraMetric) ? gp(gp(Xvi, e2), Xgi) : gp(gp(Xvi, e2), Xgi);
				tmp.compress(epsilon);
				if (tmp.gu() != GRADE_1) { // X = multivector, case closed
					m_type = MULTIVECTOR;
					return;
				}
			}
			{
				// test e3		
				mv tmp = (useAlgebraMetric) ? gp(gp(Xvi, e3), Xgi) : gp(gp(Xvi, e3), Xgi);
				tmp.compress(epsilon);
				if (tmp.gu() != GRADE_1) { // X = multivector, case closed
					m_type = MULTIVECTOR;
					return;
				}
			}
		}

		// if homogeneous: blade
		if (guCnt == 1) m_type = BLADE;
		else m_type = VERSOR;
	}



	std::string mvType::toString() const {
		char buf[1024];
		sprintf(buf, "%s, grade: %d, gradeUsage: %X, parity: %s",
			(m_type == MULTIVECTOR) ? "multivector" : ((m_type == BLADE) ? "blade" : "versor"),
			m_grade, m_gradeUsage,
			(m_parity < 0) ? "none" : ((m_parity == 0) ? "even" : "odd"));
		return buf;
	}










} // end of namespace e3ga
// post_cpp_include

