Full Name - Bradley McCormack
Student ID - s3258798
Subject CPT373 Web Development Technologies
Study Period 2, 2012


* How to run - Visual Studio*
- Press F5 or Click "Play"

* How to run - Command Line *
- cd ASR
- build.bat
- ASR.exe OR
- ASR.exe filename  to specify the user file to load such as 
- ASR.exe Support\invalid.txt


* Assumptions

- The users.txt file was malformed. Line 3 only had 6 digts after the id e prefix and same for the email. This is invalid as 7 are required to have a file that validates. I fixed it by hand.
- A Room cannot have more than 1 Teacher. The Specification only has constraints on the Student. I'm also inferring that the Constraint should be on the Teacher amount too. 
- I didn't see any requirements to abort input by pressing Q or similar. As such, I didn't implement any. If you make a mistake quit and start again :-)
- Room Availability - The user will enter a date. This functionality will then show all the slots grouped by room in asc order of DateTime
- I wasn't sure if I was supposed to handle booking time intersections. I did so. E.g 9-10 in A should fail if the same teacher requests a slot of 9:15-10:15 in room B

* References
- Blackboard
- Course Material
- http://msdn.microsoft.com/en-us/library/8t9te37d.aspx