#include "visualization.h"

int visualize_vehicle(const Eigen::Vector3d enu, const Eigen::Vector3d att, std::vector<VisualizedInstance>& vis_instances) {
	VisualizedInstance vis_instance_vehicle;
	vis_instance_vehicle.type = VisualizedPatchType::BOX;
	vis_instance_vehicle.color[0] = 0.0;
	vis_instance_vehicle.color[1] = 0.0;
	vis_instance_vehicle.color[2] = 0.0;
	vis_instance_vehicle.t = enu;
	vis_instance_vehicle.R = eul2rot(att);
	vis_instance_vehicle.h = 1.753;
	vis_instance_vehicle.l = 1.849;
	vis_instance_vehicle.w = 4.690;
	vis_instances.push_back(vis_instance_vehicle);
	return 0;
}
