#ifndef VISUALIZATION_H
#define VISUALIZATION_H
#include "gviewer.h"
#include "trans.h"

int visualize_vehicle(const Eigen::Vector3d enu, 
                      const Eigen::Vector3d att, 
                      std::vector<VisualizedInstance>& vis_instances);

#endif // VISUALIZATION_H
