#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Core>
#include <chrono>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace Eigen;

int main(int  argc, char** argv) {
    double ar = 1., br = 2. , cr = 1.;
    double ae = 2., be = -1., ce = 5.;
    int N = 100;
    double w_sigma = 1.;
    double inv_sigma = 1. / w_sigma;
    cv::RNG rng;

    vector<double> x_data, y_data;
    for (int i = 0; i < N; i++) {
        double x = i / 100.;
        x_data.push_back(x);
        y_data.push_back(exp(ar * x * x + br * x + cr) + rng.gaussian(w_sigma * w_sigma));
    }


    int iterations = 100;
    double cost = 0, lastCost = 0;

    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    for (int iter = 0; iter < iterations; iter++) {
        Matrix3d H = Matrix3d::Zero();
        Vector3d b = Vector3d::Zero();
        cost = 0;

        for (int i = 0; i < N; i++) {
            double xi = x_data[i], yi = y_data[i];
            double error = yi - exp(ae * xi * xi + be * xi + ce);
            Vector3d J = Vector3d(-xi * xi * exp(ae * xi * xi + be * xi + ce), -xi * exp(ae * xi * xi + be * xi + ce), -exp(ae * xi * xi + be * xi + ce));
            H += inv_sigma * inv_sigma * J * J.transpose();
            b += -inv_sigma * inv_sigma * error * J;
            cost += error * error;
        }

        Vector3d dx = H.ldlt().solve(b);
        if (isnan(dx[0])) {
            std::cout << "result is nan!" << endl;
            break;
        }

        if (iter > 0 && cost > lastCost) {
            std::cout << "cost: " << cost << ", last cost: " << lastCost << endl;
            break;
        }

        ae += dx[0];
        be += dx[1];
        ce += dx[2];
        lastCost = cost;

        std::cout << "total cost: " << cost << ", \tupdate: " << dx.transpose() << ", \testimated params: " << ae << ", " << be << ", " << ce << endl;
    }

    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    std::cout << "solve time cost = " << time_used.count() << " seconds." << endl;

    std::cout << "estimated abc = " << ae << ", " << be << ", " << ce << endl;
    return 0;
}

