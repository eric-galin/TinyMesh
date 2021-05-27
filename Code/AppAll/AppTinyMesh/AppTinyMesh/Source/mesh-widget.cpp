#include "realtime.h"

#include "meshcolor.h"

#include <iostream>

#include <QtWidgets/QApplication>
#include <QtGui/QKeyEvent>
#include <QtGui/QMouseEvent>
#include <QtOpenGL/QGLWidget>
#include <QtCore/qdatetime.h>

/*!
\brief Default constructor.
*/
MeshWidget::MeshGL::MeshGL()
{
	enabled = true;
	useWireframe = false;
	shading = MeshShading::Triangles;
	material = MeshMaterial::Normal;

	vao = 0;
	fullBuffer = 0;
	indexBuffer = 0;
	triangleCount = 0;
	SetFrame(Vector::Null);
}

/*!
\brief Constructor from a Mesh and a frame scaled.
*/
MeshWidget::MeshGL::MeshGL(const Mesh& mesh, const Vector& position) : MeshGL()
{
	SetFrame(position);
	bbox = mesh.GetBox();

	// Compute plain arrays of sorted vertices & normals
	QVector<int> vertexIndexes = mesh.VertexIndexes();
	QVector<int> normalIndexes = mesh.NormalIndexes();
	assert(vertexIndexes.size() == normalIndexes.size());

	int nbVertex = vertexIndexes.size();
	int singleBufferSize = nbVertex * 3;
	float* vertices = new float[singleBufferSize];
	float* normals = new float[singleBufferSize];
	for (int i = 0; i < nbVertex; i++)
	{
		int indexVertex = vertexIndexes[i];
		int indexNormal = normalIndexes[i];

		Vector vertex = mesh.Vertex(indexVertex);
		vertices[i * 3 + 0] = float(vertex[0]);
		vertices[i * 3 + 1] = float(vertex[1]);
		vertices[i * 3 + 2] = float(vertex[2]);

		Vector normal = mesh.Normal(indexNormal);
		normals[i * 3 + 0] = float(normal[0]);
		normals[i * 3 + 1] = float(normal[1]);
		normals[i * 3 + 2] = float(normal[2]);
	}
	// Indices are now sorted
	int* indices = new int[nbVertex];
	for (int i = 0; i < nbVertex; i++)
		indices[i] = i;
	triangleCount = nbVertex;

	// Generate vao & buffers
	if (vao == 0)
		glGenVertexArrays(1, &vao);
	if (fullBuffer == 0)
		glGenBuffers(1, &fullBuffer);
	if (indexBuffer == 0)
		glGenBuffers(1, &indexBuffer);


	glBindVertexArray(vao);
	size_t fullSize = sizeof(float) * singleBufferSize
		+ sizeof(float) * singleBufferSize;
	glBindBuffer(GL_ARRAY_BUFFER, fullBuffer);
	glBufferData(GL_ARRAY_BUFFER, fullSize, nullptr, GL_STATIC_DRAW);

	// Vertices(0)
	size_t size = 0;
	size_t offset = 0;
	size = sizeof(float) * singleBufferSize;
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, vertices);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (const void*)offset);
	glEnableVertexAttribArray(0);

	// Normals(1)
	offset = offset + size;
	size = sizeof(float) * singleBufferSize;
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, normals);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (const void*)offset);
	glEnableVertexAttribArray(1);

	// Triangles
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * nbVertex, indices, GL_STATIC_DRAW);

	// Free data
	delete[] vertices;
	delete[] normals;
	delete[] indices;
}

