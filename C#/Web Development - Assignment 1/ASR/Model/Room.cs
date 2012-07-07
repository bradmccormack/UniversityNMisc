using System;
using System.Collections.Generic;
using ASR.Exceptions;

namespace ASR.Model
{
    /// <summary>
    /// Represents a Room in the System
    /// </summary>
    public class Room
    {
        #region Private Members
        List<Slot> _slots;
        #endregion

        public Room(string Name)
        {
            this.Name = Name;
            _slots = new List<Slot>();
        }

        #region Properties

        public String Name
        {
            get;
            set;
        }

        #endregion

        /// <summary>
        /// Returns a list of the slots
        /// </summary>
        /// <returns>List of all the slots for this room</returns>
        public List<Slot> GetSlots()
        {
            return _slots;
        }

        /// <summary>
        /// Books this room for a particular slot
        /// </summary>
        /// <param name="Slot"></param>
        /// <returns></returns>
        public void AddSlot(Person Sender, Slot Slot)
        {
            //Generic validation against School hours and room maximum slots
            if (Slot.DateTime.Hour < DataTypes.SchoolHours.Start || Slot.DateTime.Hour > DataTypes.SchoolHours.Finish)
            {
                throw new ArgumentException(String.Format("{0} is an invalid booking time. Must be between {1} and {2}!",
                                            Slot.DateTime.ToString("HH:mm"),
                                            DataTypes.SchoolHours.Start,
                                            DataTypes.SchoolHours.Finish));
            }
            if (_slots.Count == DataTypes.RoomMaxSlots)
            {
                throw new SlotMaximumException(String.Format("Room {0} Currently full!", Name));
            }

            //Assign the current Room to the slot that has been requested
            Slot.Room = this;

            //Student Specific Validations
            if (Sender is Student)
            {
                if (Slot.Student != null && Slot.Student.Bookings.Count == DataTypes.StudentMaxSlots)
                {
                    throw new SlotMaximumException(String.Format("Student of ID {0} already has maximum slots of ({1}) booked for the day!", Slot.Student.Id, DataTypes.StudentMaxSlots));
                }

                //Find the existing slot that has been booked by a teacher. If it hasn't something awry has happend. Should not be possible
                Slot Existing = _slots.Find(r => r.DateTime == Slot.DateTime && r.Duration == Slot.Duration);
                if (Existing == null)
                {
                    throw new ArgumentException(String.Format("Slot was requested by Student {0} at DateTime {1} when it has not been reserved by any teacher. This should not happen!",
                                                            Slot.Student.Id,
                                                            Slot.DateTime.ToString("g")));
                }
                else
                {
                    if (Existing.Student != null)
                    {
                        throw new SlotMaximumException(String.Format("Room {0} at {1} is already booked by {2} for a duration of {3}!",
                                                            Existing.Room.Name,
                                                            Slot.DateTime.ToString("g"),
                                                            Existing.Student.Id,
                                                            Slot.Duration));
                    }

                    //Assign the student to the existing slot
                    Existing.Student = Slot.Student;

                    //Register Slot for the Student
                    Sender.Bookings.Add(Slot);
                    return;
                }
            }

            //Teacher specific Validation
            if (Sender is Teacher)
            {
                //Validate against maximum slots for a teacher
                if (Slot.Teacher != null & Slot.Teacher.Bookings.Count == DataTypes.StaffMaxSlots)
                {
                    throw new SlotMaximumException(String.Format("Teacher of ID {0} already has maximum slots of ({1}) booked for the day!", Slot.Teacher.Id, DataTypes.StaffMaxSlots));
                }
                //Register Slot for the Teacher
                Sender.Bookings.Add(Slot);
            }

            //Register Slot for the room 
            _slots.Add(Slot);
        }

        /// <summary>
        /// Cancels a particular booking
        /// </summary>
        /// <param name="Sender">The Student reference that wants to cancel a slot</param>
        /// <param name="Slot">The slot to cancel for the student</param>
        public void CancelBooking(Student Sender, Slot Slot)
        {
            //If the booking currently exists for this student then clear it from the student and clear the student reference for that booking by the teacher
            Slot existing = _slots.Find(ex => ex.Teacher == Slot.Teacher && ex.Student == Slot.Student && ex.DateTime == Slot.DateTime);
            if (existing != null)
            {
                existing.Student = null;
                Sender.Bookings.Remove(existing);
            }
            else
            {
                throw new ArgumentException(String.Format("This slot has not been booked for this room"));
            }
        }

        /// <summary>
        /// Deletes a particular Slot
        /// </summary>
        /// <param name="Sender">The Teacher that has requested to delete the slot</param>
        /// <param name="Slot">The slot to delete</param>
        public void DeleteSlot(Teacher Sender, Slot Slot)
        {
            //Check to see if a student has already booked 
            if (Slot.Student != null)
            {
                throw new SlotPermissionException(String.Format("The room is already booked by Student {0} cannot delete slot.", Slot.Student.Id));
            }

            //If this room contains this booking then remove it and also remove it from the Teacher who instigated the removal
            if (_slots.Contains(Slot))
            {
                Sender.Bookings.Remove(Slot);
                _slots.Remove(Slot);
            }
            else
            {
                throw new ArgumentException(String.Format("This slot has not been booked for this room"));
            }
        }
    }
}
