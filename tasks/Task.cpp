/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Task.hpp"
#include <math.h>
#include <raw_io/Analog.hpp>

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

        if(real_voltage>=1.5 && real_voltage<= 8.5)
        {
            _angle.write(base::Angle::fromRad(asin((real_voltage-5)/5)));
        }
        else
            throw std::logic_error("Voltage outside linear range");

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