/*!
\brief Constructor from a MeshColor and a frame scaled.
*/
MeshWidget::MeshGL::MeshGL(const MeshColor& mesh, const Vector& fr) : MeshGL()
{
	SetFrame(fr);
	bbox = mesh.GetBox();

	// Compute plain arrays of sorted vertices & normals
	QVector<int> vertexIndexes = mesh.VertexIndexes();
	QVector<int> normalIndexes = mesh.NormalIndexes();
	QVector<int> colorIndexes = mesh.ColorIndexes();
	assert(vertexIndexes.size() == normalIndexes.size());

	int nbVertex = vertexIndexes.size();
	int singleBufferSize = nbVertex * 3;
	float* vertices = new float[singleBufferSize];
	float* normals = new float[singleBufferSize];
	float* colors = new float[singleBufferSize];
	for (int i = 0; i < nbVertex; i++)
	{
		int indexVertex = vertexIndexes[i];
		int indexNormal = normalIndexes[i];
		int indexColor = colorIndexes[i];

		Vector vertex = mesh.Vertex(indexVertex);
		vertices[i * 3 + 0] = float(vertex[0]);
		vertices[i * 3 + 1] = float(vertex[1]);
		vertices[i * 3 + 2] = float(vertex[2]);

		Vector normal = mesh.Normal(indexNormal);
		normals[i * 3 + 0] = float(normal[0]);
		normals[i * 3 + 1] = float(normal[1]);
		normals[i * 3 + 2] = float(normal[2]);

		Color color = mesh.GetColor(indexColor);
		colors[i * 3 + 0] = float(color[0]);
		colors[i * 3 + 1] = float(color[1]);
		colors[i * 3 + 2] = float(color[2]);
	}
	// Indices are now sorted
	int* indices = new int[nbVertex];
	for (int i = 0; i < nbVertex; i++)
		indices[i] = i;
	triangleCount = nbVertex;

	// Generate vao & buffers
	if (vao == 0)
		glGenVertexArrays(1, &vao);
	if (fullBuffer == 0)
		glGenBuffers(1, &fullBuffer);
	if (indexBuffer == 0)
		glGenBuffers(1, &indexBuffer);

	glBindVertexArray(vao);
	size_t fullSize =
		sizeof(float) * singleBufferSize	// Vertices
		+ sizeof(float) * singleBufferSize	// Normals
		+ sizeof(float) * singleBufferSize;	// Colors
	glBindBuffer(GL_ARRAY_BUFFER, fullBuffer);
	glBufferData(GL_ARRAY_BUFFER, fullSize, nullptr, GL_STATIC_DRAW);

	// Vertices(0)
	size_t size = 0;
	size_t offset = 0;
	size = sizeof(float) * singleBufferSize;
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, vertices);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (const void*)offset);
	glEnableVertexAttribArray(0);

	// Normals(1)
	offset = offset + size;
	size = sizeof(float) * singleBufferSize;
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, normals);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (const void*)offset);
	glEnableVertexAttribArray(1);

	// Colors(2)
	offset = offset + size;
	size = sizeof(float) * singleBufferSize;
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, colors);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (const void*)offset);
	glEnableVertexAttribArray(2);

	// Triangles
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * nbVertex, indices, GL_STATIC_DRAW);

	// Free data
	delete[] vertices;
	delete[] normals;
	delete[] colors;
	delete[] indices;
}

/*!
\brief Delete all opengl buffers.
*/
void MeshWidget::MeshGL::Delete()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &fullBuffer);
	glDeleteBuffers(1, &indexBuffer);
}

/*!
\brief
*/
void MeshWidget::MeshGL::SetFrame(const Vector& fr)
{
	// Rotation and scale
	TRSMatrix[0] = 1.0f;
	TRSMatrix[1] = 0.0f;
	TRSMatrix[2] = 0.0f;
	TRSMatrix[4] = 0.0f;
	TRSMatrix[5] = 1.0f;
	TRSMatrix[6] = 0.0f;
	TRSMatrix[8] = 0.0f;
	TRSMatrix[9] = 0.0f;
	TRSMatrix[10] = 1.0f;
	
	// Translation
	TRSMatrix[12] = fr[0];
	TRSMatrix[13] = fr[1];
	TRSMatrix[14] = fr[2];
	
	// Shear
	TRSMatrix[3] = TRSMatrix[7] = TRSMatrix[11] = 0.0;

	// Scale
	TRSMatrix[15] = 1.0;
}


/*!
\brief Default constructor.
*/
MeshWidget::MeshWidget()
{
	perspectiveProjection = true;
	cameraOrthoSize = 100.0f;
}

/*!
\brief Destructor.
*/
MeshWidget::~MeshWidget()
{
	// Destroy all meshes
	ClearAll();

	// Release shader
	release_program(mainShaderProgram);
}

