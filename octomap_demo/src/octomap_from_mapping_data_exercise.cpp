#include <octomap/octomap.h>
#include <octomap/OcTree.h>
#include <fstream>
#include <iostream>

using namespace std;
using namespace octomap;

const int NUM_FILES = 4632;
const std::string FILE_PREFIX = "../data/mapping_data/germany_demo/bpearl_pointcloud_in_world_frame/bpearl_pointcloud_";

int main(int argc, char **argv){
    OcTree octree(0.1);
    octree.setClampingThresMin(0.25);
    octree.setClampingThresMax(0.80);
    octree.setProbHit(0.9);
    octree.setProbMiss(0.1);
    for(int i = 0; i < NUM_FILES; i+=4){
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
    octree.toMaxLikelihood();
    octree.prune();

    octree.writeBinary("octomap_from_mapping_data.bt");

}