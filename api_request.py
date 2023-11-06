#!/usr/bin/env python3

import json
import requests
import rospy

from std_msgs.msg import String

# Define the base URL and the endpoint
task_endpoint = "/task_list"

base_url = " http://localhost:8000/api/v1"
token_endpoint = "/user/token"
map_id_endpoint = "/map/current"
goto_pose_endpoint = "/bot/goto/pose"
all_get_endpoint = task_endpoint + "/all"
run_endpoint = task_endpoint + "/run_now"
queue_waypoint_endpoint = task_endpoint + "/add_queue"
get_running_task_endpoint = "/queue/active"

# Nama Task_List sesuaikan dengan yang ada
taskIncity1 = "TASK_Bagian_A"
taskIncity2 = "TASK_Bagian_B"
taskIncity3 = "TASK_Bagian_C"
taskOutcity1 = "TASK_Bagian_D"
taskOutcity2 = "TASK_Bagian_E"
taskOutcity3 = "TASK_Bagian_F"

def get_auth_token():
    # Define the request body with username and password
    body = {
    "username": "admin",
    "password": "admin"
    }

    # Make a POST request to the endpoint with the body
    response = requests.post(base_url + token_endpoint, json=body)

    # Check the status code of the response
    if response.status_code == 200:
        # Extract the token from the response
        token = response.json()["token"]
        # Print the token
        #print("The user token is:", token)
        return token
    else:
        # Print the error message
        print("Error:", response.text)
        return None

def get_current_map_id():
    token = get_auth_token()

    # Define the headers with the token
    headers = {
        "authorization": token
    }

    # Make a GET request to the endpoint with the headers
    response = requests.get(base_url + map_id_endpoint, headers=headers)
    if response.status_code == 200:
        # Extract the map id from the response
        map_id = response.json()["_id"]
        #print("The current map id is:", map_id)
        return map_id
    else:
        print("Error:", response.text)
        return None

# Get waypoint id by name
def get_waypoint_id(waypoint_name):
    token = get_auth_token()
    map_id = get_current_map_id()

    headers = {
        "authorization": token
    }

    # Define the query with the map id and waypoint name
    query = {
        "map_id": map_id,
        "name": waypoint_name
    }

    # Make a GET request to the endpoint with the headers and query
    response = requests.get(base_url + all_get_endpoint, headers=headers, params=query)
    #print(response.text)

    if response.status_code == 200:
        waypoint_id = response.json()[0]["_id"]
        print("The waypoint id is:", waypoint_id)
        return waypoint_id
    else:
        print("Error:", response.text)
        return None

# Queue waypoint by waypoint name
def queue_waypoint(waypoint_name):
    token = get_auth_token()
    map_id = get_current_map_id()
    waypoint_id = get_waypoint_id(waypoint_name)

    headers = {
        "authorization": token
    }
    # Define the body with the waypoint id, map id, velocity and startAtNearestPoint
    body = {
        "taskId": waypoint_id,
        "toMapId": map_id,
        "velocity": {
            "linear_velocity": 0.2, # Change this according to your needs
            "angular_velocity": 0.3 # Change this according to your needs
        },
        "startAtNearestPoint": False
    }
    # Make a POST request to the endpoint with the headers and body
    response = requests.post(base_url + queue_waypoint_endpoint, headers=headers, json=body)
    if response.status_code == 200:
        print("Queue waypoint success")
    else:
        print("Error:", response.text)

# Get all running and active task_list
def get_running_task(task_name):
    token = get_auth_token()
    map_id = get_current_map_id()
    waypoint_id = get_waypoint_id(task_name)

    headers = {
        "authorization": token
    }

    # Define the query with the map id and waypoint name
    query = {
        "map_id": map_id,
        "name":""
    }

    # Make a GET request to the endpoint with the headers and query
    response = requests.get(base_url + get_running_task_endpoint, headers=headers)
    #print(response.text)

    if response.status_code == 200:
        if len(response.text) > 0:
        array_task = response.json()
            flag = 0
            for array_task[0] in array_task:
                if array_task[0]["taskId"] == waypoint_id:
                    flag = flag + 1                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
            if flag == 0:
                print("Task_list not queued") 
                return True
            else:
                print("Task_list is already in queue")
                return False
        else:
            print("Queue is empty")
            return True
    else:
        print("Error:", response.text)
        return True
        
#def main():  
#    lala = "TASK_Bagian_A"
#    if get_running_task(lala):
#        queue_waypoint(lala)

def topikCallback(data):
    if data.data == "incity1=ambil":
        queue_waypoint(taskIncity1)
    else if data.data == "incity2=ambil":
        queue_waypoint(taskIncity2)
    else if data.data == "incity3=ambil":
        queue_waypoint(taskIncity3)
    else if data.data == "outcity1=ambil":
        queue_waypoint(taskOutcity1)
    else if data.data == "outcity2=ambil":
        queue_waypoint(taskOutcity2)
    else if data.data == "outcity3=ambil":
        queue_waypoint(taskOutcity3)

sub = rospy.Subscriber('topik_hidayat', String, topikCallback, queue_size=10)

if __name__ == "__main__":
    #main()
    rospy.init_node('api_request', anonymous=True)
    rospy.spin()