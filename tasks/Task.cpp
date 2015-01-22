/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Task.hpp"
#include <math.h>
#include <raw_io/Analog.hpp>
#include <base/samples/RigidBodyState.hpp>

using namespace inclinometer;


Task::Task(std::string const& name)
    : TaskBase(name)
{
}

Task::Task(std::string const& name, RTT::ExecutionEngine* engine)
    : TaskBase(name, engine)
{
}

Task::~Task()
{
}



/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See Task.hpp for more detailed
// documentation about them.

bool Task::configureHook()
{ 
    if (! TaskBase::configureHook())
        return false;
    return true;
}
bool Task::startHook()
{
    if (! TaskBase::startHook())
        return false;
    return true;
}
void Task::updateHook()
{
    raw_io::Analog voltage_input;
    while(_analog_input.read(voltage_input) == RTT::NewData)
    {      
        float real_voltage = voltage_input.data;
	double angle_read = asin((real_voltage-5)/5.0);
	if(!_direction_flag.get())
	  angle_read = -1*angle_read;
	
	double inclination = angle_read + _offset.get();
	
	_angle.write(base::Angle::fromRad(inclination));
	
	//TODO add property to choose the axis sampled?
	base::samples::RigidBodyState roll_sample;       
        roll_sample.sourceFrame = _body_frame.get();
        roll_sample.targetFrame = _world_frame.get();
        roll_sample.position =  Eigen::Vector3d::Zero();
        roll_sample.orientation = Eigen::AngleAxisd( inclination,  Eigen::MatrixBase<base::Vector3d>::UnitX());
        roll_sample.time = base::Time::now();
       _roll_samples.write(roll_sample);
    }

    TaskBase::updateHook();
}
void Task::errorHook()
{
    TaskBase::errorHook();
}
void Task::stopHook()
{
    TaskBase::stopHook();
}
void Task::cleanupHook()
{
    TaskBase::cleanupHook();
}
