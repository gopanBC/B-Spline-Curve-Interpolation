#include <cstddef>
#include <iostream>
#include <eigen3/Eigen/Eigen>
#include <typeinfo>
#include <vector>
#include <initializer_list>
#include <utility>
#include <typeinfo>

#include "gnuplot-iostream.h"

void plotData(const std::vector<std::pair<float, float>> data)
{
    Gnuplot gp;
    gp << "set xrange [-2.5:2.5]\nset yrange [-2.5:2.5]\n";
    gp << "plot '-' with lines title 'cubic', '-' with points title 'circle'\n";
    gp.send1d(data);
}

template<int Rows, int Cols>
class Bspline
{
    public:
        Bspline(const Eigen::Matrix<float, Rows, Cols> knots)
        {
            findControlPoints(knots);
        }
        void compute(int i)
        {
            Eigen::Matrix<float, 4, 4> B;
            B << 1.0, 4.0, 1.0, 0.0,
              -3.0, 0.0, 3.0, 0.0,
              3.0, -6.0, 3.0, 0.0,
              -1.0, 3.0, -3.0, 1.0;
            Eigen::Matrix<float, 4, 3> D0;
            for(float u = 0.0; u < 1.01;)
            {
                Eigen::Matrix<float, 1, 4> U;
                U << 1.0, u, u*u, u*u*u;
                if(i == 0)
                {
                    D0.row(0) << control_points_.row(0); 
                    D0.row(1) << control_points_.row(0); 
                    D0.row(2) << control_points_.row(1); 
                    D0.row(3) << control_points_.row(2); 
                    auto point = 1.0/6.0 * (U * B * D0);
                    points.emplace_back(point[0], point[1]);
                }
                else if(i == 1)
                {
                    D0.row(0) << control_points_.row(0); 
                    D0.row(1) << control_points_.row(1); 
                    D0.row(2) << control_points_.row(2); 
                    D0.row(3) << control_points_.row(3); 
                    auto point = 1.0/6.0 * (U * B * D0);
                    points.emplace_back(point[0], point[1]);
                }
                else if(i == 2)
                {
                    D0.row(0) << control_points_.row(1); 
                    D0.row(1) << control_points_.row(2); 
                    D0.row(2) << control_points_.row(3); 
                    D0.row(3) << control_points_.row(0);  
                    auto point = 1.0/6.0 * (U * B * D0);
                    points.emplace_back(point[0], point[1]);
                }
                
                u +=  0.01;
            }
        } 
        void getSpline() 
        {
            for(int i = 0; i< 3; i++)
            {
                compute(i);
            }
            plotData(points);
            // for(auto& point : points)
            // {
            //     std::cout << "x : " << point.first << "\t" << "y : " << point.second << "\n";
            // }
        }
    private:
        void findControlPoints(const Eigen::Matrix<float, Rows, Cols>& knots)
        {
            Eigen::Matrix<float, 4, 4> A;
            A << 5.0, 1.0, 0.0, 0.0,
              1.0, 4.0, 1.0, 0.0,
              0.0, 1.0, 4.0, 1.0,
              0.0, 0.0, 1.0, 4.0;
            auto A_inv = (A.inverse());
            control_points_ =  (A_inv * knots) * 6.0;
        }
        Eigen::Matrix<float, Rows, Cols> control_points_;
        std::vector<std::pair<float, float>> points;
};


int main()
{
    Eigen::Matrix<float, 4, 3> knots;
    knots  << 0.0, 0.0, 0.0,
           0.05, 0.1, 0.0,
           -2.05, 1.5, 0.0,
           2.04, 0.05, 0.0;
    Bspline<4, 3> bspline(knots);
    bspline.getSpline();
}
