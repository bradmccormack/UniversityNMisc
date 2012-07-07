using System;
using System.Collections.Generic;
using System.Linq;
using ASR.Interfaces;
using ASR.Utilitiy;
using ASR.Model;
using System.Threading;
using System.Globalization;

namespace ASR.View
{
    /// <summary>
    /// The MainConsoleView which provides output , input and interaction with the user via the console
    /// </summary>
    public class MainConsoleView : IMainView
    {
        private IModel _model;

        public MainConsoleView(IModel Model)
        {
            _model = Model;
            _model.OnRooms += new RoomsEvent(_model_OnRooms);
            _model.OnSlots += new SlotsEvent(_model_OnSlots);
            _model.OnPeople += new PersonsEvent(_model_OnPeople);
        }

        #region PrivateMethods

        //The following Menu implementation makes it extremely easy to add display/input for any other menus.
        /// <summary>
        /// Helper for GetMenuOption which actually displays the menu
        /// </summary>
        private void ShowMenu<T>(String Heading, List<T> Menu) where T : struct, IConvertible
        {
            Console.WriteLine("\n\n" + Heading);
            Console.WriteLine(Helper.Divider('-', 60));
            foreach (var menuItem in Menu)
            {
                string menuItemText = menuItem.ToString();
                var opt = (int)(Enum.Parse(typeof(T), menuItemText));

                //Clean up the enum description for output
                Console.WriteLine(string.Format("{0}. {1}", opt, menuItemText.Replace('_', ' ')));
            }
        }

        /// <summary>
        /// Creates a menu and gets menu option input from a specified type that implements IConvertible
        /// </summary>
        /// <typeparam name="T"> The generic type that we want to create a menu from and get input for</typeparam>
        /// <param name="Prompt"> String prompt for input</param>
        /// <param name="Menu">The generic type that contains the information a menu is derrived from</param>
        /// <returns></returns>
        private T getMenuOption<T>(string Heading, string Prompt, List<T> Menu) where T : struct, IConvertible
        {
            bool valid = false;
            T option = default(T);
            while (!valid)
            {
                try
                {
                    ShowMenu(Heading, Menu);
                    Console.Write(Prompt);
                    //For now getMenuOption only supports Enum types for generating Menu's
                    if (typeof(T).IsEnum)
                    {
                        /*
                         * Read from the console and attempt to cast it to the particular Enum Type passed in.
                         * If OK then make sure It's a valid Option that has been input
                         */
                        T opt;
                        if (Enum.TryParse<T>(Console.ReadLine(), out opt))
                        {
                            valid = Menu.Contains(opt);
                            option = opt;
                        }
                    }
                    if (!valid)
                    {
                        throw new ArgumentException();
                    }
                }
                catch (ArgumentException)
                {
                    Console.WriteLine("Invalid input ...");
                }
            }
            return option;
        }

        /// <summary>
        /// Inputs a Date with validation
        /// </summary>
        /// <returns></returns>
        private DateTime getDate(string Prompt)
        {
            DateTime d;
            do
            {
                Console.WriteLine(String.Format("Enter valid date for {0}:", Prompt));
            } while (!DateTime.TryParseExact(Console.ReadLine(), "dd-MM-yyyy", Thread.CurrentThread.CurrentCulture.DateTimeFormat, DateTimeStyles.None, out d));
            return d;
        }

        /// <summary>
        /// Will get a particular type of Person designated by Person including appropriate validation
        /// </summary>
        /// <typeparam name="T">The type of Person to return eg Teacher, Student</typeparam>
        /// <returns>The value found</returns>
        private T getPerson<T>() where T : Person
        {
            Person P = null;
            string target = string.Empty;
            Dictionary<String, Person> targetCollection;
            if (typeof(T) == typeof(Teacher))
            {
                target = "Teacher";
                targetCollection = _model.Teachers;
            }
            else
            {
                target = "Student";
                targetCollection = _model.Students;
            }
            do
            {
                Console.WriteLine(String.Format("Enter valid {0} ID:", target));
                string desiredID = Console.ReadLine();
                //Make sure the ID exists in the system
                P = targetCollection.Values.FirstOrDefault(tch => tch.Id == desiredID);
            } while (P == null);
            return (T)P;
        }

        /// <summary>
        /// Gets a valid room from the available rooms
        /// </summary>
        /// <returns></returns>
        private Room getRoom()
        {
            Room room;
            do
            {
                Console.WriteLine("Enter room name:");
                string desiredRoom = Console.ReadLine();
                room = _model.Rooms.Find(rm => rm.Name == desiredRoom);
            } while (room == null);
            return room;
        }

        /// <summary>
        /// Gets a valid time slot
        /// </summary>
        /// 
        private TimeSpan getTime()
        {
            TimeSpan t;
            do
            {
                Console.WriteLine("Enter valid time for slot (hh:mm):");
            } while (!TimeSpan.TryParse(Console.ReadLine(), out t));
            return t;
        }

        #endregion

        #region PublicMethods

        #region TeacherFunctionality

