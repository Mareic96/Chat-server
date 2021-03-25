import requests
from requests.auth import HTTPBasicAuth 
import base64

homePage = "http://127.0.0.1:18080/"
home = requests.get(homePage)
print(home)

def login():
    again = True;
    loginPage = homePage + "login"
    while(again == True):
        username = input("Enter your username: ")
        password = input("Enter password: ")
        resp = requests.post(loginPage, auth=HTTPBasicAuth(username, password))
        #print(resp.status_code)
        if(resp.status_code == 401):
            print("Account doesn't exist, your're not authorised to login.\n")
            print("Please try again")
        else:
            print("Welcome\n");
            again = False;

     #print(resp.url)

def readMessages(user):
    url = homePage + "user/" + user
    print(url)
    r = requests.get(url)
    jsonList = r.json()['Messages']
    
    for num, messages in enumerate(jsonList, start=1):
        print("Message number {} is: {} ".format(num, messages));
        input()

def writeMessages():
    sendMessage = input("Message: ")
    #r = requests.get(url)
    #jsonList = r.json()['Messages']
    jsonList = {'message':sendMessage}
    
    #jsonList.append(sendMessage)
    print(jsonList)
    p = requests.post("http://127.0.0.1:18080/user/Mareic1073/send_messages", json=jsonList)
    print(p.text)

login()

readOrWrite = input("Would you like to read or write a message? ")
if(readOrWrite == 'Read' or readOrWrite == 'read'):
    readMessages(username)
elif(readOrWrite == 'Write' or readOrWrite == 'write'):
    writeMessages()
    



