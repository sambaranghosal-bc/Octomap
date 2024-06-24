#include <octomap/octomap.h>
#include <octomap/OcTree.h>
#include <fstream>
#include <iostream>

using namespace std;
using namespace octomap;

const int NUM_FILES = 200;
const std::string FILE_PREFIX = "../data/mapping_data/pointclouds/point_cloud_";

int main(int argc, char **argv){
    OcTree octree(0.05);
    for(int i = 0; i < NUM_FILES; i++){
            cout<<"Processing file: "<<i<<" / "<<NUM_FILES<<endl;
            std::string file_name = FILE_PREFIX + std::to_string(i) + ".txt";
            std::ifstream infile(file_name);
            if (!infile) {
                std::cerr << "Error opening point cloud file." << std::endl;
                return -1;
            }
            double x, y, z;
            point3d origin(0, 0, 0);
            while (infile >> x >> y >> z) {
                point3d point(x, y, z);
                octree.insertRay(origin, point);  // Insert free cells along the ray
                octree.updateNode(point, true);  // Mark as occupied
            }
            infile.close();
    }

    octree.writeBinary("octomap_from_mapping_data.bt");

}