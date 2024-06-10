/*
 * OctoMap - An Efficient Probabilistic 3D Mapping Framework Based on Octrees
 * https://octomap.github.io/
 *
 * Copyright (c) 2009-2013, K.M. Wurm and A. Hornung, University of Freiburg
 * All rights reserved.
 * License: New BSD
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the University of Freiburg nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <octomap/octomap.h>
#include <octomap/OcTree.h>
#include <fstream>
#include <string>
using namespace std;
using namespace octomap;


//void print_query_info(point3d query, OcTreeNode* node) {
//  if (node != NULL) {
//    cout << "occupancy probability at " << query << ":\t " << node->getOccupancy() << endl;
//  }
//  else
//    cout << "occupancy probability at " << query << ":\t is unknown" << endl;
//}
//
//int main(int /*argc*/, char** /*argv*/) {
//
//  cout << endl;
//  cout << "generating example map" << endl;
//
//  OcTree tree (0.1);  // create empty tree with resolution 0.1
//
//
//  // insert some measurements of occupied cells
//
//  for (int x=-20; x<20; x++) {
//    for (int y=-20; y<20; y++) {
//      for (int z=-20; z<20; z++) {
//        point3d endpoint ((float) x*0.05f, (float) y*0.05f, (float) z*0.05f);
//        tree.updateNode(endpoint, true); // integrate 'occupied' measurement
//      }
//    }
//  }
//
//  // insert some measurements of free cells
//
//  for (int x=-30; x<30; x++) {
//    for (int y=-30; y<30; y++) {
//      for (int z=-30; z<30; z++) {
//        point3d endpoint ((float) x*0.02f-1.0f, (float) y*0.02f-1.0f, (float) z*0.02f-1.0f);
//        tree.updateNode(endpoint, false);  // integrate 'free' measurement
//      }
//    }
//  }
//
//  cout << endl;
//  cout << "performing some queries:" << endl;
//
//  point3d query (0., 0., 0.);
//  OcTreeNode* result = tree.search (query);
//  print_query_info(query, result);
//
//  query = point3d(-1.,-1.,-1.);
//  result = tree.search (query);
//  print_query_info(query, result);
//
//  query = point3d(1.,1.,1.);
//  result = tree.search (query);
//  print_query_info(query, result);
//
//
//  cout << endl;
//  tree.writeBinary("simple_tree.bt");
//  cout << "wrote example file simple_tree.bt" << endl << endl;
//  cout << "now you can use octovis to visualize: octovis simple_tree.bt"  << endl;
//  cout << "Hint: hit 'F'-key in viewer to see the freespace" << endl  << endl;
//
//}

int main(int /*argc*/, char** /*argv*/) {
    // Create an empty octree with a resolution of 0.25 meters
    double resolution = 0.1;
    std::cout<<"resolution: "<<resolution<<std::endl;
    octomap::OcTree tree(resolution);

    // Open the point cloud text file
    std::ifstream infile("/home/sambaran.ghosal/BrainCorp/Sambaran/development/octomap/adaptive_voxel_grid_points.txt");
    if (!infile) {
        std::cerr << "Error opening point cloud file." << std::endl;
        return -1;
    }

    // Read the points from the file and insert into the octree
    double x, y, z;
    octomap::Pointcloud pointcloud;
    while (infile >> x >> y >> z) {
        pointcloud.push_back(x, y, z);
    }

    octomap::point3d origin(0, 0, 0);
//    while (infile >> x >> y >> z) {
//        octomap::point3d point(x, y, z);
//        tree.insertRay(origin, point);  // Insert free cells along the ray
//        tree.updateNode(point, true);  // Mark as occupied
//    }

    infile.close();
    tree.insertPointCloudRays(pointcloud, origin);

    //Add a far away point from current observations to the pointcloud
//    tree.updateNode(octomap::point3d(50, -20, 10), true);

    // Optionally save the octree to a file
    tree.writeBinary("octree_from_point_cloud.bt");

    std::cout << "Octree created and saved to octree_from_point_cloud.bt" << std::endl;

    return 0;
}
