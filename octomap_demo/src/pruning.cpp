#include <octomap/octomap.h>
#include <octomap/OcTree.h>
#include <iostream>

using namespace std;
using namespace octomap;

int main(int argc, char **argv)
{
    //Create empty octree with resolution of 0.2 meters
    const double resolution = 0.2;
    OcTree octree(resolution);

    std::vector<octomap::point3d> points = {
        {0.1, 0.1, 0.1},
        {0.2, 0.2, 0.2},
        {0.3, 0.3, 0.3},
        {0.4, 0.4, 0.4},
        {0.5, 0.5, 0.5},
        {1.0, 1.0, 1.0},
        {1.1, 1.1, 1.1},
        {1.2, 1.2, 1.2},
        {1.3, 1.3, 1.3},
        {1.4, 1.4, 1.4}
    };

    // Add points to the octree
    for (const auto& point : points) {
        octree.updateNode(point, true); // Mark as occupied
    }

    // Print the octree before pruning
    std::cout << "Octree before pruning:" << std::endl;
//    for(octomap::OcTree::tree_iterator it = octree.begin_tree(), end=octree.end_tree(); it!= end; ++it){
//        cout<< "Node center: "<< it.getCoordinate()<< " value: "<< it->getValue()<<endl;
//        if (it->hasChildren()){
//            cout<<"Node has children"<<endl;
//        }
//        else
//            cout<<"Node does not have children"<<endl;
//    }

    octree.writeBinary("no_pruning.bt");

    // Perform pruning
    octree.prune();

    // Print the octree after pruning
    std::cout << "Octree after pruning:" << std::endl;
//    for(octomap::OcTree::tree_iterator it = octree.begin_tree(), end=octree.end_tree(); it!= end; ++it){
//        cout<< "Node center: "<< it.getCoordinate()<< " value: "<< it->getValue()<<endl;
//        if (it->hasChildren()){
//            cout<<"Node has children"<<endl;
//        }
//        else
//            cout<<"Node does not have children"<<endl;
//    }

    octree.writeBinary("pruning.bt");

    return 0;
}