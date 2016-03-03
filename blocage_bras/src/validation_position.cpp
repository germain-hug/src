//Programme qui analyse et filtre les coordonnées angulaires du bras
//afin de ne publier que celles qui ne le mettent pas en danger

#include "ros/ros.h"
#include "boost/units/systems/si.hpp"
#include "boost/units/io.hpp"
#include "brics_actuator/JointPositions.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

ros::Publisher pub;
ros::Subscriber sub;

void callback(const brics_actuator::JointPositions& msg)
{//Des nouvelles coordonnées ont été publiées

  //1) On vérifie qu'il est dans les bornes constructeur
// Cf Frezza ->  void in_bounds() {
//     if(angles[0]<.2) angles[0] = .2;
//   }

  //2) On calcule la distance avec le point le plus proche
  
  //Si ok on publie
  pub.publish(msg);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "record_position");
  ros::NodeHandle n;
  pub = n.advertise<brics_actuator::JointPositions>("out", 1);
  sub = n.subscribe("in",1,callback);
  ros::Rate r(10);
  sleep(1);
  while (ros::ok())
    { ros::spinOnce();
      r.sleep();
    }
  return 0;
}
