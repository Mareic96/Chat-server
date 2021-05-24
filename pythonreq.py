import requests
from requests.auth import HTTPBasicAuth 
import base64

homePage = "http://127.0.0.1:18080/"
home = requests.get(homePage)
print(home)

class User:
    username = ""#These are properties of the class
    password = ""
    header = ""

#below the method is a function that belongs to a class
    def login(self):
        again = True
        loginPage = homePage + "login"
        while(again == True):
            self.username = input("Please enter your username: ")
            self.password = input("Please enter your password: ")
            username = "%s" % (self.username)
            password = "%s" % (self.password)
            resp = requests.post(loginPage, auth=HTTPBasicAuth(username, password))
            if(resp.status_code == 401):
                print("Account doesn't exist, your're not authorised to login.")
                print("Please try again")
            else:
                print("Welcome")
                self.header = resp.headers
                #print(resp.headers)
                again = False
        #return resp.headers

def readMessages(user, header):
    url = homePage + "user/" + user
    resp = requests.get(url, headers={'Authorization':header['JWT']})
    #resp = requests.get(url, headers={'Authorization':"I am a bad person Tom"})
    #print(url)
    #r = requests.get(url)
    #print(resp.headers)
    #print(resp.content)

    try:
        resp.raise_for_status()
    except requests.exceptions.HTTPError as err:
        if(resp.status_code == 401):
            print(err)
            return
        else:
            raise

    jsonList = resp.json()['Messages']  
    for num, messages in enumerate(jsonList, start=1):
        print("Message number {} is: {} ".format(num, messages));
        input()

def writeMessages(user, header):
    sendMessage = input("Message: ")
    #r = requests.get(url)
    #jsonList = r.json()['Messages']
    jsonList = {'message':sendMessage}
    
    #jsonList.append(sendMessage)
    print(jsonList)
    sendMessUrl = "http://127.0.0.1:18080/user/" + user + "/send_messages"
    #p = requests.post(sendMessUrl, json=jsonList, headers={'Authorization':"I am hacker"})
    p = requests.post(sendMessUrl, json=jsonList, headers={'Authorization':header['JWT']})
    print(p.text)

user1 = User()
user1.login()

readOrWrite = input("Would you like to read or write a message? ")
if(readOrWrite == 'Read' or readOrWrite == 'read'):
    readMessages(user1.username, user1.header)
elif(readOrWrite == 'Write' or readOrWrite == 'write'):
    writeMessages(user1.username, user1.header)
