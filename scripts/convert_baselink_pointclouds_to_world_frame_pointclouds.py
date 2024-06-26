import numpy as np
import os
from tqdm import tqdm


def transform_pointclouds_to_world_frame():
    num_files = len(list(os.listdir("../octomap_demo/data/mapping_data/germany_demo/bpearl_pointcloud_in_baselink")))
    print(num_files)
    for i in tqdm(range(num_files)):
        transform = np.loadtxt(f"../octomap_demo/data/mapping_data/germany_demo/robot_poses/robot_pose_{i}.txt")
        pointcloud = np.loadtxt(f"../octomap_demo/data/mapping_data/germany_demo/bpearl_pointcloud_in_baselink/bpearl_pointcloud_{i}.txt")
        transform_matrix = np.array(
            [
                [np.cos(transform[2]), -np.sin(transform[2]), 0, transform[0]],
                [np.sin(transform[2]), np.cos(transform[2]), 0, transform[1]],
                [0, 0, 1, 0],
                [0, 0, 0, 1]
            ]
        )
        pointcloud_in_world_frame = pointcloud @ transform_matrix[:3, :3].T + transform_matrix[:3, 3]
        np.savetxt(
            f"../octomap_demo/data/mapping_data/germany_demo/bpearl_pointcloud_in_world_frame/bpearl_pointcloud_{i}.txt",
            pointcloud_in_world_frame
        )


if __name__ == "__main__":
    transform_pointclouds_to_world_frame()
