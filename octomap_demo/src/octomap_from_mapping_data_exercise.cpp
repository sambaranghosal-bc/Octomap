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

    const int NUM_FILES = countFilesInDirectory(directory);  // Count the number of files in the directory

    for(int i = 0; i < NUM_FILES / 3; i+=1){
        cout<<"Processing file: "<<i<<" / "<<NUM_FILES / 3<<endl;
        std::string file_name = directory + "/point_cloud_" + std::to_string(i) + ".txt";
        std::ifstream infile(file_name);
        if (!infile) {
            std::cerr << "Error opening point cloud file." << std::endl;
        }
        double x, y, z;
        point3d origin(0, 0, 0);
        while (infile >> x >> y >> z) {
            if (z > 3.95 || z < 1) continue;
            point3d point(x, y, z);
            // To demonstrate that ray casting is extremely slow. In reality we make use of parallelization (tBB, OPENMP)
//                octree.insertRay(origin, point, 100);  // Insert free cells along the ray
            octree.updateNode(point, true);  // Mark as occupied
        }
        infile.close();
    }

    octree.writeBinary("octomap_from_mapping_data.bt");
    return 0;
}