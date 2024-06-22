#include <octomap/octomap.h>
#include <octomap/OcTree.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    //Create empty octree with resolution of 0.5 meters
    const double resolution = 0.5;
    octomap::OcTree octree(resolution);

    /*
    This is a demo of creating an octree from scratch. We will insert some points into the octree and mark them as occupied or free.
    We will add points one by one, manually calculate the tree structure by hand and verify it by traversing the octree from root to leaf.
    */

    octree.updateNode(octomap::point3d(0.75, 0.75, 0.75), true); //Mark as occupied
    octree.updateNode(octomap::point3d(-0.5, 0.5, 0.25), true); //Mark as occupied
    octree.updateNode(octomap::point3d(2.15, 2, -2), true); //Mark as occupied
    octree.updateNode(octomap::point3d(4.5, -4, 3), true); //Mark as occupied
    octree.updateNode(octomap::point3d(-3, 10, 3), false); //Mark as free
    octree.updateNode(octomap::point3d(0.90, 0.50, 0.60), false); //Mark as free
    octree.updateNode(octomap::point3d(-0.30, 0.45, 0.), false); //Mark as free

    for(octomap::OcTree::tree_iterator it = octree.begin_tree(), end=octree.end_tree(); it!= end; ++it){
        cout<< "Node center: "<< it.getCoordinate()<< " value: "<< it->getValue()<<endl;
        if (it->hasChildren()){
            cout<<"Node has children"<<endl;
//            for (auto i = 0; i < 8; i++)
//                cout<<"Child "<<i + 1<<" : "<<octree.getNodeChild(*it, i).getCoordinate()<<endl
        }
        else
            cout<<"Node does not have children"<<endl;

    }

    cout<<"Writing octree to file demo.bt"<<endl;
    octree.writeBinary("demo.bt");
    return 0;
}