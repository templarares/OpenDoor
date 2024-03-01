#include "OpenDoor_Initial.h"

#include "../OpenDoor.h"


static void SetInitialPose(mc_control::fsm::Controller & ctl, const sva::PTransformd & pose)
{
  ctl.robot().posW(pose);
  ctl.removeContact({"bit_humanoid", "ground", "LeftFoot", "AllGround"});
  ctl.removeContact({"bit_humanoid", "ground", "RightFoot", "AllGround"});
  ctl.addContact({"bit_humanoid", "ground", "LeftFoot", "AllGround"});
  ctl.addContact({"bit_humanoid", "ground", "RightFoot", "AllGround"});
  //SaveInitialPose(ctl);
}

void OpenDoor_Initial::configure(const mc_rtc::Configuration & config)
{
}

void OpenDoor_Initial::start(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<OpenDoor &>(ctl_);
  ctl.gui()->addElement({}, mc_rtc::gui::Button("Open door", [this]() { openDoor_ = true; }));

  //sync init pose
  sva::PTransformd default_pose;
  {
    const auto & da = ctl.robot().module().default_attitude();
    default_pose.translation() << da[4], da[5], da[6];
    default_pose.rotation() = Eigen::Quaterniond{da[0], da[1], da[2], da[3]}.toRotationMatrix();
  }
  if(ctl.robot().posW() == default_pose)
  {
    mc_rtc::Configuration init_pose_cfg(static_cast<std::string>(ctl.config()("ETC_DIR")) + "/initial_pose.yaml");
    ctl.robot().posW(init_pose_cfg("initial_pose"));
    mc_rtc::log::success("Check if posW is in sync");
  }
}

bool OpenDoor_Initial::run(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<OpenDoor &>(ctl_);
  if(openDoor_)
  {
    output("OpenDoor");
    return true;
  }
  return false;
}

void OpenDoor_Initial::teardown(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<OpenDoor &>(ctl_);
}

EXPORT_SINGLE_STATE("OpenDoor_Initial", OpenDoor_Initial)
