using System;

namespace ASR.Model
{
    /// <summary>
    /// Various data structures that are central to the program
    /// </summary>
    public static class DataTypes
    {

        public static readonly TimeSpan SlotTime = new TimeSpan(1, 0, 0);   //Slot duration - by default Each slot must be of 1 hour duration
        public static readonly int StaffMaxSlots = 4; // Maximum slots a staff member may book per day
        public static readonly int RoomMaxSlots = 2; //Maximum slots a room can be booked for per day
        public static readonly int StudentMaxSlots = 1; //Maximum slots for a student per day

        public class SchoolHours
        {
            public static readonly int Start = 9;
            public static readonly int Finish = 14;
        }

        /// <summary>
        /// Menu Options for the Main menu.
        /// </summary>
        public enum MenuMainOptions
        {
            List_Rooms = 1,
            List_Slots,
            Staff_Menu,
            Student_Menu,
            Exit
        }

        /// <summary>
        /// Menu Options for the Teacher menu
        /// </summary>
        public enum MenuStaffOptions
        {
            List_Staff = 1,
            Room_Availability,
            Create_Slot,
            Remove_Slot,
            Exit
        }

        /// <summary>
        /// Menu Options for the Student menu
        /// </summary>
        public enum MenuStudentOptions
        {
            List_Students = 1,
            Staff_Availability,
            Make_Booking,
            Cancel_Booking,
            Exit
        }
    }
}
