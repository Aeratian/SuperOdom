# Author: TaeYoung Kim
# email: tyoung96@yonsei.ac.kr

FROM osrf/ros:noetic-desktop-full

ENV NVIDIA_VISIBLE_DEVICES=${NVIDIA_VISIBLE_DEVICES:-all}
ENV NVIDIA_DRIVER_CAPABILITIES=${NVIDIA_DRIVER_CAPABILITIES:+$NVIDIA_DRIVER_CAPABILITIES,}graphics

# Install core utilities and dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    cppcheck \
    gdb \
    git \
    sudo \
    vim \
    wget \
    tmux \
    curl \
    less \
    htop \
    libsm6 \
    libxext6 \
    libgl1-mesa-glx \
    libxrender-dev \
    tzdata \
    libatlas-base-dev \
    libeigen3-dev \
    libpcl-dev \
    libgoogle-glog-dev \
    libsuitesparse-dev \
    libglew-dev \
    unzip \
    python3-pip \
    python3-tk \
    && apt-get clean

# Set timezone
RUN ln -fs /usr/share/zoneinfo/America/New_York /etc/localtime && \
    dpkg-reconfigure -f noninteractive tzdata

# Install ROS Noetic packages
RUN apt-get update && apt-get install -y \
    ros-noetic-tf2 \
    ros-noetic-cv-bridge \
    ros-noetic-pcl-conversions \
    ros-noetic-xacro \
    ros-noetic-robot-state-publisher \
    ros-noetic-rviz \
    ros-noetic-image-transport \
    ros-noetic-image-transport-plugins \
    ros-noetic-pcl-ros \
    ros-noetic-grid-map-msgs \
    ros-noetic-grid-map \
    python3-rosdep \
    python3-rosinstall \
    python3-rosinstall-generator \
    python3-wstool \
    && apt-get clean

# Initialize rosdep
RUN rosdep update

# Python packages
RUN pip3 install --upgrade pip
RUN pip3 install --no-cache-dir \
    numpy==1.24.3 \
    scipy \
    matplotlib==3.7.1 \
    ipython \
    opencv-python \
    pandas \
    visdom \
    scikit-image \
    scikit-learn \
    numba \
    Pillow \
    pyyaml \
    pycryptodome \
    bagpy \
    Cython \
    catkin_tools \
    gym \
    rerun-sdk \
    packaging \
    torch --ignore-installed

# Build Livox SDK
WORKDIR /root/
RUN git clone https://github.com/Livox-SDK/Livox-SDK2.git && \
    cd Livox-SDK2 && mkdir build && cd build && \
    cmake .. && make -j2 && make install

# Build Sophus
WORKDIR /root/
RUN git clone http://github.com/strasdat/Sophus.git && \
    cd Sophus && git checkout 97e7161 && \
    mkdir build && cd build && \
    cmake .. -DBUILD_TESTS=OFF && \
    make -j8 && make install

# Build GTSAM
WORKDIR /root/
RUN git clone https://github.com/borglab/gtsam.git && \
    cd gtsam && git checkout 4abef92 && \
    mkdir build && cd build && \
    cmake -DGTSAM_USE_SYSTEM_EIGEN=ON -DGTSAM_BUILD_WITH_MARCH_NATIVE=OFF .. && \
    make -j6 && make install

# Build Ceres Solver
WORKDIR /root/
RUN git clone https://github.com/ceres-solver/ceres-solver.git && \
    cd ceres-solver && git checkout f68321e7de8929fbcdb95dd42877531e64f72f66 && \
    mkdir build && cd build && \
    cmake .. && make -j6 && make install

# Source ROS on container entry
RUN echo "source /opt/ros/noetic/setup.bash" >> /root/.bashrc
RUN echo "export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH" >> /root/.bashrc

# Optional entrypoint setup (comment if not used)
COPY ./ros_entrypoint.sh /
RUN chmod +x /ros_entrypoint.sh
ENTRYPOINT ["/ros_entrypoint.sh"]

CMD ["bash"]