        /// <summary>
        /// The user will enter a date. This functionality will then show all the slots grouped by room in asc order of DateTime
        /// </summary>
        public void RoomAvailability()
        {
            DateTime d = getDate("slot(dd-mm-yyyy)");
            foreach (Room r in _model.Rooms)
            {
                Console.WriteLine(String.Format("Room: {0}", r.Name));

                //Get all the slots for this room and sort by datetime
                List<Slot> slots = r.GetSlots();
                if (slots.Count > 0)
                {
                    Console.WriteLine(String.Format("{0,-10} {1,-25} {2,-20} {3,-10}", "TeacherID", "Start", "Duration", "StudentID"));
                    foreach (Slot l in slots.OrderBy(dd => dd.DateTime))
                    {
                        Console.WriteLine(String.Format("{0,-10} {1,-25} {2,-20} {3,-10}",
                                                        l.Teacher.Id,
                                                        l.DateTime.ToString("g"),
                                                        l.Duration,
                                                        l.Student !=null ? l.Student.Id : String.Empty));
                    }
                    Console.WriteLine();
                }
                else
                {
                    Console.WriteLine("No Bookings\n");
                }
            }
        }

        /// <summary>
        /// Creates a slot for the Teacher
        /// </summary>
        public void CreateSlot()
        {
            DateTime d = getDate("slot(dd-mm-yyyy)");
            TimeSpan t = getTime();
            Teacher teacher = getPerson<Teacher>();

            DateTime date = new DateTime(d.Year, d.Month, d.Day, t.Hours, t.Minutes, 0);
            teacher.CheckExistingBookings(date);

            Room room = getRoom();
            room.AddSlot(teacher, new Slot(teacher, null, date));
        }
        /// <summary>
        /// Delets a slot reserved by a Teacher
        /// </summary>
        public void DeleteSlot()
        {
            Teacher teacher = getPerson<Teacher>();
            if (teacher.Bookings == null || teacher.Bookings.Count == 0)
            {
                Console.WriteLine("No current Bookings");
                return;
            }

            //Show all the current slots for the teacher and choose one to delete
            Console.WriteLine(String.Format("Current Slots for {0}", teacher.Id));
            Console.WriteLine(String.Format("{0,-3} {1,-5} {2,-20} {3,-10} {4,3}",
                "No",
                "Room",
                "DateTime",
                "Duration",
                "Booked"));
            for (int i = 0; i < teacher.Bookings.Count; i++)
            {
                Slot slot = teacher.Bookings[i];
                Console.WriteLine(String.Format("{0,-3} {1,-5} {2,-20} {3,-10} {4,3}",
                    i,
                    slot.Room.Name,
                    slot.DateTime.ToString("g"),
                    slot.Duration,
                    slot.Student == null ? "No" : "Yes"));

            }
            int choice = -1; bool valid = false;
            do
            {
                Console.Write("Enter a valid Slot No to delete : ");
                valid = int.TryParse(Console.ReadLine(), out choice);
            } while (choice < 0 || choice >= teacher.Bookings.Count || !valid);

            //Remove the booking from the room
            Slot Booking = teacher.Bookings[choice];
            Booking.Room.DeleteSlot(teacher, Booking);
            Console.WriteLine("Slot deleted");
        }



        #endregion

        #region StudentFunctionality
        /// <summary>
        /// List's availabile 
        /// </summary>
        public void ListAvailability()
        {
            DateTime d = getDate("staff availability (dd-mm-yyyy)");
            Teacher teacher = getPerson<Teacher>();
            Console.WriteLine(String.Format("Staff {0} availability on {1}", teacher.Id, d.ToString("dd-mm-yyyy")));
            Console.WriteLine(String.Format("{0,-10} {1, -20} {2,-20} {3,-15}", "Room name", "Start Time", "End Time", "Room Currently Booked"));
            foreach (Slot s in teacher.Bookings)
            {
                Console.WriteLine(String.Format("{0,-10} {1, -20} {2,-20} {3,-15}", s.Room.Name,
                                                                            s.DateTime.ToString("g"),
                                                                            s.DateTime.Add(s.Duration).ToString("g"),
                                                                            s.Student == null ? "No" : "Yes"));
            }
        }

        /// <summary>
        /// Attempts to make a booking for a student in a particular room, for a particular teacher at a certain time.
        /// </summary>
        public void MakeBooking()
        {
            DateTime d = getDate("slot(dd-mm-yyyy)");
            TimeSpan t = getTime();
            Teacher teacher = getPerson<Teacher>();
            Room room = getRoom();
            Student student = getPerson<Student>();
            _model.MakeBooking(teacher, student, room, new Slot(teacher, student, new DateTime(d.Year, d.Month, d.Day, t.Hours, t.Minutes, t.Seconds)));
        }

