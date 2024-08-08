#pragma once
#include <Eigen/Core>
#include <Eigen/Dense>

Eigen::Matrix3d askew(const Eigen::Vector3d& v);

Eigen::Vector3d unskew(const Eigen::Matrix3d& m);

Eigen::Vector3d rot2euler(const Eigen::Matrix3d& R);

Eigen::Matrix3d euler2rot(const Eigen::Vector3d& euler);

Eigen::Matrix3d quat2rot(const Eigen::Vector4d& q);

Eigen::Vector4d rot2quat(const Eigen::Matrix3d& R);
