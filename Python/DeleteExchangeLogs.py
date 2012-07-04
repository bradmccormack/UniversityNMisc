import sys,os,time,datetime

days=0
#if no command arg supplied then use default days of 1
if len(sys.argv)==1:
	days=1
	print("No command line args specified")
#if more than 2 supplied only use the second
elif len(sys.argv)>2:
	days=int(sys.argv[2])
	print("Usage: deletelogs.py dayscount")
	print("Ignoring other arguments")
#if the correct amount of args supplied then get the dats
elif len(sys.argv)==2:
	days=int(sys.argv[1])

print("Deleting log older than to " + str(days) +" days old")
print("Log cleanup occured on "+str(datetime.date.today()))


#keep a count of logs deleted and the total amount of MB saved
mbdeleted=0
logsdeleted=0

#get todays date
todaysdate=time.localtime()[7]

#get all the files in the current directory and loop through them
currentdir=os.getcwd()
files=os.listdir(currentdir)
for file in files:
	
	#check file extension for .log
	filename=os.path.splitext(file)
	if filename[1]==".log":
		
		# retrieves the stats for the current file as a tuple
        	# (mode, ino, dev, nlink, uid, gid, size, atime, mtime, ctime)
        	# the tuple element mtime at index 8 is the last-modified-date
		stats=os.stat(file)
	
		# create tuple (year yyyy, month(1-12), day(1-31), hour(0-23), minute(0-59), second(0-59),
        	# weekday(0-6, 0 is monday), Julian day(1-366), daylight flag(-1,0 or 1)) from seconds since epoch
        	# note:  this tuple can be sorted properly by date and time	
		moddate=time.localtime(stats[8])[7]
		
		#only delete the file if its older than the days requested
		daysdiff=todaysdate-moddate
		
		#if the file modification date is up to "days" old then delete it. 
		#if days=5 then all logs up to 5 days old will be deleted
		if daysdiff >=days:
			#attempt to delete the file
			try:
				os.remove(file)
				mbdeleted+=stats[6]
				logsdeleted+=1
			#it was locked or something so skip it
			except Exception:
				print(file+" was locked open by Exchange. Skipped")
				continue


#show the amount of logs deleted and MB that was removed
print(str(logsdeleted)+" logs deleted. "+str(mbdeleted/1024/1024)+" MB was removed")
		