/*!
\brief Initialize OpenGL, shaders and a camera centered at origin.
*/
void MeshWidget::initializeGL()
{
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "Error : " << glewGetErrorString(err) << std::endl;
		std::cin.get();
		exit(-1);
	}

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Disable vsync for proper performance measurements
	QGLFormat fmt;
	fmt.setSwapInterval(0);
	QGLFormat::setDefaultFormat(fmt);

	// Shader/Camera/Profiler
	QString pPath = "./";
	if (pPath.isEmpty())
	{
		std::cout << "TerrainMeshWidget::initializeGL() : variable d'environnement MAYADIR non d�fini" << std::endl;
		std::cin.get();
		exit(-1);
	}
	QString fullPath = pPath + QString("/Shaders/mesh.glsl");
	QByteArray ba = fullPath.toLocal8Bit();
	mainShaderProgram = read_program(ba.data());
	camera = Camera(Vector(-10.0),Vector(0.0));
	SetNearAndFarPlane(1.0, 10000.0);
	profiler.Init();

	// Sky
	fullPath = pPath + QString("/Shaders/skybox.glsl");
	ba = fullPath.toLocal8Bit();
	skyboxShader = read_program(ba.data());
	glGenVertexArrays(1, &skyboxVAO);
}

/*!
\brief Resize window.
\param w, h Width and height.
*/
void MeshWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, (GLint)w, (GLint)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (perspectiveProjection)
		gluPerspective(Math::RadianToDegree(camera.GetAngleOfViewV(w, h)), (GLdouble)w / (GLdouble)h, camera.GetNear(), camera.GetFar());
	else
		glOrtho(-cameraOrthoSize, cameraOrthoSize, -cameraOrthoSize, cameraOrthoSize, camera.GetNear(), camera.GetFar());
}

/*!
\brief Renders the scene.
*/
void MeshWidget::paintGL()
{
	// Custom update from user
	emit _signalUpdate();

	// Clear
	glClearColor(1.0f, 1.0f, 1.0f, 1.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Move camera
	if (MoveAt)
	{
		if (stepAt < 15)
		{
			stepAt++;
			double alpha = double(stepAt) / 15.;
			camera.SetAt(currentAt * (1. - alpha) + toAt * (alpha));
		}
		else
			MoveAt = false;
	}
	gluLookAt(camera.Eye()[0], camera.Eye()[1], camera.Eye()[2], camera.At()[0], camera.At()[1], camera.At()[2], camera.Up()[0], camera.Up()[1], camera.Up()[2]);

	// Sky
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glUseProgram(skyboxShader);
	glBindVertexArray(skyboxVAO);
	glUniform3f(0, camera.Eye()[0], camera.Eye()[1], camera.Eye()[2]);
	glUniform3f(1, camera.At()[0], camera.At()[1], camera.At()[2]);
	glUniform3f(2, camera.Up()[0], camera.Up()[1], camera.Up()[2]);
	glUniform2f(3, width(), height());
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	// Draw meshes
	profiler.BeginGPU();
	GLfloat ModelViewMatrix[16];
	GLfloat ProjectionMatrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, ModelViewMatrix);
	glGetFloatv(GL_PROJECTION_MATRIX, ProjectionMatrix);
	glUseProgram(mainShaderProgram);

	// Shared uniforms
	glUniformMatrix4fv(glGetUniformLocation(mainShaderProgram, "ModelViewMatrix"), 1, 0, ModelViewMatrix);
	glUniformMatrix4fv(glGetUniformLocation(mainShaderProgram, "ProjectionMatrix"), 1, 0, ProjectionMatrix);

	for (MeshIterator i = objects.begin(); i != objects.end(); i++)
	{
		if (!i.value()->enabled)
			continue;

		// Uniforms
		glUniform2f(glGetUniformLocation(mainShaderProgram, "WIN_SCALE"), width() / 2.0f, height() / 2.0f);
		glUniformMatrix4fv(glGetUniformLocation(mainShaderProgram, "TRSMatrix"), 1, GL_FALSE, &i.value()->TRSMatrix[0]);
		glUniform1i(glGetUniformLocation(mainShaderProgram, "useWireframe"), i.value()->useWireframe ? 1 : 0);
		glUniform1i(glGetUniformLocation(mainShaderProgram, "material"), (int)i.value()->material);
		glUniform1i(glGetUniformLocation(mainShaderProgram, "shading"), (int)i.value()->shading);

		// Draw
		glBindVertexArray(i.value()->vao);
		glDrawElements(GL_TRIANGLES, (GLsizei)i.value()->triangleCount, GL_UNSIGNED_INT, 0);
	}
	profiler.EndGPU();

	// CPU Profiling
	if (profiler.enabled)
	{
		profiler.Update();
		RenderStats();
	}

	// Schedule next draw
	update();
}

