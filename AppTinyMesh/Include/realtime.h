#pragma once

#include "shader-api.h"
#include "box.h"
#include "ray.h"
#include "camera.h"

#include "mesh.h"
#include "meshcolor.h"

#include <QtCore/QMap>

// Utility class for profiling CPU & GPU
typedef std::chrono::time_point<std::chrono::high_resolution_clock> MyChrono;
class RenderingProfiler
{
public:
  bool enabled = false;			//!< Flag linked to UI.

  GLuint query;					//!< GL Query for stats
  GLuint64 elapsedTimeGPU;		//!< GPU rendering time for a frame.

  int nbframes = 0;				//!< CPU Frame counter.
  MyChrono start;					//!< CPU profiler.
  double msPerFrame = 0;			//!< Recorded info.
  double framePerSecond = 0;		//!< Recorded info.

  /*!
  \brief Init the profiler. Only has to be done once in the program.
  */
  inline void Init()
  {
    glGenQueries(1, &query);
    start = std::chrono::high_resolution_clock::now();
  }

  /*!
  \brief Starts profiling the GPU if enabled.
  */
  inline void BeginGPU()
  {
    if (enabled)
      glBeginQuery(GL_TIME_ELAPSED, query);
  }

  /*!
  \brief Ends the GPU profiling if enabled.
  */
  inline void EndGPU()
  {
    if (enabled)
    {
      glEndQuery(GL_TIME_ELAPSED);
      int done = 0;
      while (!done)
        glGetQueryObjectiv(query, GL_QUERY_RESULT_AVAILABLE, &done);
      glGetQueryObjectui64v(query, GL_QUERY_RESULT, &elapsedTimeGPU);
    }
  }

  /*!
  \brief Update the CPU profiling.
  */
  inline void Update()
  {
    nbframes++;
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
    const double seconds = static_cast<double>(microseconds) / 1000000.0;
    if (seconds >= 1.0)
    {
      msPerFrame = seconds * 1000.0 / nbframes;
      framePerSecond = nbframes / seconds;
      nbframes = 0;
      start = std::chrono::high_resolution_clock::now();
    }
  }
};

enum class MeshMaterial
{
  Normal = 0,
  Color = 1,
};

enum class MeshShading
{
  Triangles = 0,
  Lines = 1,
};

class MeshWidget : public QOpenGLWidget
{
  // Must include this if you use Qt signals/slots
  Q_OBJECT
protected:
  class MeshGL
  {
  public:
    bool enabled;				//!< Render flag. Mesh is not rendered if enabled equals false.
    GLuint vao;					//!< Mesh VAO.
    GLuint fullBuffer;			//!< Mesh buffer. Contains 3D normals, 2D vertices and heights.
    GLuint indexBuffer;			//!< Mesh index buffer.
    int triangleCount;			//!< Triangle count to draw.
    float TRSMatrix[16];		//!< Translation-Rotation-Scale Matrix.
    Box bbox;					//!< Bounding box of the mesh.

    MeshShading shading;		//!< Render flag.
    MeshMaterial material;		//!< Render flag.
    bool useWireframe;			//!< Render flag.

  public:
    MeshGL();
    MeshGL(const Mesh& mesh, const Vector& position = Vector::Null);
    MeshGL(const MeshColor& mesh, const Vector& position = Vector::Null);

    void Delete();
    void SetFrame(const Vector& position);
  };

  typedef QMap<QString, MeshGL*>::iterator MeshIterator;

protected:
  // Scene
  int x0, y0;
  bool perspectiveProjection = true;
  double cameraOrthoSize = 100.0;
  Camera camera;
  bool MoveAt = false;
  Vector currentAt = Vector::Null;
  Vector toAt = Vector::Null;
  int stepAt = 0;

  // Meshes
  GLuint mainShaderProgram;
  QMap<QString, MeshGL*> objects;

  // Skybox
  GLuint skyboxShader = 0;
  GLuint skyboxVAO = 0;

  // Profiling
  RenderingProfiler profiler;

public:
  MeshWidget();
  ~MeshWidget();

  void AddMesh(const QString&, const Mesh&, const Vector & = Vector::Null);
  void AddMesh(const QString&, const MeshColor&, const Vector & = Vector::Null);
  void DeleteMesh(const QString&);
  void ClearAll();

  void UpdateMesh(const QString&, const Vector&);
  void EnableMesh(const QString&);
  void DisableMesh(const QString&);

  Ray ComputeRay(const QPoint&) const;
  void SetCamera(const Camera&);

  void SetCameraMode(bool);
  void SetNearAndFarPlane(double, double);
  void SaveScreen(int = 1280, int = 1280);
  QPoint GetMousePosition() const;

  void SetMaterial(const QString&, MeshMaterial);
  void SetMaterialGlobal(MeshMaterial);
  void UseWireframe(const QString&, bool);
  void UseWireframeGlobal(bool);
  void SetShading(const QString&, MeshShading);
  void SetShadingGlobal(MeshShading);

private:
  void _InternalGetMouseGlobalPosition(QMouseEvent* e, int& x0, int& y0) const;

protected:
  virtual void initializeGL();
  virtual void resizeGL(int, int);
  virtual void paintGL();
  virtual void RenderStats();

signals:
  void _signalUpdate();
  void _signalMouseMoveEdit(QMouseEvent*);
  void _signalMouseMove(QMouseEvent*);
  void _signalMouseRelease();
  void _signalEditSceneLeft(const Ray&);
  void _signalEditSceneRight(const Ray&);

public slots:
  virtual void mousePressEvent(QMouseEvent*);
  virtual void mouseReleaseEvent(QMouseEvent*);
  virtual void mouseDoubleClickEvent(QMouseEvent*);
  virtual void mouseMoveEvent(QMouseEvent*);
  virtual void wheelEvent(QWheelEvent*);
  virtual void keyPressEvent(QKeyEvent*);
  virtual void keyReleaseEvent(QKeyEvent*);
};

