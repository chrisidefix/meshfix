/****************************************************************************
* JMeshExt                                                                  *
*                                                                           *
* Consiglio Nazionale delle Ricerche                                        *
* Istituto di Matematica Applicata e Tecnologie Informatiche                *
* Sezione di Genova                                                         *
* IMATI-GE / CNR                                                            *
*                                                                           *
* Authors: Marco Attene                                                     *
*                                                                           *
* Copyright(C) 2006: IMATI-GE / CNR                                         *
*                                                                           *
* All rights reserved.                                                      *
*                                                                           *
* This program is free software; you can redistribute it and/or modify      *
* it under the terms of the GNU General Public License as published by      *
* the Free Software Foundation; either version 2 of the License, or         *
* (at your option) any later version.                                       *
*                                                                           *
* This program is distributed in the hope that it will be useful,           *
* but WITHOUT ANY WARRANTY; without even the implied warranty of            *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
* GNU General Public License (http://www.gnu.org/licenses/gpl.txt)          *
* for more details.                                                         *
*                                                                           *
****************************************************************************/

#ifndef _EXTTRIMESH_H
#define _EXTTRIMESH_H

#include "jmesh.h"
#include "binTree.h"
#include "triangleoctree.h"
#include <set>
using std::set;

class ExtTriMesh : public Triangulation
{
 public:
 TriangleOctree *ot;
 // Constructors
 ExtTriMesh() : Triangulation() { ot = NULL; }
 ExtTriMesh(const char *s) : Triangulation(s) { ot = NULL; }
 ExtTriMesh(const Triangulation *t) : Triangulation(t) { ot = NULL; }
 ExtTriMesh(const Triangle *t, const bool keep_ref =false) : Triangulation(t, keep_ref) { ot = NULL; }

 Edge	*joinBoundaryLoops(bool =0, bool =1, bool =1); // (in "ALGORITHMS/holeFilling.C")
 Edge	*joinBoundaryLoops(Vertex *, Vertex *, bool =0, bool =1, bool =1); // (in "ALGORITHMS/holeFilling.C")
 int     fillSmallBoundaries(int, bool =0, bool =0);   // (in "ALGORITHMS/holeFilling.C")
 int     TriangulateHole(Edge *);		       // (in "ALGORITHMS/holeFilling.C")
 void    FillHole(Edge *, bool =0);		       // (in "ALGORITHMS/holeFilling.C")
 int refineSelectedHolePatches(Triangle * =NULL);      // (in "ALGORITHMS/holeFilling.C")
 void fairSelection(Triangle * =NULL);		       // (in "ALGORITHMS/holeFilling.C")

 // Mirko's functions
 void initializeOctree();
 int  joinCloseOrOverlappingComponents( double minAllowedDistance = 1.0 );
 bool joinComponentsCloseBoundaries(List* nl, List *ml, double maxDistanceToJoin);
 //! Returns true, if the Point p is inside the component. The component must be a
 //! closed surface. Triangles of the surface must be recognizable using (t->mask & 1<<bit)>0.
 //! This function needs an initialized octree.
 //! Warning: The normals must be directed outwards of each component!
 bool isPointInComponent(Point *p, char bit);
 List* getComponentsVertices(List *component);

 // Misc Algorithms (Implemented in "ALGORITHMS/*.C")

 void loopSubdivision(int);
 void modbutSubdivision();
 void sqrt3Subdivision();
 int laplacianSmooth(int =1, double =1.0);
 int uniformRemesh(int, int =0);
 int spherize(int);
 int featureRecover(double, double);
 int simplify(int, int =0, int =0, int =0);
 int multiplechoice_simplify(int, int =0, int =8, int =0);
 void mc_resample(int, int =0, int =0);
 int epsilonSample(double, int =0);

 int  selectIntersectingTriangles(UINT16 tri_per_cell=100);

 void tagPlanarRegionsBoundaries(double max_distance);

 //! Normalize all the shells and distribute them on a virtual sphere. O(N).
 void placeShellsOnVirtualSphere();
 Edge *flatten(Edge * =NULL);

 bool plumberSelect(Vertex *start, double radius);
};

#endif // _EXTTRIMESH_H
