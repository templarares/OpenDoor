#include "OpenDoor_Initial.h"

#include "../OpenDoor.h"

void OpenDoor_Initial::configure(const mc_rtc::Configuration & config)
{
}

void OpenDoor_Initial::start(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<OpenDoor &>(ctl_);
}

bool OpenDoor_Initial::run(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<OpenDoor &>(ctl_);
  output("OK");
  return true;
}

void OpenDoor_Initial::teardown(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<OpenDoor &>(ctl_);
}

EXPORT_SINGLE_STATE("OpenDoor_Initial", OpenDoor_Initial)
