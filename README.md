# Octomap

## Run docker container
```
docker run -it --rm --gpus all --env="DISPLAY=$DISPLAY" --env="QT_X11_NO_MITSHM=1" --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" --volume="$HOME/.Xauthority:/root/.Xauthority:rw" --env="XAUTHORITY=/root/.Xauthority" -p 8888:8888 brain-spark:octomap
```

## Launch Jupyter notebook from inside docker container
```
jupyter-notebook --ip=0.0.0.0 --port=8888 --no-browser --allow-root
```