/*!
\brief Add a new mesh in the scene.
\param mesh new mesh
\param frame mesh frame, identity by default.
*/
void MeshWidget::AddMesh(const QString& name, const Mesh& mesh, const Vector& frame)
{
	makeCurrent();
	objects.insert(name, new MeshGL(mesh, frame));
}

/*!
\brief Add a new colored mesh in the scene.
\param mesh new colored mesh
\param frame mesh frame, identity by default.
*/
void MeshWidget::AddMesh(const QString& name, const MeshColor& mesh, const Vector& frame)
{
	makeCurrent();
	objects.insert(name, new MeshGL(mesh, frame));
}

/*!
\brief Delete a mesh in the scene from its name.
\param name mesh name
*/
void MeshWidget::DeleteMesh(const QString& name)
{
	makeCurrent();
	if (objects.contains(name))
	{
		objects[name]->Delete();
		objects.remove(name);
	}
}

/*!
\brief Updates the transform of a mesh given its name.
\param name mesh name
\param frame new frame
*/
void MeshWidget::UpdateMesh(const QString& name, const Vector& frame)
{
	makeCurrent();
	if (objects.contains(name))
		objects[name]->SetFrame(frame);
}

/*!
\brief Enable a mesh given its name.
\param name mesh name
*/
void MeshWidget::EnableMesh(const QString& name)
{
	if (objects.contains(name))
		objects[name]->enabled = true;
}

/*!
\brief Disable a mesh given its name. The mesh will not be rendered until it's enabled again.
\param name mesh name
*/
void MeshWidget::DisableMesh(const QString& name)
{
	if (objects.contains(name))
		objects[name]->enabled = false;
}

/*!
\brief Destroys all mesh objects in the scene.
*/
void MeshWidget::ClearAll()
{
	makeCurrent();
	for (MeshIterator i = objects.begin(); i != objects.end(); i++)
	{
		i.value()->Delete();
		delete i.value();
	}
	objects.clear();
}

/*!
\brief Computes a ray from a pixel
\param pix pixel coordinates
*/
Ray MeshWidget::ComputeRay(const QPoint& pix) const
{
	return camera.PixelToRay(pix.x(), pix.y(), this->width(), this->height());
}

/*!
\brief Set the camera for the widget
\param cam new camera
*/
void MeshWidget::SetCamera(const Camera& cam)
{
	makeCurrent();

	camera = cam;
	camera.SetPlanes(nearplane, farplane);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (perspectiveProjection)
		gluPerspective(Math::RadianToDegree(camera.GetAngleOfViewV(width(), height())), (GLdouble)width() / (GLdouble)height(), camera.GetNear(), camera.GetFar());
	else
		glOrtho(-cameraOrthoSize, cameraOrthoSize, -cameraOrthoSize, cameraOrthoSize, camera.GetNear(), camera.GetFar());
}

/*!
\brief Set the near and far clipping planes of the camera.
\param n,f Clipping plane distances.
*/
void MeshWidget::SetNearAndFarPlane(double n,double f)
{
	makeCurrent();
	nearplane = n;
	farplane = f;

	camera.SetPlanes(nearplane, farplane);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (perspectiveProjection)
		gluPerspective(Math::RadianToDegree(camera.GetAngleOfViewV(width(), height())), (GLdouble)width() / (GLdouble)height(), camera.GetNear(), camera.GetFar());
	else
		glOrtho(-cameraOrthoSize, cameraOrthoSize, -cameraOrthoSize, cameraOrthoSize, camera.GetNear(), camera.GetFar());
}

/*!
\brief Get the current camera of the scene.
*/
Camera MeshWidget::GetCamera() const
{
	return camera;
}

/*!
\brief Set the camera mode (perspective or orthographic).
\param perspective
*/
void MeshWidget::SetCameraMode(bool perspective)
{
	makeCurrent();
	perspectiveProjection = perspective;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (perspectiveProjection)
		gluPerspective(Math::RadianToDegree(camera.GetAngleOfViewV(width(), height())), (GLdouble)width() / (GLdouble)height(), camera.GetNear(), camera.GetFar());
	else
		glOrtho(-cameraOrthoSize, cameraOrthoSize, -cameraOrthoSize, cameraOrthoSize, camera.GetNear(), camera.GetFar());
}

