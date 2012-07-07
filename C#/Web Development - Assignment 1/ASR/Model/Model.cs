using System;
using System.Collections.Generic;
using ASR.Interfaces;

//The model is not dependent on the View OR the Controller

namespace ASR.Model
{
    //Various Delegates use for the events the Model can Invoke and subscribe to
    public delegate void ChangedEvent(IModel ChangedModel);
    public delegate void RoomsEvent(List<Room> Rooms);
    public delegate void SlotsEvent(List<Slot> Slots, DateTime? ForDate);
    public delegate void PersonsEvent(Dictionary<string, Person> People);

    /// <summary>
    /// The Model for the ASR System
    /// </summary>
    public class Model : IModel
    {
        #region Members
        private List<Room> _rooms;
        private Dictionary<string, Person> _people;

        //Events that may be subscribed to and Invoked
        public event ChangedEvent onChanged;
        public event RoomsEvent OnRooms;
        public event SlotsEvent OnSlots;
        public event PersonsEvent OnPeople;

        #endregion

        public Model()
        {
            //Setup dummy rooms to match the assignment sample-output.txt
            _rooms = new List<Room>();
            _rooms.Add(new Room("A"));
            _rooms.Add(new Room("B"));
            _rooms.Add(new Room("C"));
            _rooms.Add(new Room("D"));
        }


        #region Properties

        public Dictionary<string, Person> Teachers
        {
            // Will return only the Person elements that are of type Teacher 
            get
            {
                return getPeopleOfType<Teacher>(_people);
            }
        }

        public Dictionary<string, Person> Students
        {
            // Will return only the Person elements that are of Type Student
            get
            {
                return getPeopleOfType<Student>(_people);
            }
        }

        public List<Room> Rooms
        {
            get
            {
                return _rooms;
            }
        }
        #endregion

        #region PrivateMethods

        /// <summary>
        /// Will return a dictionary of People of a certain type (Student/Teacher at present)
        /// </summary>
        /// <typeparam name="T">The type of person to search for</typeparam>
        /// <param name="People">The list of people to search in</param>
        /// <returns>Dictionary of People that are of the specified type</returns>
        private Dictionary<string, Person> getPeopleOfType<T>(Dictionary<string, Person> People) where T : Person
        {
            Dictionary<string, Person> found = new Dictionary<string, Person>();
            foreach (Person P in People.Values)
            {
                if (P is T)
                {
                    found[P.Id] = P;
                }
            }
            return found;
        }
        #endregion

        #region PublicMethods

        /// <summary>
        /// Makes a booking for the student with a certain teacher in a certain timeslot
        /// </summary>
        /// <param name="Teacher">The teacher to book with</param>
        /// <param name="Student">The student that has requested to book</param>
        /// <param name="Slot">The timeslot requested</param>
        public void MakeBooking(Teacher Teacher, Student Student, Room R, Slot Slot)
        {

            Slot existingSlot = Teacher.Bookings.Find(S => S.Room == R && S.DateTime == Slot.DateTime && S.Duration == Slot.Duration);
            if (existingSlot != null)
            {
                R.AddSlot(Student, Slot);
            }
            else
            {
                throw new ArgumentException(String.Format("Slot was requested to book but does not exist"));
            }
        }
        /// <summary>
        /// Loads Users of the ASR system from the specified file
        /// </summary>
        /// <param name="Filename">The file name to load the users from</param>
        public void LoadUsers(String Filename)
        {
            _people = Utilitiy.ASRTextFileLoader.LoadPersonDetails(Filename);

            //If there are any subscribers then notify them
            if (onChanged != null)
            {
                onChanged(this);
            }
        }


        /// <summary>
        /// Will notify any observers of Students currently in the system
        /// </summary>
        public void ListStudents()
        {
            if (OnPeople != null)
            {
                OnPeople(Students);
            }
        }

        /// <summary>
        /// Will notify any observers of Teachers currently in the system
        /// </summary>
        public void ListTeachers()
        {
            if (OnPeople != null)
            {
                OnPeople(Teachers);
            }
        }

        /// <summary>
        /// Will notify any observers of Rooms currently in the system
        /// </summary>
        public void ListRooms()
        {
            if (OnRooms != null)
            {
                OnRooms(_rooms);
            }
        }

        /// <summary>
        /// Find all slots on a specific date
        /// </summary>
        /// <param name="forDate">The date to look for slots. Null value specifies any date</param>
        public void ListSlots(DateTime? ForDate)
        {
            List<Slot> found = new List<Slot>();
            foreach (Room r in _rooms)
            {
                foreach (Slot s in r.GetSlots())
                {
                    if (s.DateTime.Date == ForDate || ForDate == null)
                    {
                        found.Add(s);
                    }
                }
            }
            //Notify the View when we have finished
            if (OnSlots != null)
            {
                OnSlots(found, ForDate);
            }

        }
        #endregion
    }
}
