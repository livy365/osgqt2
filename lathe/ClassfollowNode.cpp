#include "ClassfollowNode.h"

#include <osg/ShapeDrawable>

extern osg::ref_ptr < osg::MatrixTransform >basicaxis;
transformAccumulator::transformAccumulator()
{
    parent = NULL;
    node = new osg::Node;
    mpcb = new updateAccumulatedMatrix();
    node->setUpdateCallback(mpcb);
}

osg::Matrix transformAccumulator::getMatrix()
{
    return mpcb->matrix;
}

bool transformAccumulator::attachToGroup(osg::Group* g)
// 注意不要在回调中调用这个函数。
{
    bool success = false;
    if (parent != NULL)
    {
        int n = parent->getNumChildren();
        for (int i = 0; i < n; i++)
        {
            if (node == parent->getChild(i))
            {
                parent->removeChild(i, 1);
                success = true;
            }
        }
        if (!success)
        {
            return success;
        }
    }
    g->addChild(node);
    return true;
}

followNodeMatrixManipulator::followNodeMatrixManipulator(transformAccumulator* ta)
{
    worldCoordinatesOfNode = ta; theMatrix = osg::Matrixd::identity();
    m_vecPosition= osg::Vec3 (0.0, -300.0, 400.0);
    m_vecRotation = osg::Vec3(osg::PI/4,0, 0);
   


    osg::ref_ptr<osg::Cylinder> cy1=new osg::Cylinder;
    
    cy1->setHeight(50);
    cy1->setCenter(osg::Vec3(0, 0, 0));
    cy1->setRadius(20);
    osg::ref_ptr<osg::ShapeDrawable> sd6 = new osg::ShapeDrawable(cy1);
    sd6->setColor(osg::Vec4(1, 0, 0, 0.5));
    osg::ref_ptr<osg::Geode> ball = new osg::Geode;
    osg::ref_ptr<osg::StateSet>ballstate = ball->getOrCreateStateSet();
    ballstate->setMode(GL_BLEND, osg::StateAttribute::ON |
        osg::StateAttribute::PROTECTED);
    ballstate->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
    ball->addDrawable(sd6.get());
    basicaxis->addChild(ball);
}
void followNodeMatrixManipulator::updateTheMatrix()
{
    theMatrix = osg::Matrixd::inverse(worldCoordinatesOfNode->getMatrix());

     basicaxis->setMatrix( osg::Matrixd::translate(m_vecPosition) * theMatrix);
}
osg::Matrixd followNodeMatrixManipulator::getMatrix() const
{
    osg::Matrixd mat;
    mat.makeRotate(m_vecRotation.x(), osg::Vec3(1.0, 0.0, 0.0),
        m_vecRotation.y(), osg::Vec3(0.0, 1.0, 0.0),
        m_vecRotation.z(), osg::Vec3(0.0, 0.0, 1.0));
   
    return mat*osg::Matrixd::translate(m_vecPosition )* theMatrix   ;
}
osg::Matrixd followNodeMatrixManipulator::getInverseMatrix() const
{
        osg::Matrixd mat;
    mat.makeRotate(m_vecRotation.x(), osg::Vec3(1.0, 0.0, 0.0),
        m_vecRotation.y(), osg::Vec3(0.0, 1.0, 0.0),
        m_vecRotation.z(), osg::Vec3(0.0, 0.0, 1.0));

    // 将矩阵从Y轴向上旋转到Z轴向上
    osg::Matrixd m;
  //  m = theMatrix * osg::Matrixd::rotate(-osg::PI_2, osg::Vec3(1, 0, 0));
    m = osg::Matrixd::inverse( mat*osg::Matrixd::translate(m_vecPosition)* theMatrix );
    return m;
}



bool followNodeMatrixManipulator::handle
(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
    switch (ea.getEventType())
    {
    case (osgGA::GUIEventAdapter::FRAME):
    {
        updateTheMatrix();
        return false;
    }

    case osgGA::GUIEventAdapter::KEYDOWN:
    {
        if (ea.getKey() == 'w' || ea.getKey() == 'W')
        {
            ChangePosition(osg::Vec3(6 * cosf(osg::PI_2 + m_vecRotation[2]),6 * sinf(osg::PI_2 + m_vecRotation[2]), 0));
           
        }



        if (ea.getKey() == 's' || ea.getKey() == 'S')
        {
            ChangePosition(osg::Vec3(-6 * cosf(osg::PI_2 + m_vecRotation[2]), -6 * sinf(osg::PI_2 + m_vecRotation[2]), 0));
           
        }
        if (ea.getKey() == 'a' || ea.getKey() == 'A')
        {
            ChangePosition(osg::Vec3(-6 * sinf(osg::PI_2 + m_vecRotation[2]), 6 * cosf(osg::PI_2 + m_vecRotation[2]), 0));
            
        }
        if (ea.getKey() == 'd' || ea.getKey() == 'D')
        {
            ChangePosition(osg::Vec3(6 * sinf(osg::PI_2 + m_vecRotation[2]), -6 * cosf(osg::PI_2 + m_vecRotation[2]), 0));
          
        }
        if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Right) //右旋转
        {
            float temp = m_vecRotation._v[2];
            m_vecRotation._v[2] -= osg::DegreesToRadians(3.0);
            ChangePosition(osg::Vec3(12 * sin(m_vecRotation._v[2]) - 12 * sin(temp), 12 * (1 - cos(m_vecRotation._v[2])) - 12 * (1 - cos(temp)), 0));
        }
        if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Left) //左旋转
        {
            float temp = m_vecRotation._v[2];
            m_vecRotation._v[2] += osg::DegreesToRadians(3.0);
            ChangePosition(osg::Vec3(12 * sin(m_vecRotation._v[2]) - 12 * sin(temp), 12 * (1 - cos(m_vecRotation._v[2])) - 12 * (1 - cos(temp)), 0));
        }
        if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Up) //上旋转
        {
            float temp = m_vecRotation._v[0];
            m_vecRotation._v[0] += osg::DegreesToRadians(3.0);
        }
        if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Down) //下旋转
        {
            float temp = m_vecRotation._v[0];
            m_vecRotation._v[0] -= osg::DegreesToRadians(3.0);
        }

     }


    }
    return false;
}
void followNodeMatrixManipulator::ChangePosition(osg::Vec3 vec3Delta)
{

    
        m_vecPosition += vec3Delta;

   
}