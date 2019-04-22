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
account_sid = "AC53db19b9bee199055205d0ad3003b3b7"
# Your Auth Token from twilio.com/console
auth_token  = "aa1019986354dddbddb360ecba58906f"

client = Client(account_sid, auth_token)

message = client.messages.create(
    to=receiver, 
    from_="+17059900419",
    body=msg)

print(message.sid)
