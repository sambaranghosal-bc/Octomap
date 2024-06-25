import laspy
import numpy as np
import open3d as o3d

def read_las_file(file_path):
    # Open the .laz file
    las = laspy.read(file_path)
    # Accessing point data
    points = las.points
    # Print the point data

    x = points["X"]
    y = points["Y"]
    z = points["Z"]
    points = np.vstack((x, y, z)).T
    # print(points)
    # Create open3d point cloud from points
    pcd = o3d.geometry.PointCloud()
    pcd.points = o3d.utility.Vector3dVector(np.asarray(points))
    # Visualize the point cloud
    o3d.visualization.draw_geometries([pcd])


if __name__ == "__main__":
    read_las_file("/home/sambaran.ghosal/Downloads/octomap_demo.laz")
