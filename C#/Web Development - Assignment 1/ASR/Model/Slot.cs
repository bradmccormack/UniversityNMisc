using System;

namespace ASR.Model
{
    /// <summary>
    /// Represents an Invividual Slot of Booked Time. 
    /// 
    /// </summary>
    public class Slot
    {
        Teacher _teacher;

        public Slot(Teacher Teacher, Student Student, DateTime DateTime)
        {
            _teacher = Teacher;
            this.Student = Student;
            this.DateTime = DateTime;
        }

        //We need a reference to the room
        public Room Room
        {
            get;
            set;
        }

        public Teacher Teacher
        {
            get
            {
                return _teacher;
            }
            set
            {
                if (value != null)
                {
                    _teacher = value;
                }
            }
        }

        public Student Student
        {
            get;
            set;

        }

        public DateTime DateTime
        {
            get;
            set;
        }

        public TimeSpan Duration
        {
            get
            {
                return DataTypes.SlotTime;
            }
        }
    }
}
