# Brain-Spark Octomap
Octomap is an important open source framework for 3D mapping. It is widely used in robotics community for its ease of use and integration. Please see [OctoMap Introduction](OCTOMAP.md) for more information.

In this workshop, we will cover the basics of octopmap (adding points, raycasting, querying, etc.). Then we will see how to create some octomaps from our robot mapping data. While doing so, we will explore the other advantages of octomap like multi-resolution, dynamic handling of obstacles.

## Docker container for project
To ease installation issues, a docker image is provided to run the exercises in this session. The docker image will have all pre-requisites installed and ready to use.

### Install docker
Please follow the instructions here to install docker on your system based on OS.

#### Ubuntu
1. Update the apt package index and install packages to allow apt to use a repository over HTTPS:
```commandline
# Add Docker's official GPG key:
sudo apt-get update
sudo apt-get install ca-certificates curl
sudo install -m 0755 -d /etc/apt/keyrings
sudo curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc
sudo chmod a+r /etc/apt/keyrings/docker.asc

# Add the repository to Apt sources:
echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/ubuntu \
  $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
sudo apt-get update
```

2. Install Docker Engine:
```commandline
sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
```

3. Verify that Docker Engine is installed correctly by running the hello-world image:
```
sudo docker run hello-world
```

Should see output : 
```angular2html
Unable to find image 'hello-world:latest' locally
latest: Pulling from library/hello-world
c1ec31eb5944: Pull complete 
Digest: sha256:94323f3e5e09a8b9515d74337010375a456c909543e1ff1538f5116d38ab3989
Status: Downloaded newer image for hello-world:latest

Hello from Docker!
This message shows that your installation appears to be working correctly.

To generate this message, Docker took the following steps:
 1. The Docker client contacted the Docker daemon.
 2. The Docker daemon pulled the "hello-world" image from the Docker Hub.
    (amd64)
 3. The Docker daemon created a new container from that image which runs the
    executable that produces the output you are currently reading.
 4. The Docker daemon streamed that output to the Docker client, which sent it
    to your terminal.

To try something more ambitious, you can run an Ubuntu container with:
 $ docker run -it ubuntu bash

Share images, automate workflows, and more with a free Docker ID:
 https://hub.docker.com/

For more examples and ideas, visit:
 https://docs.docker.com/get-started/
```

#### MacOS

Before installing Docker Desktop for Mac, ensure your system meets the following requirements:

- macOS must be version 10.15 (Catalina) or newer.
- At least 4GB of RAM.
- VirtualBox prior to version 4.3.30 must not be installed (Docker Desktop for Mac includes its own version of Docker Engine).

##### Download Docker Desktop for Mac

1. Go to the [Docker Desktop for Mac download page](https://www.docker.com/products/docker-desktop).
2. Click on the "Download for Mac" button.

##### Install Docker Desktop

1. Once the download is complete, open the downloaded `.dmg` file.
2. In the window that appears, drag the Docker icon to the Applications folder.

##### Start Docker Desktop

1. Open the Applications folder and double-click on the Docker icon to start Docker Desktop.
2. You may be prompted to authorize Docker with your system password. Enter your password to continue.
3. Docker Desktop will start and you will see the Docker icon in the menu bar at the top of your screen.

##### Verify the Installation

1. Open a terminal window.
2. Run the following command to verify that Docker is installed correctly:
```sh
docker --version
```
3. Additionally run the following and verify that output is as shown in docker for ubuntu:
```sh
docker run hello-world
```

Output should be similar as here : 
```angular2html
Unable to find image 'hello-world:latest' locally
latest: Pulling from library/hello-world
c1ec31eb5944: Pull complete 
Digest: sha256:94323f3e5e09a8b9515d74337010375a456c909543e1ff1538f5116d38ab3989
Status: Downloaded newer image for hello-world:latest

Hello from Docker!
This message shows that your installation appears to be working correctly.

To generate this message, Docker took the following steps:
 1. The Docker client contacted the Docker daemon.
 2. The Docker daemon pulled the "hello-world" image from the Docker Hub.
    (amd64)
 3. The Docker daemon created a new container from that image which runs the
    executable that produces the output you are currently reading.
 4. The Docker daemon streamed that output to the Docker client, which sent it
    to your terminal.

To try something more ambitious, you can run an Ubuntu container with:
 $ docker run -it ubuntu bash

Share images, automate workflows, and more with a free Docker ID:
 https://hub.docker.com/

For more examples and ideas, visit:
 https://docs.docker.com/get-started/
```

## Run docker container
Once the installation is successful, first we need to build the docker image.
We can do this in two ways : 
### Pull docker image from Docker Hub
1. Create a docker hub account[here](https://www.docker.com/products/docker-hub/) if you don't have one. 
2. Pull the docker image from docker hub using the following command:
```commandline
docker pull <image_name:tag>
```
3. Once the docker image has been pulled succssfully, run the docker container using the following command:
```commandline
docker run -it --rm --gpus all --env="DISPLAY=$DISPLAY" --env="QT_X11_NO_MITSHM=1" --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" --volume="$HOME/.Xauthority:/root/.Xauthority:rw" --env="XAUTHORITY=/root/.Xauthority" -p 8888:8888 brain-spark:octomap
```

### Build docker image from Dockerfile
The other way is to build the docker image from the Dockerfile provided in the repository.
1. Clone the repository to your local machine.
```commandline
git clone https://github.com/sambaranghosal-bc/Octomap.git
docker build -t brain-spark:octomap .
```
2. It will take some time to build the docker image, once done, run the docker container using the following command:
```commandline
docker run -it --rm --gpus all --env="DISPLAY=$DISPLAY" --env="QT_X11_NO_MITSHM=1" --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" --volume="$HOME/.Xauthority:/root/.Xauthority:rw" --env="XAUTHORITY=/root/.Xauthority" -p 8888:8888 brain-spark:octomap
```

## Launch Jupyter notebook from inside docker container
```
jupyter-notebook --ip=0.0.0.0 --port=8888 --no-browser --allow-root
```
