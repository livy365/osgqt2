#include <osgViewer/Viewer>
#include <osg/ref_ptr>
#include <osg/Geode> 
#include <osg/Group>

class turn_off : public osg::NodeVisitor
{
public:
	turn_off(osg::ref_ptr<osg::Switch> circleswitch)
		: osg::NodeVisitor(
			osg::NodeVisitor::TRAVERSE_ALL_CHILDREN),
		_circleswitch(circleswitch) {}

	virtual void apply(osg::Node& node)
	{
		_node = &node;
		_circleswitch->setChildValue(_node.get(), false);

		// 继续遍历场景图形剩余的部分。
		traverse(node);
	}

protected:
	osg::ref_ptr<osg::Switch> _circleswitch;
	osg::ref_ptr<osg::Node> _node;
};