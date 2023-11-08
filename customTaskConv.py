
import rospy
from movel_seirios_msgs.srv import StringTrigger, StringTriggerResponse # like setbool
from std_msgs.msg import Bool, UInt8, String

from customIncity1 import PyIncity1
from customIncity2 import PyIncity2
from customIncity3 import PyIncity3
from customOutcity1 import PyOutcity1
from customOutcity2 import PyOutcity2
from customOutcity3 import PyOutcity3
from customEmptyIncity import PyEmptyIncity
from customEmptyOutcity import PyEmptyOutcity
from customConvDorong import PyConvDorong
from customConvTarik import PyConvTarik
from customLifter0 import PyLifter0
from customLifter1 import PyLifter1
from customLifter2 import PyLifter2

if __name__ == '__main__':
    
    rospy.init_node('custom_task', anonymous=True)
    py_incity1 = PyIncity1()
    py_incity2 = PyIncity2()
    py_incity3 = PyIncity3()
    py_outcity1 = PyOutcity1()
    py_outcity2 = PyOutcity2()
    py_outcity3 = PyOutcity3()
    py_emptyincity = PyEmptyIncity()
    py_emptyoutcity = PyEmptyOutcity()
    py_convdorong = PyConvDorong()
    py_convtarik = PyConvTarik()
    py_lifter0 = PyLifter0()
    py_lifter1 = PyLifter1()
    py_lifter2 = PyLifter2()

    rospy.spin()
