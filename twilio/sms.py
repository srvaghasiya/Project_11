from twilio.rest import Client
import sys

# reciever's phone number
receiver = '+1'+str(sys.argv[1])

#message to be send
msg = ''
for i in range (2,len(sys.argv)):
	msg = str(msg)+str(sys.argv[i])+' '	

#print(msg)

# Your Account SID from twilio.com/console
account_sid = "AC2ba2b8d6e65379f59dc011d18ef989df"
# Your Auth Token from twilio.com/console
auth_token  = "9cff220292a22eeb87b41d90e7bbb4df"

client = Client(account_sid, auth_token)

message = client.messages.create(
    to=receiver, 
    from_="+17099100419",
    body=msg)

print(message.sid)
