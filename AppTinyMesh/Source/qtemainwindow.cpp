#include "qte.h"

MainWindow::MainWindow()
{
	// Chargement de l'interface
	uiw.setupUi(this);

	// Chargement du GLWidget
	meshWidget = new MeshWidget;
	QGridLayout* GLlayout = new QGridLayout;
	GLlayout->addWidget(meshWidget, 0, 0);
	GLlayout->setContentsMargins(0, 0, 0, 0);
	uiw.widget_GL->setLayout(GLlayout);

	// Creation des connect
	CreateActions();

	meshWidget->SetCamera(Camera(Vector(639, -604, 76), Vector(0.0, 0.0, 0.0)));
}

MainWindow::~MainWindow()
{
	delete meshWidget;
}

void MainWindow::CreateActions()
{
	// Buttons
	connect(uiw.boxMesh, SIGNAL(clicked()), this, SLOT(BoxMeshExample()));
	connect(uiw.resetcameraButton, SIGNAL(clicked()), this, SLOT(ResetCamera()));
	connect(uiw.wireframe, SIGNAL(clicked()), this, SLOT(UpdateMaterial()));

	// Widget edition
	connect(meshWidget, SIGNAL(_signalEditSceneLeft(const Ray&)), this, SLOT(editingSceneLeft(const Ray&)));
	connect(meshWidget, SIGNAL(_signalEditSceneRight(const Ray&)), this, SLOT(editingSceneRight(const Ray&)));
}

void MainWindow::editingSceneLeft(const Ray&)
{
}

void MainWindow::editingSceneRight(const Ray&)
{
}

void MainWindow::BoxMeshExample()
{
	meshColor = MeshColor(Mesh(Box(Vector(0), 1)));
	UpdateGeometry();
}

void MainWindow::UpdateGeometry()
{
	meshWidget->ClearAll();
	meshWidget->AddMesh("BoxMesh", meshColor);

	uiw.lineEdit->setText(QString::number(meshColor.GetVertices().size()));
	uiw.lineEdit_2->setText(QString::number(meshColor.VertexIndexes().size()));

	UpdateMaterial();
}

void MainWindow::UpdateMaterial()
{
	meshWidget->UseWireframeGlobal(uiw.wireframe->isChecked());
}

void MainWindow::ResetCamera()
{
	meshWidget->SetCamera(Camera(Vector(-10.0), Vector(0.0)));
}
