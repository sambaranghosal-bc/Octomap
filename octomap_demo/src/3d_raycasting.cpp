#include <octomap/octomap.h>
#include <octomap/OcTree.h>
#include <iostream>
#include <math.h>
#include <cassert>

using namespace std;
using namespace octomap;

vector<point3d> get_points(const double r, const int n)
{
    assert(n > 0);

    double x{0}, y{0};

    vector<point3d> points;
    for(double z = 0; z < 1.1; z += 0.1){
        for (int i = 0; i < n; i++)
        {
            x = r * cos(2 * M_PI * i / n);
            y = r * sin(2 * M_PI * i / n);
            points.push_back(point3d(x, y, z));
        }
    }
    return points;
}

int main(int argc, char **argv)
{
    //Create empty octree with resolution of 0.2 meters
    const double resolution = 0.2;
    OcTree octree(resolution);

    vector<point3d> points = get_points(1.0, 100);
    // Add points to the octree
    for (const auto &point : points)
    {
        octree.updateNode(point, true); // Mark as occupied
    }

    // Save octomap without free space marking
    octree.writeBinary("no_ray_casting.bt");

    // Perform ray casting
    point3d origin(0, 0, 0);
    unsigned int done = 0;
    for (const auto &point : points)
    {
        cout<<"Percentage done: "<<((done + 1) * 100) / points.size()<<"%"<<endl;
        done++;
        point3d direction = (point - origin).normalized();
        auto range = (point - origin).norm();
        unsigned int num_steps = range / resolution;
        for (size_t i = 0; i < num_steps; i++)
        {
            point3d ray_point = origin + direction * i * resolution;
            octree.updateNode(ray_point, false); // Mark as free
        }
    }

    // Save octomap with free space marking
    octree.writeBinary("ray_casting.bt");

    return 0;
}

