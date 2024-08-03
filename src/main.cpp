#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <iomanip>
#include <unistd.h>

#include "gviewer.h"
#include "visualization.h"
#include "logger.h"

using namespace std;

#define pai 3.14159265358979323846
#define EARTH_RE 6378137.0 //地球半径
#define EARTH_F 0.0033528106647474807198455286185206 //地球扁率
#define EARTH_WIE 0.000072921151467348494572823629331 //地球自转角速度

bool initGPS = false;
double GPS_last_latitude, GPS_last_longitude, GPS_last_height;
double GPS_calculate_longitude = 0;
double GPS_calculate_latitude = 0;

std::vector<std::vector<double>> Readlla(const char* filename);
void lla2xyz(double latitude, double longitude, double altitude, double* xyz);

int main(int argc, char** argv) {
    cv::Mat img = cv::imread(argv[1]);
    cv::imshow("test", img);
    cv::waitKey(0);
    return 0;
}

std::vector<std::vector<double>> Readlla(const char* filename) {
    std::fstream file(filename, std::ios::in);
    std::string line;
    assert(file.is_open());

    std::vector<std::vector<double>> lla;

    while (std::getline(file, line)) {
        std::vector<double> data;
        std::stringstream ss(line);
        std::string value;
        while (std::getline(ss, value, ',')) {
            try {
                data.push_back(std::stod(value));
            } catch (const std::invalid_argument& e) {
                std::cerr << "\033[33m [WARN]:" << " invalid number: " << value << "\033[0m" << std::endl;
                break;
            }
        }
        if (data.size() == 12) {
            std::swap(data[1], data[2]);
            data.erase(data.begin(), data.begin() + 2);
            lla.push_back(data);
        }
    }
    file.close();
    return lla;
}

void lla2xyz(double latitude, double longitude, double altitude, double* xyz) {
    if (!initGPS) {
        std::cout << "GPS init" << std::endl;
        initGPS = true;
        GPS_last_latitude = latitude;
        GPS_last_longitude = longitude;
        GPS_last_height = altitude;
    }
    double Rm_GPS = EARTH_RE * (1 - 2 * EARTH_F + 3 * EARTH_F * sin(latitude * pai / 180) * sin(latitude * pai / 180));
    double Rn_GPS = EARTH_RE * (1 + EARTH_F * sin(latitude * pai / 180) * sin(latitude * pai / 180));
    GPS_calculate_longitude = (longitude - GPS_last_longitude) * pai / 180 * (Rn_GPS + altitude) * cos(latitude * pai / 180) + GPS_calculate_longitude;
    GPS_calculate_latitude = (latitude - GPS_last_latitude) * pai / 180 * (Rm_GPS + altitude) + GPS_calculate_latitude;

    GPS_last_longitude = longitude;
    GPS_last_latitude = latitude;
    GPS_last_height = altitude;

    xyz[0] = GPS_calculate_longitude;
    xyz[1] = GPS_calculate_latitude;
    xyz[2] = altitude;
}
