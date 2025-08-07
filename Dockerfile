# Use Alpine as base image
FROM alpine:latest

# Set environment variables
ENV DISPLAY=:0

# Install necessary packages
RUN apk update && apk add --no-cache \
    build-base \
    g++ \
    mesa-dev \
    mesa-gl \
    mesa-glu \
    freeglut-dev \
    libx11-dev \
    libxext-dev \
    libxi-dev \
    libxmu-dev

# Set working directory
WORKDIR /app

# Copy project files
COPY . .

# Compile the chess project
RUN g++ -o chess chess.cpp -lGL -lGLU -lglut

# Create a script to run the application
RUN echo '#!/bin/bash\n\
export DISPLAY=${DISPLAY:-:0}\n\
./chess' > run_chess.sh && chmod +x run_chess.sh

# Expose X11 for GUI
VOLUME /tmp/.X11-unix

# Default command
CMD ["./run_chess.sh"]
