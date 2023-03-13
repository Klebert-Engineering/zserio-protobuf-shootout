FROM dockcross/linux-armv7:latest

# All deps that are not covered by the dockcross/linux-armv7 image
RUN apt-get update && DEBIAN_FRONTEND="noninteractive" apt-get install -y \
    openjdk-11-jre \
    

# Need a specific version of conan (downgrade)
RUN pip3 install conan==1.58.0