/*!
\brief Changes the material for a mesh given its name.
\param name mesh name
\param mat the new material
*/
void MeshWidget::SetMaterial(const QString& name, MeshMaterial mat)
{
	if (objects.contains(name))
		objects[name]->material = mat;
}

/*!
\brief Changes the material for all meshes.
\param mat the new material
*/
void MeshWidget::SetMaterialGlobal(MeshMaterial mat)
{
	for (MeshIterator i = objects.begin(); i != objects.end(); i++)
		i.value()->material = mat;
}

/*!
\brief Changes the wireframe render flag for a mesh given its name.
\param name mesh name
\param wireframe new wireframe flag value
*/
void MeshWidget::UseWireframe(const QString& name, bool wireframe)
{
	if (objects.contains(name))
		objects[name]->useWireframe = wireframe;
}

/*!
\brief Changes the wireframe render flag for all meshes.
\param u new value for wireframe flag.
*/
void MeshWidget::UseWireframeGlobal(bool wireframe)
{
	for (MeshIterator i = objects.begin(); i != objects.end(); i++)
		i.value()->useWireframe = wireframe;
}

/*!
\brief Changes the shading mode for a given mesh.
\param shading new shading mode
*/
void MeshWidget::SetShading(const QString& name, MeshShading shading)
{
	if (objects.contains(name))
		objects[name]->shading = shading;
}

/*!
\brief Changes the shading mode for all meshes.
\param shading new shading mode
*/
void MeshWidget::SetShadingGlobal(MeshShading shading)
{
	for (MeshIterator i = objects.begin(); i != objects.end(); i++)
		i.value()->shading = shading;
}


/*!
\brief Capture the rendering viewport and save it to disk.
*/
void MeshWidget::SaveScreen(int w, int h)
{
	QSize qs = size();
	resize(w, h);
	QImage image(size(), QImage::Format_ARGB32);

	// Date and time
	QDate date = QDate::currentDate();
	QTime time = QTime::currentTime();

	// Set name according to date and time
	QString name = QString("../screen-%1%2%3-%4%5%6.png")
		.arg(date.year(), 4)
		.arg(date.month(), 2, 10, QChar('0'))
		.arg(date.day(), 2, 10, QChar('0'))
		.arg(time.hour(), 2, 10, QChar('0'))
		.arg(time.minute(), 2, 10, QChar('0'))
		.arg(time.second(), 2, 10, QChar('0'));

	// Get image
	image = grabFramebuffer();

	// Save
	image.save(name, "PNG");
	resize(qs);
}

/*!
\brief Returns the current mouse position.
*/
QPoint MeshWidget::GetMousePosition() const
{
	return QPoint(x0, y0);
}

