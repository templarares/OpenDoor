#include "OpenDoor_Initial.h"

#include "../OpenDoor.h"

void OpenDoor_Initial::configure(const mc_rtc::Configuration & config)
{
}

void OpenDoor_Initial::start(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<OpenDoor &>(ctl_);
  ctl.gui()->addElement({}, mc_rtc::gui::Button("Open door", [this]() { openDoor_ = true; }));
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
