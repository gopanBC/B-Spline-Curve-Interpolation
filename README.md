# Cubic B-Spline Interpolation (C++ with Eigen & Gnuplot)

This repository implements **cubic uniform B-spline interpolation with zero-curvature endpoint conditions**, based on the methodology from:

>Y. Pu, Y. Shi, X. Lin, Y. Hu, and Z. Li, “C2 -Continuous orientation planning for robot end-effector with B-spline curve based on logarithmic quaternion,” Math. Problems Eng., vol. 2020, Jul. 2020, Art. no. 2543824.

---

## Features
- Implements cubic uniform B-spline curve interpolation.
- Enforces **zero curvature** at endpoints (smooth start & end).
- Uses **Eigen** for linear algebra and **gnuplot-iostream** for visualization.
- Provides console output of interpolated spline points.

---

## Dependencies
- [Eigen3](https://eigen.tuxfamily.org) (linear algebra library)
- [gnuplot-iostream](https://github.com/dstahlke/gnuplot-iostream) (for plotting)

## Install dependencies (Ubuntu example):

```bash
sudo apt-get install libeigen3-dev gnuplot
```

## Build & Run
```bash
g++ bspline.cpp -o bspline -lboost_iostreams -lboost_system -lboost_filesystem

./bspline
```

