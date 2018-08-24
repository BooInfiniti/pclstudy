
/*#include "pclvisualizer.h"

pclvisualizer::pclvisualizer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

pclvisualizer::~pclvisualizer()
{

}*/

#include <QFileDialog>
#include <iostream>
#include <vtkRenderWindow.h>
#include "pclvisualizer.h"

PCLVisualizer::PCLVisualizer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//初始化
	initialVtkWidget();
	//连接信号和槽(Qt4中的用法)
	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(onOpen()));
	connect(ui.actionexit, SIGNAL(triggered()), this, SLOT(exit()));
}

PCLVisualizer::~PCLVisualizer()
{

}
void PCLVisualizer::initialVtkWidget()
{
	cloud.reset(new pcl::PointCloud<pcl::PointXYZ>);
	viewer.reset(new pcl::visualization::PCLVisualizer("viewer", false));
	viewer->addPointCloud(cloud, "cloud");

	ui.qvtkWidget->SetRenderWindow(viewer->getRenderWindow());
	viewer->setupInteractor(ui.qvtkWidget->GetInteractor(), ui.qvtkWidget->GetRenderWindow());
	ui.qvtkWidget->update();
}


//读取文本型和二进制型点云数据
void PCLVisualizer::onOpen()
{
	//只能打开PCD文件
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open PointCloud"), ".",
		tr("Open PCD files(*.pcd)"));

	if (!fileName.isEmpty())
	{
		std::string file_name = fileName.toStdString();
		//sensor_msgs::PointCloud2 cloud2;
		pcl::PCLPointCloud2 cloud2;
		//pcl::PointCloud<Eigen::MatrixXf> cloud2;
		Eigen::Vector4f origin;
		Eigen::Quaternionf orientation;
		int pcd_version;
		int data_type;
		unsigned int data_idx;
		int offset = 0;
		pcl::PCDReader rd;
		rd.readHeader(file_name, cloud2, origin, orientation, pcd_version, data_type, data_idx);

		if (data_type == 0)
		{
			pcl::io::loadPCDFile(fileName.toStdString(), *cloud);
		}
		else if (data_type == 2)
		{
			pcl::PCDReader reader;
			reader.read<pcl::PointXYZ>(fileName.toStdString(), *cloud);
		}

		viewer->updatePointCloud(cloud, "cloud");
		viewer->resetCamera();
		ui.qvtkWidget->update();
	}
}
void PCLVisualizer::exit()
{
	this->close();
}