#include "transfer.h"

Eigen::Matrix3d askew(const Eigen::Vector3d& v) {
    Eigen::Matrix3d vnx = (Eigen::Matrix3d() <<     0, -v(2),  v(1), 
                                                 v(2),    0 , -v(0), 
                                                -v(1),  v(0),    0 ).finished();
    return vnx;
}

Eigen::Vector3d unskew(const Eigen::Matrix3d& m) {
    return Eigen::Vector3d(m(2, 1), m(0, 2), m(1, 0));
}

Eigen::Vector3d rot2euler(const Eigen::Matrix3d& rot) {
    Eigen::Vector3d euler;
    // euler(0) = atan2(-m(0, 1), m(1, 1));
    // euler(1) = asin(m(2, 1));
    // euler(2) = atan2(-m(2, 0), m(2, 2));
    euler(0) = asin(rot(2, 1));
    euler(1) = atan2(-rot(2, 0), rot(2, 2));
    euler(2) = atan2(-rot(0, 1), rot(1, 1));
    // if (euler(2) > 0 && euler(2) < 180)euler(2) = 2 * glv.PI - euler(2);
    // if (euler(2) > -180 && euler(2) < 0)euler(2) = -euler(2);
    return euler;
}

Eigen::Matrix3d euler2rot(const Eigen::Vector3d& euler) {
    double sp = sin(euler(0)), cp = cos(euler(0));
    double sr = sin(euler(1)), cr = cos(euler(1));
    double sy = sin(euler(2)), cy = cos(euler(2));

    Eigen::Matrix3d rot;
    rot << cy * cr - sy * sp * sr, -sy * cp, cy * sr + sy * sp * cr,
           sy * cr + cy * sp * sr,  cy * cp, sy * sr - cy * sp * cr,
                         -cp * sr,       sp,                cp * cr;
    return rot;
}

Eigen::Matrix3d quat2rot(const Eigen::Vector4d& q) {
    Eigen::Matrix3d R;
    double q0 = q(0), q1 = q(1), q2 = q(2), q3 = q(3);
    R << q0 * q0 + q1 * q1 - q2 * q2 - q3 * q3, 2 * (q1 * q2 - q0 * q3), 2 * (q1 * q3 + q0 * q2),
         2 * (q1 * q2 + q0 * q3), q0 * q0 - q1 * q1 + q2 * q2 - q3 * q3, 2 * (q2 * q3 - q0 * q1),
         2 * (q1 * q3 - q0 * q2), 2 * (q2 * q3 + q0 * q1), q0 * q0 - q1 * q1 - q2 * q2 + q3 * q3;
    return R;
}

Eigen::Vector4d rot2quat(const Eigen::Matrix3d& R) {
    Eigen::Vector4d q;
    double tr = R.trace();
    if (tr > 0) {
        double S = sqrt(tr + 1.0) * 2;
        q <<                0.25 * S,
             (R(2, 1) - R(1, 2)) / S,
             (R(0, 2) - R(2, 0)) / S,
             (R(1, 0) - R(0, 1)) / S;
    } else if ((R(0, 0) > R(1, 1)) && (R(0, 0) > R(2, 2))) {
        double S = sqrt(1.0 + R(0, 0) - R(1, 1) - R(2, 2)) * 2;
        q << (R(2, 1) - R(1, 2)) / S,
                            0.25 * S,
             (R(0, 1) + R(1, 0)) / S,
             (R(0, 2) + R(2, 0)) / S;
    } else if (R(1, 1) > R(2, 2)) {
        double S = sqrt(1.0 + R(1, 1) - R(0, 0) - R(2, 2)) * 2;
        q << (R(0, 2) - R(2, 0)) / S,
             (R(0, 1) + R(1, 0)) / S,
                            0.25 * S,
             (R(1, 2) + R(2, 1)) / S;
    } else {
        double S = sqrt(1.0 + R(2, 2) - R(0, 0) - R(1, 1)) * 2;
        q << (R(1, 0) - R(0, 1)) / S,
             (R(0, 2) + R(2, 0)) / S,
             (R(1, 2) + R(2, 1)) / S,
                            0.25 * S;
    }
    return q;
}
