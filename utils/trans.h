#ifndef TRANS_H
#define TRANS_H
#include <Eigen/Core>
#include <fstream>
#define pai 3.14159265358979323846
#define EARTH_RE 6378137.0                            // 地球半径
#define EARTH_F 0.0033528106647474807198455286185206  // 地球扁率
#define EARTH_WIE 0.000072921151467348494572823629331 // 地球自转角速度
#define Finv 298.257223563                            // inverse flattening [-]
#define D2R (pai / 180.0)                             // deg to rad
#define R2D (180.0 / pai)                             // rad to deg

Eigen::Matrix3d askew(const Eigen::Vector3d &v);

Eigen::Matrix3d eul2rot(const Eigen::Vector3d &att);

Eigen::Vector3d rot2eul(const Eigen::Matrix3d &m);

#endif
