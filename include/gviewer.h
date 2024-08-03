#ifndef GVIEWER_H
#define GVIEWER_H
#include <Eigen/Dense>
#include <GLFW/glfw3.h>
#include <vector>
#include <utility>
#include <thread>
#include <mutex>
#include <math.h>
#include <map>
#include <opencv2/opencv.hpp>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

typedef std::vector<std::pair<Eigen::Matrix3d, Eigen::Vector3d>> Frames;
typedef std::vector<Eigen::Vector3d> VPointCloud;

enum VisualizedPatchType { BOX=0,LINE_SEGMENT =1 };

struct VisualizedInstance {
	VisualizedPatchType type;
	double color[3];
	Eigen::Matrix3d R;
	Eigen::Vector3d t;
	double w, l, h;
	std::vector<Eigen::Vector3d> pts;
	std::vector<Eigen::Vector3d> pts_color;
	float alpha = 0.75f;
	float linewidth = 3.0f;
};

class gviewer {
public:
	gviewer();
	~gviewer();
public:
	void Show();
	void ClearView();
	void SetFrames(const Frames& t);
	void SetFrames(const std::vector<Frames>& vt);
	void AddNewFrame(const std::pair<Eigen::Matrix3d, Eigen::Vector3d>& f);

	void SetPointCloud(const VPointCloud& pc);
	void SetPointCloud(const std::vector<VPointCloud>& vpc);
	void SetPointCloudSemantic(const std::vector<VPointCloud>& vpc);
	void SetInstances(const std::vector<VisualizedInstance>& vi);
	void AddNewPoint(const Eigen::Vector3d& p);
	void AddNewPoint(const std::vector<Eigen::Vector3d>& p);

	void SetTrajectory(const VPointCloud& t);
	void SetTrajectory(const std::vector<VPointCloud>& vt);
	void AddNewPos(const Eigen::Vector3d& p);
	void ScreenShot(const std::string& s);
	void SetCenter();
	void Hide();
private:
	void Run();

private:
	static std::vector<gviewer*> vptr;
	GLFWwindow* window;
	std::thread* t;
	std::mutex m_mutex;
	std::vector<VPointCloud> mv_trajectory;
	std::vector<VPointCloud> mv_pointCloud;
	std::vector<Frames> mv_frames;
	std::vector<VPointCloud> mv_pointCloud_semantic;
	std::vector<VisualizedInstance> mv_instances;
	bool need_screenshot = false;
	bool set_center = false;
	std::string screenshot_path = "";
};
#endif
