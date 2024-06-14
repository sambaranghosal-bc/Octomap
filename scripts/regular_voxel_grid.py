import logging
import os.path
from typing import Tuple, Optional
import numpy as np
import open3d as o3d
from attr import attrs


def visualize_voxel_grid(pointcloud: np.ndarray) -> None:
    """
    Visualize the voxel grid using open3d
    :return:
    """
    pcd = o3d.geometry.PointCloud()
    pcd.points = o3d.utility.Vector3dVector(pointcloud)
    pcd.paint_uniform_color([0, 1, 0])
    o3d.visualization.draw_geometries([pcd])
    return


@attrs(auto_attribs=True, slots=True)
class RegularVoxelGrid:
    """
    Regular voxel grid
    """
    resolution: float
    max_coord: float
    min_coord: float
    _grid_size: Optional[Tuple[int, int, int]] = None
    _regular_voxel_grid: Optional[np.ndarray] = None
    _total_voxels: Optional[int] = None
    _filename: str = "voxel_grid.ply"

    def __attrs_post_init__(self) -> None:
        """
        Post initialization method
        :return:
        """
        if self.max_coord < self.min_coord:
            raise ValueError("Max coord should be greater than min coord")

        self._grid_size = tuple([int((self.max_coord - self.min_coord) / self.resolution)] * 3)
        self._regular_voxel_grid = np.zeros(self._grid_size)
        self._total_voxels = int(np.prod(self._grid_size))

    def create_regular_voxel_map(self) -> None:
        """
        Create regular voxel grid by assigning a random number of points as being occupied
        The cells being assigned occupied are assigned a value of 1 in the voxel grid
        The other cells remain as free cells and have the values 0
        """
        occuppied_voxels_count = int(self._total_voxels * 0.05)
        occuppied_indices = np.random.choice(self._total_voxels, occuppied_voxels_count, replace=False)
        occuppied_voxels = np.unravel_index(occuppied_indices, self._grid_size)
        self._regular_voxel_grid[occuppied_voxels] = 1

    def add_point_to_voxel_grid(self, point: np.ndarray) -> None:
        """
        Add a point to the voxel grid
        :param point:
        """
        voxel_index = np.floor((point - self.min_coord) / self.resolution).astype(int)
        self._regular_voxel_grid[voxel_index] = 1

    def get_voxel_grid_points(self) -> np.ndarray:
        """
        Get the points in the voxel grid
        :return occuppied_voxels: np.ndarray
        """
        occuppied_voxels = np.argwhere(self._regular_voxel_grid == 1) * self.resolution + self.min_coord
        return occuppied_voxels

    def save_voxel_grid_ply(self) -> None:
        """
        Save the voxel grid as a ply file
        """
        pcd = o3d.geometry.PointCloud()
        pcd.points = o3d.utility.Vector3dVector(
            np.argwhere(self._regular_voxel_grid == 1) * self.resolution + self.min_coord
        )

        o3d.io.write_point_cloud(self._filename, pcd)

    def get_saved_voxel_map_disk_size(self) -> float:
        """
        Get the size of the voxel map saved on disk
        """
        return os.path.getsize(self._filename) / (1024 * 1024)  # in MB

    def write_voxel_grid_points_to_txt(self, filename="octomap_demo/data/voxel_grid_points.txt"):
        """
        Write voxel grid points to a txt file
        :return:
        """
        np.savetxt(filename, self.get_voxel_grid_points(), fmt="%f %f %f")


if __name__ == '__main__':
    voxel_grid = RegularVoxelGrid(resolution=0.1, max_coord=10, min_coord=-10)
    voxel_grid.create_regular_voxel_map()
    point = np.array([6, 1, 1])
    voxel_grid.add_point_to_voxel_grid(point)
    logging.log(logging.WARN, f"Voxel grid points: {voxel_grid.get_voxel_grid_points()}")
    visualize_voxel_grid(np.array(voxel_grid.get_voxel_grid_points()).reshape((-1, 3)))
