from PIL import Image
from decimal import *
import serial

ser = serial.Serial('/dev/cu.usbmodem1411')
#The following will contain the entire list of images, this can then be used to make API calls etc.
imageNumber = ["0000","0010","0019","0018","0015"]

'''We will have to map the product IDs and check for images here '''
def prodMatch(prodId):
#The product ID will come from the card number.
	if prodId!="":
		for i in range(len(imageNumber)):
			print imageNumber[i], prodId[:4] #The prodId comes with /r/n later, so take the first 4 digits
			if prodId[:4] == imageNumber[i]:
				print "Match Found"
				# Load and show the image number.
				fileNumber = imageNumber[i]+".jpeg"
				print "File Number is: ",fileNumber
				Image.open(fileNumber).show()
				print "Image Shown"
			else:
				print "No match"
	else:
		print "Product not found in the Catalouge"
			



inpVal =""
while True:
	val = ser.read() #Val is a string
	if val!="*":
		inpVal = inpVal+ val
		
	else:
		print (inpVal)
		#inpValInt= Decimal(inpVal)
		#print inpValInt
		prodMatch(inpVal)
		inpVal =""

#image =Image.open('File.jpeg')
#image.show()
