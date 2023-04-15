#include <ros/ros.h>
#include <nodelet/nodelet.h>
#include <pluginlib/class_list_macros.h>
#include <std_msgs/String.h>
#include <plugin_lecture/Position.h>
#include <plugin_lecture/Image.h>
#include <boost/shared_ptr.hpp>
namespace plugin_lecture
{
  class plugin_nodelet_listener : public nodelet::Nodelet
  {
  public:
    virtual void onInit();
    void chatter_callback(const boost::shared_ptr<plugin_lecture::Image const> &msg);

  private:
    ros::NodeHandle nh_;
    ros::Subscriber sub_;
  };

  void plugin_nodelet_listener::onInit()
  {
    NODELET_INFO("Listener Init");
    nh_ = getNodeHandle();
    sub_ = nh_.subscribe("chatter", 10, &plugin_nodelet_listener::chatter_callback, this);
  }

  void plugin_nodelet_listener::chatter_callback(const boost::shared_ptr<plugin_lecture::Image const> &msg)
  {
    NODELET_INFO("recieve: %d %d %d", msg->position.x, msg->position.y, msg->position.z);
  }
} // namespace plugin_lecture
PLUGINLIB_EXPORT_CLASS(plugin_lecture::plugin_nodelet_listener, nodelet::Nodelet)