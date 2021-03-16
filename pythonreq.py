import requests

url = input("Enter url: ")

def readMessages():
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


readOrWrite = input("Would you like to read all your messages? ")
if(readOrWrite == 'Read' or readOrWrite == 'read'):
    readMessages()
elif(readOrWrite == 'Write' or readOrWrite == 'write'):
    writeMessages()
    

    #payload = {'Message':['Im making a python client']}
    #p = requests.post("http://127.0.0.1:18080/user/Mareic1073/send_messages", data=payload)
    #print(p.text)

