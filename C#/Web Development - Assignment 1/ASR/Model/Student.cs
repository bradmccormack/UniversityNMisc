using System;

namespace ASR.Model
{
    /// <summary>
    /// Represents a Student in the system. Prevent further subclassing
    /// </summary>
    public sealed class Student : Person
    {
        //Call base constructor with args
        public Student(String Name, String ID, String Email) : base(Name, ID, Email) { }
    }
}
