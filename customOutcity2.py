import rospy
from movel_seirios_msgs.srv import StringTrigger, StringTriggerResponse # like setbool
from std_msgs.msg import Bool, UInt8, String

class PyOutcity2:

    def __init__(self):
        print('starting outcity 2 node')

        self.service_start = rospy.Service('/external_process/trigger_detecting5', StringTrigger, self.start_handler)
        self.service_stop = rospy.Service('/external_process/stop_detecting5', StringTrigger, self.stop_handler)
        
        # IGNORE dummy_publisher - just to simulate UI cancel topic
        self.dummy_publisher = rospy.Publisher('/cancel_publish', Bool, queue_size=1)

        self.topic_hidayat = rospy.Subscriber('topik_hidayat', String, self.handle_topik, queue_size=10)
        

        self.topic_process_cancel = rospy.Subscriber('/cancel_publish', Bool, self.handle_publish_cancel)
        self.client_status = rospy.Publisher('/external_process/client_status', UInt8, queue_size=1)

        self.flag = True

    def handle_topik(self, data):
        print("Received data : ", data.data)
        if (data.data == "outcity2=clear"):
            self.flag = False

    def start_handler(self, req):
        print('inside start handler')

        start_msg = StringTriggerResponse() 
        start_msg.success = True
        start_msg.message = 'starting detect'

        self.flag = True
        self.publish_client_status()

        while(self.flag):
            print('waiting topic outcity2 to be clear')
            rospy.sleep(1)

        return start_msg # return must be [success, message format]

    def stop_handler(self, req):
        print('inside stop handler')

        self.flag = False
        print('stop handler called')
        stop_msg = StringTriggerResponse()
        stop_msg.success = False
        stop_msg.message = 'stopping detect'

        return stop_msg
    
    # IGNORE if you are not using a topic to stop your code
    def handle_publish_cancel(self, req):
        print("inside publish cancel", req.data)

        cancel_trigger = req.data
        if(cancel_trigger):
            print('executing cancel stuff') # replace print statement
    
    
    # IGNORE if you are not using launch files
    def publish_client_status(self):
        print("publish client status called")
        
        cstatus = UInt8()
        
        #Dummy code
        #Decide how do you determine if your launch file is successful
        #And replace the if-else statement
        if (self.flag == True):
            cstatus.data = 2 # if start_handler successfully called, task is successful and return 2
        else:
            cstatus.data = 3 # else task not successful, return 3

        self.client_status.publish(cstatus)
