#pragma once
#include <osg/ref_ptr>
#include <osg/Geode> 
#include <osg/Geometry>
#include <osg/Group>
#include <osg/MatrixTransform> 

#include <osgGA/CameraManipulator>
#include <osgViewer/Viewer>
struct updateAccumulatedMatrix : public osg::NodeCallback
{
    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
    {
        matrix = osg::computeWorldToLocal(nv->getNodePath());
        traverse(node, nv);
    }
    osg::Matrix matrix;
};

struct transformAccumulator
{
public:
    transformAccumulator();
    bool attachToGroup(osg::Group* g);
    osg::Matrix getMatrix();
protected:
    osg::ref_ptr<osg::Group> parent;
    osg::Node* node;
    updateAccumulatedMatrix* mpcb;
};

class followNodeMatrixManipulator : public osgGA::CameraManipulator
{
public:
    followNodeMatrixManipulator(transformAccumulator* ta);
    bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
    void updateTheMatrix();
    virtual void setByMatrix(const osg::Matrixd& mat) { theMatrix = mat; }
    virtual void setByInverseMatrix(const osg::Matrixd& mat) {}
    virtual osg::Matrixd getInverseMatrix() const;
    virtual osg::Matrixd getMatrix() const;

   


    void ChangePosition(osg::Vec3 vec3Delta);

protected:
    ~followNodeMatrixManipulator() {}
  
    transformAccumulator* worldCoordinatesOfNode;
    osg::Matrixd theMatrix;
    osg::Vec3					m_vecRotation,		m_vecPosition;
};


