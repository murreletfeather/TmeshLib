# TmeshLib
A C++ geometry and mesh processing library.

## Features
- Geometry primitives (Point, Point2, quaternion)
- Half-edge mesh data structure
- Mesh iterators and traversal utilities
- Parser utilities for mesh file formats

## Project Structure
```
├── Geometry/          # Geometry primitives and math utilities
│   ├── Point.h
│   ├── Point2.h
│   └── quat.h
├── Mesh/              # Mesh data structure and components
│   ├── BaseMesh.h
│   ├── boundary.h
│   ├── Edge.h
│   ├── Face.h
│   ├── HalfEdge.h
│   ├── iterators.h
│   └── Vertex.h
└── Parser/            # File parsing utilities
    ├── parser.h
    └── StrUtil.h
```

## Dependencies
- C++17 or later
- CMake for building

## Building
```bash
mkdir build && cd build
cmake ..
make
```

