
# Height Field Water Simulation

Height Field Water Simulation implemented in OpenGL.

Height Field Water Simulation simplifies fluids into 2D with 
- u[i, j] where u represents the height given a coordinate i, j
- v[i, j] where v represents the velocity given a coordinate i, j.

The water is rendered by creating a mesh grid for each u[i, j] then rendered with enviroment mapping. There is also a debug shader for wireframe rendering.

The normals for each face in the mesh grid were calculated using a geometry shader.

The Algorithm used to simulate the water simulation is
- c = wave horizontal speed constant.
- c2 = c * c
- h = width of each point.
- h2 = h * h
- k = dmaping constant
```
for all i, j
    force = c2 *(u[i+1,j]+u[i-1,j]+u[i,j+1]+u[i,j-1] – 4u[i,j]) / h2
    damping_force = -k * force
    v[i, j] += (force + damping_force) * delta_time
    v[i, j] *= 0.995

for all i, j
    u[i, j] += v[i, j] * detla_time
```

## Demo

![alt text](https://github.com/xz1a/HeightField/blob/main/demo.JPG)
![](demo.gif)

## References

 - [Fast Water Simulation for Games Using Height Fields by Matthias Müller-Fischer from GDC 2008](https://ubm-twvideo01.s3.amazonaws.com/o1/vault/gdc08/slides/S6509i1.pdf)

## Dependencies
- [GLFW](https://github.com/glfw/glfw) - an Open Source, multi-platform library for OpenGL, OpenGL ES and Vulkan application development.
- [GL3W](https://github.com/skaslev/gl3w) - Simple OpenGL core profile loading
- [GLM](https://github.com/g-truc/glm) - a header only C++ mathematics library for graphics software based on the OpenGL Shading Language (GLSL) specifications.
- [STBI](https://github.com/nothings/stb/blob/master/stb_image.h) - Image Loading Header Library.