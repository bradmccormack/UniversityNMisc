using System;
using ASR.Exceptions;

namespace ASR.Model
{
    /// <summary>
    /// Represents a Teacher in the System. Prevent further subclassing
    /// </summary>
    public sealed class Teacher : Person
    {
        public Teacher(String Name, String ID, String Email) : base(Name, ID, Email) { }

        /// <summary>
        /// Make sure the time is not already allocated for this teacher in a seperate room (also check time intersection)
        /// </summary>
        public void CheckExistingBookings(DateTime Date)
        {
            //Confirm if a slot already exists that would clash with the new slots time
            //eg if a slot is booked at 9-10 and a new slot is requested at 9:45 to 10:45 that would clash
            Slot existing = Bookings.Find(slt => slt.DateTime.Add(slt.Duration) > Date);
            if (existing != null)
            {
                throw new SlotMaximumException(String.Format("Slot already booked out by {0} at {1} till {2} in room {3} which would clash with request of {4}",
                                                             existing.Teacher.Id,
                                                             existing.DateTime.ToString("g"),
                                                             existing.DateTime.Add(existing.Duration).ToString("g"),
                                                             existing.Room.Name,
                                                             Date.ToString("g")));
            }
        }
    }
}