        /// <summary>
        /// Cancels a booking for a student
        /// </summary>
        public void CancelBooking()
        {
            Student student = getPerson<Student>();
            if (student.Bookings == null || student.Bookings.Count == 0)
            {
                Console.WriteLine("No current bookings");
                return;
            }

            //Show all bookings for the student and select one to cancel
            Console.WriteLine(String.Format("Current Slots for {0}", student.Id));
            Console.WriteLine(String.Format("{0,-3} {1,-5} {2,-20} {3,-10}",
                "No",
                "Room",
                "DateTime",
                "Duration"
               ));
            for (int i = 0; i < student.Bookings.Count; i++)
            {
                Slot slot = student.Bookings[i];
                Console.WriteLine(String.Format("{0,-3} {1,-5} {2,-20} {3,-10}",
                    i,
                    slot.Room.Name,
                    slot.DateTime.ToString("g"),
                    slot.Duration
                   ));

            }
            int choice = -1; bool valid = false;
            do
            {
                Console.Write("Enter a valid Slot No to delete : ");
                valid = int.TryParse(Console.ReadLine(), out choice);
            } while (choice < 0 || choice >= student.Bookings.Count || !valid);

            //Cancel the booking
            Slot Booking = student.Bookings[choice];
            Booking.Room.CancelBooking(student, Booking);
            Console.WriteLine("Booking cancelled");
        }

        #endregion

        #region ViewMethods
        /// <summary>
        /// Writes the string to the console
        /// </summary>
        /// <param name="s"></param>
        public void Write(String s)
        {
            Console.WriteLine(s);
        }

        /// <summary>
        /// Gets the menu option for the main menu
        /// </summary>
        /// <param name="Heading">Heading to display</param>
        /// <returns>A MenuMainOptions enum value</returns>
        public DataTypes.MenuMainOptions GetMainMenuOption(string Heading)
        {
            return getMenuOption<DataTypes.MenuMainOptions>(Heading, "Enter option:", Helper.ToList<DataTypes.MenuMainOptions>());
        }

        /// <summary>
        /// Gets the menu option for the staff menu
        /// </summary>
        /// <param name="Heading">Heading to display</param>
        /// <returns>A MenuStaffOptions enum value</returns>
        public DataTypes.MenuStaffOptions GetStaffMenuOption(string Heading)
        {
            return getMenuOption<DataTypes.MenuStaffOptions>(Heading, "Enter option:", Helper.ToList<DataTypes.MenuStaffOptions>());
        }

        /// <summary>
        /// Gets the menu option for the Student menu
        /// </summary>
        /// <param name="Heading">Heading to display</param>
        /// <returns>A MenuStudentOptions enum value</returns>
        public DataTypes.MenuStudentOptions GetStudentMenuOption(string Heading)
        {
            return getMenuOption<DataTypes.MenuStudentOptions>(Heading, "Enter option:", Helper.ToList<DataTypes.MenuStudentOptions>());
        }

        /// <summary>
        /// Generic welcome display
        /// </summary>
        public void ShowWelcome()
        {
            Console.WriteLine(Helper.Divider('-', 60));
            Console.WriteLine("Welcome to Appointment Scheduling and Reservation System");
        }

        /// <summary>
        /// Generic exit display
        /// </summary>
        public void ShowExit()
        {
            Console.WriteLine("Terminating ASR .. Press any key");
            Console.ReadKey();
        }
        #endregion
        #endregion

        #region Events

        /// <summary>
        /// Callback for People collection being changed in the Model
        /// </summary>
        /// <param name="People"></param>
        void _model_OnPeople(Dictionary<String, Person> People)
        {
            //Show all people in the System
            Console.WriteLine(String.Format("{0,-20} {1,-8} {2,-25}",
                 "Name",
                 "ID",
                 "Email"));

            foreach (Person P in People.Values)
            {
                Console.WriteLine(String.Format("{0,-20} {1,-8} {2,-25}",
                    P.Name,
                    P.Id,
                    P.Email));
            }
        }

        //Show the Slots when the model notifies of Slot information
        void _model_OnSlots(List<Slot> Slots, DateTime? ForDate)
        {
            Console.WriteLine(string.Format("Existing slots on {0}:", ForDate));
            //Left align all headings
            Console.WriteLine(string.Format("{0,-9} {1,-20} {2,-20} {3,-15} {4,-15}",
                                            "Room name",
                                            "Start Time",
                                            "End Time",
                                            "Staff ID",
                                            "Bookings"));

            if (Slots == null || Slots.Count == 0)
            {
                Console.WriteLine("<no existing slots>");
                return;
            }
            foreach (Slot s in Slots)
            {

                Console.WriteLine(String.Format("{0,-9} {1,-20} {2,-20} {3,-15} {4,-15}",
                                                s.Room.Name,
                                                s.DateTime,
                                                s.DateTime.Add(s.Duration),
                                                s.Teacher.Id,
                                                s.Student == null ? "-" : s.Student.Id));
            }
        }

        //Show the Rooms when the model notifies of Room information
        void _model_OnRooms(List<Room> Rooms)
        {
            Console.WriteLine("Room Name");
            foreach (Room r in Rooms)
            {
                Console.WriteLine(r.Name);
            }
        }

        #endregion

    }
}
