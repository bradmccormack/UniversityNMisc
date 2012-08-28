import os.path

def read_lines(filename):
    """
    Read all lines from filename and return them
    """
    if os.path.isfile(filename):
        with open(filename, 'r') as f:  
            lines = [line.strip() for line in f if not line.startswith("#")]
            return lines
        
def read_table(filename):
    """
    Process filename and return a list of lists
    """
    lines = [line.split(":") for line in read_lines(filename)]
    return lines
    
def write_lines(filename, lines):
    """
    Writeout all of the lines in the lines argument to the filename specified
    """
    try:
        f = open(filename, "w")
        try:
            for line in lines:
                f.write(line + '\n')    
        finally:
            f.close()
            return 1
    except:
        return 0


class Enrol(object): 
    def __init__(self, Directory):
        self.Data = {'SUBJECTS': {} , 'CLASSES': {}, 'VENUES': {} , 'STUDENTS' : {} }
        self.Active = {} # active classes
        
        self.Directory = Directory
        
        for filename in os.listdir(Directory):
            if(filename in self.Data.iterkeys()):
                #read in colon delimited data
                table = read_table(Directory + filename)
                #make a new dataDict the first value is the key .. the remaining data is the values
                dataDict = {}
                for row in table:
                    dataDict[row[0]] = row[1:]
                self.Data[filename] = dataDict
                
        #find all enrollment records for all classes
        for cl in self.Data["CLASSES"]:
            self.Active[cl] = 0 #no students attending by default
            students = read_lines(Directory + cl + ".roll")
            #Iterate over all students in the class file and add a record of the classes this student attends
            if(students != None):
                for student in students:
                    if student not in self.Data["STUDENTS"]:
                        self.Data["STUDENTS"][student] = []
                    #register class against student
                    self.Data["STUDENTS"][student].append(cl)
                    #add a count to the class
                    self.Active[cl] = self.Active[cl] + 1
    
    
    def getStudents(self, classCode):
        """
        Gets all of the students registered for classCode
        """
        return [k for k, v in self.Data["STUDENTS"].iteritems() if classCode in v]
    
    def getClassInfo(self, classCode):
        """
        Get information about the class matching classCode
        """
        return self.Data["CLASSES"][classCode]
                                 
    def subjects(self):
        """
        Get all of the subjects
        """
        if self.Data["SUBJECTS"] != None:
                return self.Data["SUBJECTS"].keys()
        
    def subject_name(self, SubjectCode):
        """
        Get the name of the subject that SubjectCode represents
        """
        if self.Data["SUBJECTS"] != None:
            if SubjectCode in self.Data["SUBJECTS"]:
                return self.Data["SUBJECTS"][SubjectCode][0]
            else:
                raise KeyError
    
    def classes(self, SubjectCode):
        """
        Get all of the classes that belong to Subject matching SubjectCode
        """
        if self.Data["CLASSES"] != None:
            result = [k for k, v in self.Data["CLASSES"].iteritems() if v[0] == SubjectCode]
            #If the length of the result is zero It can be inferred that the key didn't exist
            if(len(result) == 0):
                raise KeyError
            return result
              
               
    def class_info(self, ClassCode):
        """
        Get information about the class matching ClassCode with some constraints
        """
        if self.Data["CLASSES"] != None:
            if ClassCode in self.Data["CLASSES"]:
                cl = [v for k, v in self.Data["CLASSES"].iteritems() if k == ClassCode]
                return (str(cl[0][0]), str(cl[0][1]), str(cl[0][2]), str(cl[0][3]) , self.getStudents(ClassCode))
            else:
                raise KeyError
            
        
 
    def check_student(self, StudentId, SubjectCode=None):
        """
        find all classes for the specified subject (or all if not spec) that the student is enrolled for
        """   
        #even though not required in the assignment spec let's be defensive
        if StudentId not in self.Data["STUDENTS"]:
            raise KeyError
        
        #loop through all classes assigned to the specified student
        #if the subjectcode is NOT None then check if the current class has a subject of subject code
        #else just add it
        slist = []
        for cl in self.Data["STUDENTS"][StudentId]:
            if SubjectCode == None:
                slist.append(cl)
            else:
                if self.Data["CLASSES"][cl][0] == SubjectCode:
                    slist.append(cl) 
                
        if SubjectCode == None:
            return slist
        elif(len(slist) == 0):
            return None
            
        
    #returns 1 if succ None if not
    def enrol(self, StudentId, ClassCode):
	#attempts to enrol a student with StudentId Id to the class with code ClassCode
        if ClassCode not in self.Data["CLASSES"]:
            raise KeyError
        
        #Check Capacity of class
        cap = self.Data["VENUES"][self.Data["CLASSES"][ClassCode][2]]
        if self.Active[ClassCode] >= cap:
            return None
   
        #Are they an existing student?
        if StudentId in self.Data["STUDENTS"]:
            basesubject = self.Data["CLASSES"][ClassCode][0]     #remove them from any existing classes of the same ID
    
            #decrement the appropriate class count  
            for cl in [cl for cl in self.Data["STUDENTS"][StudentId] 
                       if self.Data["CLASSES"][cl][0] == basesubject]: self.Active[cl] = self.Active[cl] - 1
            
            #remove all classes in this students list that match this subject
            self.Data["STUDENTS"][StudentId] = [cl for cl in self.Data["STUDENTS"][StudentId] 
                       if self.Data["CLASSES"][cl][0] != basesubject]
        
        #add the student to the class 
        self.Active[ClassCode] = self.Active[ClassCode] + 1
        self.Data["STUDENTS"][StudentId].append(ClassCode)
            
        #save the updated Students file and class role
        write_lines(self.Directory + ClassCode + ".roll", self.getStudents(ClassCode))
        return 1

    
      





