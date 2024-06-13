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

void perform_ray_casting(const octomap::OcTree &tree)
{
    std::vector<octomap::point3d> directions{
    point3d(1, 0, 0), point3d(-1, 0, 0), point3d(0, 1, 0), point3d(0, -1, 0), point3d(0, 0, 1), point3d(0, 0, -1),
    };

    octomap::point3d origin(0, 0, 0);

    for(size_t i=0; i < directions.size(); i++)
    {

        octomap::point3d point;
        octomap::point3d direction = directions[i];
        bool hit = tree.castRay(origin, direction, point, true, 100.0);
        if (hit)
        {
            std::cout<<"Ray from "<<origin<<" at direction "<< direction<<" hit the point: "<<point<<std::endl;
        }
        else
        {
            std::cout<<"Ray from "<<origin<<" at direction "<<direction<<"  did not hit any obstacle"<<std::endl;
        }
    }
}

int main(int /*argc*/, char** /*argv*/) {
    // Create an empty octree with a resolution of 0.25 meters
    double resolution = 0.1;
    std::cout<<"resolution: "<<resolution<<std::endl;
    octomap::OcTree tree(resolution);

    // Open the point cloud text file
    std::ifstream infile("/home/brain-spark/Octomap/adaptive_voxel_grid_points.txt");
    if (!infile) {
        std::cerr << "Error opening point cloud file." << std::endl;
        return -1;
    }

    // Read the points from the file and insert into the octree
    double x, y, z;

    octomap::point3d origin(0, 0, 0);
    while (infile >> x >> y >> z) {
        octomap::point3d point(x, y, z);
        tree.insertRay(origin, point);  // Insert free cells along the ray
        tree.updateNode(point, true);  // Mark as occupied
    }

    // Either when we add individual point, we need to do the rayCasting
    // Or we can add the entire point cloud at once and that process does the rayCasting implicitly
    infile.close();

    //Add a far away point from current observations to the pointcloud
    //tree.updateNode(octomap::point3d(50, -20, 10), true);

    // Optionally save the octree to a file
    tree.writeBinary("octree_from_point_cloud.bt");

    std::cout << "Octree created and saved to octree_from_point_cloud.bt" << std::endl;

    perform_ray_casting(tree);

    return 0;
}
