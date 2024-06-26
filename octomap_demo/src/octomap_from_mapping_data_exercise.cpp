#include <octomap/octomap.h>
#include <octomap/OcTree.h>
#include <fstream>
#include <iostream>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>

using namespace std;
using namespace octomap;

const int countFilesInDirectory(const std::string& directoryPath) {
    DIR* dir;
    struct dirent* ent;
    int count = 0;

    // Open directory
    dir = opendir(directoryPath.c_str());
    if (dir != NULL) {
        // Count the files
        while ((ent = readdir(dir)) != NULL) {
            count++;
        }
        // Close directory
        closedir(dir);
    } else {
        // Could not open directory
        perror("");
        return -1;
    }

    return count;
}

// Usage: ./octomap_from_mapping_data_exercise ../data/mapping_data/germany_demo/bpearl_pointcloud_in_world_frame
int main(int argc, char **argv){
    OcTree octree(0.05);
    cout<<"Original clamping threhold min: "<<octree.getClampingThresMin()<<endl;
    cout<<"Original clamping threshold max: "<<octree.getClampingThresMax()<<endl;
    cout<<"Original probHit: "<<octree.getProbHit()<<endl;
    cout<<"Original probMiss: "<<octree.getProbMiss()<<endl;
    const std::string directory = argv[1];

    octree.setClampingThresMin(0.25);
    octree.setClampingThresMax(0.85);
    octree.setProbHit(0.7);
    octree.setProbMiss(0.4);
//    const int NUM_FILES = countFilesInDirectory(directory+ "/bpearl_pointcloud_in_world_frame");  // Count the number of files in the directory
    const int NUM_FILES = 900;
    for(int i = 0; i < NUM_FILES; i+=1){
        cout<<"Processing file: "<<i<<" out of "<<NUM_FILES<<endl;
        std::string file_name = directory + "/bpearl_pointcloud_in_world_frame/point_cloud_" + std::to_string(i) + ".txt";
        std::ifstream infile(file_name);
        if (!infile) {
            std::cerr << "Error opening point cloud file." << std::endl;
        }
        double x, y, z;
        point3d origin(0, 0, 0);
        while (infile >> x >> y >> z) {
            if (z > 2.0 || z < 0.1) continue;
            point3d point(x, y, z);
            // To demonstrate that ray casting is extremely slow. In reality we make use of parallelization (tBB, OPENMP)
            octree.insertRay(origin, point, 50);  // Insert free cells along the ray
            octree.updateNode(point, true);  // Mark as occupied
        }
        infile.close();
    }

    cout<<"Entering robot pose into octomap to show trajectory"<<endl;
    for(int i = 0; i < NUM_FILES; i++)
    {
        std::string file_name = directory + "/robot_poses/robot_pose_" + std::to_string(i) + ".txt";
        std::ifstream infile(file_name);
        if (!infile) {
            std::cerr << "Error opening robot pose file." << std::endl;
        }
        point3d pose;
        while (infile >> pose.x() >> pose.y() >> pose.z()) {
            octree.updateNode(pose, true);  // Mark as occupied
        }
    }

    octree.writeBinary("octomap_from_mapping_data.bt");
    return 0;
}