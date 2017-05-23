#!/usr/bin/env python

#  Kinect_tf_broadcaster sends tf messages to place the Microsoft Kinect sensor correctly.
#  Copyright (C) 2014  Ben Bellekens ben.bellekens@uantwerpen.be
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.

from math import pi

import rospy
import tf
import sensor_msgs.msg

def handle_kinect_tf(msg):


  br = tf.TransformBroadcaster()
  br.sendTransform((0.0, 0.0, -0.1),
                  tf.transformations.quaternion_from_euler(pi / 2.0, pi, pi / 2.0,),
                  msg.header.stamp,
                  "kinect",
                  "base_link")

if __name__ == '__main__':
  print "Starting static transform"
  rospy.init_node('kinect_tf_broadcaster')
  rospy.Subscriber('/camera/depth/points',
                   sensor_msgs.msg.PointCloud2,
                   handle_kinect_tf)
  rospy.spin()