/*!
\brief Render the stats panel of the widget.
*/
void MeshWidget::RenderStats()
{
	// We need to unbind VAO and program for now because it causes problem with below command.
	glBindVertexArray(0);
	glUseProgram(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	QPainter painter;
	painter.begin(this);
	painter.setRenderHint(QPainter::Antialiasing);
	QPen penLineGrey(QColor(50, 50, 50));
	QPen penLineWhite(QColor(250, 250, 250));

	const int bX = 10;
	const int bY = 10;
	const int sizeX = 200;
	const int sizeY = 65;

	// Background
	painter.setPen(penLineGrey);
	painter.fillRect(QRect(bX, bY, sizeX, sizeY), QColor(0, 0, 255, 25));
	painter.drawRect(bX, bY, sizeX, sizeY);

	// Text
	QFont f1, f2;
	f1.setBold(true);
	painter.setFont(f1);
	painter.setPen(penLineWhite);
	painter.drawText(10 + 5, bY + 10 + 5, "Statistics");
	painter.setFont(f2);
	painter.drawText(10 + 5, bY + 10 + 20, "CPU FPS:\t" + QString::number(profiler.framePerSecond));
	painter.drawText(10 + 5, bY + 10 + 35, "CPU Frame:\t" + QString::number(profiler.msPerFrame) + "ms");
	painter.drawText(10 + 5, bY + 10 + 50, "GPU:\t" + QString::number(profiler.elapsedTimeGPU / 1000000.0) + "ms");

	painter.end();

	// Reset GL depth test
	glEnable(GL_DEPTH_TEST);
}

/*!
\brief Process mouse click events.
\param e Events.
*/
void MeshWidget::mousePressEvent(QMouseEvent* e)
{
	x0 = e->globalX();
	y0 = e->globalY();
	if (e->modifiers() & Qt::ControlModifier)
	{
		if (e->buttons() == Qt::LeftButton)
			emit _signalEditSceneLeft(ComputeRay(e->pos()));
		else if (e->buttons() == Qt::RightButton)
			emit _signalEditSceneRight(ComputeRay(e->pos()));
		emit _signalMouseMoveEdit(e);
	}
}

/*!
\brief Process the mouse release events.
\param e Events.
*/
void MeshWidget::mouseReleaseEvent(QMouseEvent*)
{
	QApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
	emit _signalMouseRelease();
	update();
}

/*!
\brief Process the mouse double click events.
\param e Events.
*/
void MeshWidget::mouseDoubleClickEvent(QMouseEvent* e)
{
	emit _signalMouseMove(e);
	update();
}

/*!
\brief Process the mouse move events.
\param e Events
*/
void MeshWidget::mouseMoveEvent(QMouseEvent* e)
{
	int x = e->globalX();
	int y = e->globalY();
	if ((e->modifiers() & Qt::AltModifier))
	{
		// Displacement mode 
		double MoveScale = Norm(camera.View()) * 0.015 * 0.05;
		if (e->buttons() & Qt::LeftButton)
		{
			// Alt + Left Mouse Move    : Rotation 
			camera.LeftRightRound((x0 - x) * 0.01);
			camera.UpDownRound((y0 - y) * 0.005);
		}
		else if (e->buttons() & Qt::RightButton)
		{
			// Alt + Right Mouse Move   : Forward and Backward
			camera.BackForth((y - y0) * MoveScale);
			QApplication::setOverrideCursor(QCursor(Qt::SplitVCursor));
		}
		else if (e->buttons() & Qt::MiddleButton)
		{
			// Alt + Left Mouse Move    : Plan displacement
			camera.LeftRightHorizontal((x - x0) * MoveScale);
			camera.UpDownVertical((y - y0) * MoveScale);
			QApplication::setOverrideCursor(QCursor(Qt::SizeAllCursor));
		}

		x0 = e->globalX();
		y0 = e->globalY();

		emit _signalMouseMove(e);
	}
	if (e->modifiers() & Qt::ControlModifier)
	{
		emit _signalMouseMoveEdit(e);

		x0 = e->globalX();
		y0 = e->globalY();
	}
}

/*!
\brief Process the mouse wheel events.
\param e Events
*/
void MeshWidget::wheelEvent(QWheelEvent* e)
{
	if (!(e->modifiers() & Qt::ControlModifier) && !(e->modifiers() & Qt::ShiftModifier))
	{
		double MoveScale = Norm(camera.View()) * 0.025;
		if (e->delta() > 0)
		{
			cameraOrthoSize -= MoveScale;
			camera.BackForth(MoveScale);
		}
		else
		{
			cameraOrthoSize += MoveScale;
			camera.BackForth(-MoveScale);
		}

		// Apply changes to projection matrix if we are in orthographic mode
		if (!perspectiveProjection)
		{
			makeCurrent();
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-cameraOrthoSize, cameraOrthoSize, -cameraOrthoSize, cameraOrthoSize, camera.GetNear(), camera.GetFar());
		}
	}
	update();
}

/*!
\brief Process the keyboard press events.
\param e Events
*/
void MeshWidget::keyPressEvent(QKeyEvent* e)
{
	switch (e->key())
	{
		// F1: screenshot in the app folder
	case Qt::Key_F1:
		SaveScreen();
		break;
	case Qt::Key_S:
		// Alt + S: Statistics
		if (e->modifiers() & Qt::AltModifier)
			profiler.enabled = !profiler.enabled;
		break;
	default:
		QOpenGLWidget::keyPressEvent(e);
	}
}

/*!
\brief Process the keyboard release events.
\param e Events
*/
void MeshWidget::keyReleaseEvent(QKeyEvent* e)
{
	QOpenGLWidget::keyReleaseEvent(e);
	update();
}
