require 'orocos'
include Orocos

## Initialize orocos ##
Orocos.initialize

## Execute the task 'message_producer::Task' ##
Orocos.run 'inclinometer::Task' => 'inclinometer' do
  ## Get the task context##
  inclinometer = Orocos.name_service.get 'inclinometer'
  ## Create a sample writer for a port ##
  voltagePort = inclinometer.analog_input.writer
  ## Start the tasks ##
  

  
  voltage = voltagePort.new_sample
  voltage.data = 1.5*(293/870.0)
  voltage.time =Types::Base::Time.new
  
  inclinometer.configure
  inclinometer.start
  while true
    voltagePort.write(voltage) 
    voltage.data = voltage.data + (293/1740.0)
   sleep 0.1
  end
end
