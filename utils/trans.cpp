#include "trans.h"

Eigen::Matrix3d askew(const Eigen::Vector3d &v) {
    Eigen::Matrix3d vnx = (Eigen::Matrix3d() << 0, -v(2), v(1), v(2), 0, -v(0), -v(1), v(0), 0).finished();
    return vnx;
}

Eigen::Matrix3d eul2rot(const Eigen::Vector3d &att) {
    // double sy = sin(att(0)), cy = cos(att(0));
    // double sp = sin(att(1)), cp = cos(att(1));
    // double sr = sin(att(2)), cr = cos(att(2));

    double sp = sin(att(0)), cp = cos(att(0));
    double sr = sin(att(1)), cr = cos(att(1));
    double sy = sin(att(2)), cy = cos(att(2));

    Eigen::Matrix3d m;
    m << cy * cr - sy * sp * sr, -sy * cp, cy * sr + sy * sp * cr,
         sy * cr + cy * sp * sr,  cy * cp, sy * sr - cy * sp * cr,
                       -cp * sr,       sp,                cp * cr;
    return m;
}

Eigen::Vector3d rot2eul(const Eigen::Matrix3d &m) {
    Eigen::Vector3d att;
    // att(0) = atan2(-m(0, 1), m(1, 1));
    // att(1) = asin(m(2, 1));
    // att(2) = atan2(-m(2, 0), m(2, 2));
    att(0) = asin(m(2, 1));
    att(1) = atan2(-m(2, 0), m(2, 2));
    att(2) = atan2(-m(0, 1), m(1, 1));
    // if (att(2) > 0 && att(2) < 180)att(2) = 2 * glv.PI - att(2);
    // if (att(2) > -180 && att(2) < 0)att(2) = -att(2);
    return att;
}
